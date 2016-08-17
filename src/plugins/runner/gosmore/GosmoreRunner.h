//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2010      Dennis Nienhüser <earthwings@gentoo.org>
//


#ifndef MARBLE_GOSMORERUNNER_H
#define MARBLE_GOSMORERUNNER_H

#include "MarbleAbstractRunner.h"
#include "routing/RouteRequest.h"

namespace Marble
{

class GosmoreRunnerPrivate;

class GosmoreRunner : public MarbleAbstractRunner
{
public:
    explicit GosmoreRunner(QObject *parent = 0);

    ~GosmoreRunner();

    // Overriding MarbleAbstractRunner
    GeoDataFeature::GeoDataVisualCategory category() const;

    // Overriding MarbleAbstractRunner
    virtual void retrieveRoute( const RouteRequest *request );

    // Overriding MarbleAbstractRunner
    virtual void reverseGeocoding( const GeoDataCoordinates &coordinates );

private:
    GosmoreRunnerPrivate* const d;
};

}

#endif
