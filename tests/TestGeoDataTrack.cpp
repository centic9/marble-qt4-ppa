//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2011      Niko Sams <niko.sams@gmail.com>
//

#include <QtCore/QObject>
#include <QtTest/QtTest>

#include "GeoDataPoint.h"
#include "GeoDataLinearRing.h"
#include <GeoDataParser.h>
#include <GeoDataDocument.h>
#include <GeoDataPlacemark.h>
#include <MarbleDebug.h>
#include <GeoDataFolder.h>
#include <GeoDataTrack.h>

using namespace Marble;


class TestGeoDataTrack : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void parseTest();
};

void TestGeoDataTrack::initTestCase()
{
    MarbleDebug::enable = true;
}

void TestGeoDataTrack::parseTest()
{
    //"Simple Example" from kmlreference
    QString content(
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
"<kml xmlns=\"http://www.opengis.net/kml/2.2\""
" xmlns:gx=\"http://www.google.com/kml/ext/2.2\">"
"<Folder>"
"  <Placemark>"
"    <gx:Track>"
"      <when>2010-05-28T02:02:09Z</when>"
"      <when>2010-05-28T02:02:35Z</when>"
"      <when>2010-05-28T02:02:44Z</when>"
"      <when>2010-05-28T02:02:53Z</when>"
"      <when>2010-05-28T02:02:54Z</when>"
"      <when>2010-05-28T02:02:55Z</when>"
"      <when>2010-05-28T02:02:56Z</when>"
"      <gx:coord>-122.207881 37.371915 156.000000</gx:coord>"
"      <gx:coord>-122.205712 37.373288 152.000000</gx:coord>"
"      <gx:coord>-122.204678 37.373939 147.000000</gx:coord>"
"      <gx:coord>-122.203572 37.374630 142.199997</gx:coord>"
"      <gx:coord>-122.203451 37.374706 141.800003</gx:coord>"
"      <gx:coord>-122.203329 37.374780 141.199997</gx:coord>"
"      <gx:coord>-122.203207 37.374857 140.199997</gx:coord>"
"    </gx:Track>"
"  </Placemark>"
"</Folder>"
"</kml>" );

    GeoDataParser parser( GeoData_KML );

    QByteArray array( content.toUtf8() );
    QBuffer buffer( &array );
    buffer.open( QIODevice::ReadOnly );
    qDebug() << "Buffer content:" << endl << buffer.buffer();
    if ( !parser.read( &buffer ) ) {
        qWarning( "Could not parse data!" );
        QFAIL( "Could not parse data!" );
        return;
    }
    GeoDocument* document = parser.releaseDocument();
    QVERIFY( document );
    GeoDataDocument *dataDocument = static_cast<GeoDataDocument*>( document );
    GeoDataFolder *folder = dataDocument->folderList().at( 0 );
    QCOMPARE( folder->placemarkList().size(), 1 );
    GeoDataPlacemark* placemark = folder->placemarkList().at( 0 );
    QCOMPARE( placemark->geometry()->geometryId(), GeoDataTrackId );
    GeoDataTrack* track = static_cast<GeoDataTrack*>( placemark->geometry() );
    QCOMPARE( track->size(), 7 );
    {
        QDateTime when = track->whenList().at( 0 );
        QCOMPARE( when, QDateTime( QDate( 2010, 5, 28 ), QTime( 2, 2, 9 ), Qt::UTC ) );
    }
    {
        GeoDataCoordinates coord = track->coordinatesList().at( 0 );
        QCOMPARE( coord.longitude( GeoDataCoordinates::Degree ), -122.207881 );
        QCOMPARE( coord.latitude( GeoDataCoordinates::Degree ), 37.371915 );
        QCOMPARE( coord.altitude(), 156.000000 );
    }
    {
        GeoDataCoordinates coord = track->coordinatesAt( QDateTime( QDate( 2010, 5, 28 ), QTime( 2, 2, 9 ), Qt::UTC ) );
        QCOMPARE( coord.longitude( GeoDataCoordinates::Degree ), -122.207881 );
        QCOMPARE( coord.latitude( GeoDataCoordinates::Degree ), 37.371915 );
        QCOMPARE( coord.altitude(), 156.000000 );
    }

    delete document;

}

QTEST_MAIN( TestGeoDataTrack )

#include "TestGeoDataTrack.moc"

