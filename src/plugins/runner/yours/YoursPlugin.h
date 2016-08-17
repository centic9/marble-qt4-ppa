//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2010      Dennis Nienhüser <earthwings@gentoo.org>
//


#ifndef MARBLE_YOURSPLUGIN_H
#define MARBLE_YOURSPLUGIN_H

#include "RunnerPlugin.h"

namespace Marble
{

class YoursPlugin : public RunnerPlugin
{
    Q_OBJECT
    Q_INTERFACES( Marble::RunnerPlugin )

public:
    explicit YoursPlugin( QObject *parent = 0 );

    virtual MarbleAbstractRunner* newRunner() const;

    virtual bool supportsTemplate(RoutingProfilesModel::ProfileTemplate profileTemplate) const;
};

}

#endif
