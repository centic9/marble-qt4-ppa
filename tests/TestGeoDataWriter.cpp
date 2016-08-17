//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009      Andrew Manson <g.real.ate@gmail.com>
//

#include <QObject>

#include "GeoDataParser.h"
#include "GeoDataDocument.h"
#include "GeoDataColorStyle.h"
#include "GeoWriter.h"

#include <QDir>
#include <QFile>
#include <QTest>
#include <QTemporaryFile>
#include <QTextStream>

using namespace Marble;

class TestGeoDataWriter : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void countFeatures_data();
    void countFeatures();
    void saveFile_data();
    void saveFile();
    void saveAndLoad_data();
    void saveAndLoad();
    void saveAndCompare_data();
    void saveAndCompare();
    void cleanupTestCase();
private:
    QDir dataDir;
    QMap<QString, QSharedPointer<GeoDataParser> > parsers;
};

Q_DECLARE_METATYPE( QSharedPointer<GeoDataParser> )

void TestGeoDataWriter::initTestCase()
{
    QStringList filters;
    filters << "*.kml";
    dataDir.setNameFilters( filters );

    dataDir = QDir( TESTSRCDIR );
    dataDir.cd( "data" );
    //check there are files in the data dir
    QVERIFY( dataDir.count() > 0 );

    //test the loading of each file in the data dir
    foreach( const QString &filename, dataDir.entryList(filters, QDir::Files) ){

        //Add example files
        QFile file( dataDir.filePath(filename));

        //Verify file existence
        QVERIFY( file.exists() );

        //Make the parsers
        GeoDataParser* parser = new GeoDataParser( GeoData_KML );

        QSharedPointer<GeoDataParser>parserPointer ( parser );

        //Open the files and verify
        QVERIFY( file.open( QIODevice::ReadOnly ) );

        //Parser and verify
        QVERIFY2( parser->read( &file ), filename.toLatin1() );

        parsers.insert( filename, parserPointer );

        //close files
        file.close();
    }
}

void TestGeoDataWriter::countFeatures_data()
{
    // add the tables here
    QTest::addColumn<QSharedPointer<GeoDataParser> >("parser");
    QTest::addColumn<int>("count");

    //Add feature parsers ( referenced by file name ) and their count of features

    QTest::newRow("New York") << parsers.value("NewYork.kml") << 1;
    QTest::newRow("New York Document") << parsers.value("NewYorkDocument.kml") << 2;
    QTest::newRow("CDATATest") << parsers.value("CDATATest.kml") << 1;
    QTest::newRow("NetworkLink") << parsers.value("NetworkLink.kml") << 1;
    QTest::newRow("NetworkLinkDocument") << parsers.value("NetworkLinkDocument.kml") << 2;
    QTest::newRow("MackyModel") << parsers.value("MackyModel.kml") << 1;
    QTest::newRow("Tour") << parsers.value("Tour.kml") << 1;
    QTest::newRow("AltitudeMode") << parsers.value("AltitudeMode.kml") << 1;
    QTest::newRow("ScreenOverlay_Folder") << parsers.value("ScreenOverlay_Folder.kml") << 1;
    QTest::newRow("ScreenOverlay_kml") << parsers.value("ScreenOverlay_kml.kml") << 1;
}

void TestGeoDataWriter::countFeatures()
{
    //count the features in the loaded KML file
    QFETCH(QSharedPointer<GeoDataParser>, parser);
    QFETCH(int, count );
    GeoDataDocument* document = dynamic_cast<GeoDataDocument*>(parser->activeDocument());
    QVERIFY( document );

    // there should be exactly 1 placemark in the NewYork File
    QCOMPARE( document->size(), count );
}

void TestGeoDataWriter::saveFile_data()
{
    QTest::addColumn<QSharedPointer<GeoDataParser> >( "parser" );

    QTest::newRow( "NewYork" ) << parsers.value("NewYork.kml");
    QTest::newRow( "NewYorkDocument") << parsers.value("NewYorkDocument.kml");
    QTest::newRow("CDATATest") << parsers.value("CDATATest.kml");
    QTest::newRow("NetworkLink") << parsers.value("NetworkLink.kml");
    QTest::newRow("NetworkLinkDocument") << parsers.value("NetworkLinkDocument.kml");
    QTest::newRow("MackyModel") << parsers.value("MackyModel.kml");
    QTest::newRow("Tour") << parsers.value("Tour.kml");
    QTest::newRow("AltitudeMode") << parsers.value("AltitudeMode.kml");
    QTest::newRow("ScreenOverlay_Folder") << parsers.value("ScreenOverlay_Folder.kml");
    QTest::newRow("ScreenOverlay_kml") << parsers.value("ScreenOverlay_kml.kml");
}

void TestGeoDataWriter::saveFile()
{
    QFETCH( QSharedPointer<GeoDataParser>, parser );

    //attempt to save a file using the GeoWriter
    QTemporaryFile tempFile;

    GeoWriter writer;
    //FIXME: a better way to do this?
    writer.setDocumentType( "http://earth.google.com/kml/2.2" );

    // Open file in right mode
    QVERIFY( tempFile.open() );

    QVERIFY( writer.write( &tempFile, &(*dynamic_cast<GeoDataFeature*>(parser->activeDocument() ) ) ) );

}

void TestGeoDataWriter::saveAndLoad_data()
{
    QTest::addColumn<QSharedPointer<GeoDataParser> >("parser");

    QTest::newRow("NewYork") << parsers.value( "NewYork.kml" ) ;
    QTest::newRow("NewYorkDocument") << parsers.value( "NewYorkDocument.kml" );
    QTest::newRow("CDATATest") << parsers.value("CDATATest.kml");
    QTest::newRow("NetworkLink") << parsers.value("NetworkLink.kml");
    QTest::newRow("NetworkLinkDocument") << parsers.value("NetworkLinkDocument.kml");
    QTest::newRow("MackyModel") << parsers.value("MackyModel.kml");
    QTest::newRow("Tour") << parsers.value("Tour.kml");
    QTest::newRow("AltitudeMode") << parsers.value("AltitudeMode.kml");
    QTest::newRow("ScreenOverlay_Folder") << parsers.value("ScreenOverlay_Folder.kml");
    QTest::newRow("ScreenOverlay_kml") << parsers.value("ScreenOverlay_kml.kml");
}

void TestGeoDataWriter::saveAndLoad()
{
    //Save the file and then verify loading it again
    QFETCH( QSharedPointer<GeoDataParser>, parser );

    QTemporaryFile tempFile;
    GeoWriter writer;
    //FIXME: a better way to do this?
    writer.setDocumentType( "http://earth.google.com/kml/2.2" );

    // Open file in right mode
    QVERIFY( tempFile.open() );

    QVERIFY( writer.write( &tempFile, &( *dynamic_cast<GeoDataFeature*>(parser->activeDocument() ) ) ) );

    GeoDataParser resultParser( GeoData_KML );

    tempFile.reset();
    QVERIFY( resultParser.read( &tempFile ) );
}

void TestGeoDataWriter::saveAndCompare_data()
{
    QTest::addColumn<QSharedPointer<GeoDataParser> >("parser");
    QTest::addColumn<QString>("original");

    QTest::newRow("NewYork") << parsers.value( "NewYork.kml" ) << "NewYork.kml";
    QTest::newRow("NewYorkDocument") << parsers.value( "NewYorkDocument.kml" ) << "NewYorkDocument.kml";
    QTest::newRow("NetworkLink") << parsers.value( "NetworkLink.kml" ) << "NetworkLink.kml";
    QTest::newRow("NetworkLinkDocument") << parsers.value( "NetworkLinkDocument.kml" ) << "NetworkLinkDocument.kml";
    QTest::newRow("MackyModel") << parsers.value("MackyModel.kml") << "MackyModel.kml";
    QTest::newRow("Tour") << parsers.value("Tour.kml") << "Tour.kml";
    QTest::newRow("AltitudeMode") << parsers.value("AltitudeMode.kml") << "AltitudeMode.kml";
    QTest::newRow("ScreenOverlay_Folder") << parsers.value("ScreenOverlay_Folder.kml") << "ScreenOverlay_Folder.kml";
    QTest::newRow("ScreenOverlay_kml") << parsers.value("ScreenOverlay_kml.kml") << "ScreenOverlay_kml.kml";
}

void TestGeoDataWriter::saveAndCompare()
{
    //save the file and compare it to the original
    QFETCH( QSharedPointer<GeoDataParser>, parser );
    QFETCH( QString, original );

    //attempt to save a file using the GeoWriter
    QTemporaryFile tempFile;

    GeoWriter writer;
    //FIXME: a better way to do this?
    writer.setDocumentType( "http://earth.google.com/kml/2.2" );

    // Open file in right mode
    QVERIFY( tempFile.open() );

    QVERIFY( writer.write( &tempFile, &( *dynamic_cast<GeoDataFeature*>(parser->activeDocument() ) ) ) );

    QFile file( dataDir.filePath( original ) );
    QVERIFY( file.open( QIODevice::ReadOnly ) );
    QVERIFY( tempFile.reset() );
    QTextStream oldFile( &file );
    QTextStream newFile( &tempFile );

    QCOMPARE( newFile.readAll().simplified(), oldFile.readAll().simplified() );
}

void TestGeoDataWriter::cleanupTestCase()
{
    QMap<QString, QSharedPointer<GeoDataParser> >::iterator itpoint = parsers.begin();
    QMap<QString, QSharedPointer<GeoDataParser> >::iterator const endpoint = parsers.end();
    for (; itpoint != endpoint; ++itpoint ) {
        delete itpoint.value()->releaseDocument();
    }
}

QTEST_MAIN( TestGeoDataWriter )
#include "TestGeoDataWriter.moc"

