//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009      Andrew Manson <g.real.ate@gmail.com>
//
#include "AreaAnnotation.h"
#include "GeoPainter.h"


namespace Marble
{



AreaAnnotation::AreaAnnotation()
{
}

void AreaAnnotation::setGeometry( GeoDataPolygon g )
{
    m_geo = g;
}

void AreaAnnotation::paint(GeoPainter *painter, ViewportParams *viewport,
                           const QString &renderPos, GeoSceneLayer *layer )
{
    Q_UNUSED(viewport);
    Q_UNUSED(renderPos);
    Q_UNUSED(layer);

    painter->save();

    painter->setBrush( QBrush( QColor( 0, 255, 255, 80 )  ) );
    painter->drawPolygon( m_geo );

    painter->restore();

}

}
