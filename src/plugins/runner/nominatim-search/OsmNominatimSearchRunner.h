//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2010      Dennis Nienhüser <earthwings@gentoo.org>
//


#ifndef MARBLE_OSMNOMINATIMRUNNER_H
#define MARBLE_OSMNOMINATIMRUNNER_H

#include "SearchRunner.h"

#include <QString>
#include <QHostInfo>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

class QNetworkReply;
class QDomNodeList;

namespace Marble
{

class OsmNominatimRunner : public SearchRunner
{
    Q_OBJECT
public:
    explicit OsmNominatimRunner(QObject *parent = 0);

    ~OsmNominatimRunner();

    void search( const QString &searchTerm, const GeoDataLatLonBox &preferred );

private Q_SLOTS:
    // Forward a result to the search or reverse geocoding handler
    void handleResult( QNetworkReply* );

    // No results (or an error)
    void returnNoResults();

    void startSearch();

private:
    QNetworkAccessManager m_manager;

    QNetworkRequest m_request;
};

}

#endif
