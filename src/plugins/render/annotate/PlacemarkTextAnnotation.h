//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009      Andrew Manson <g.real.ate@gmail.com>
// Copyright 2013      Thibaut Gridel <tgridel@free.fr>
//

#ifndef PLACEMARKTEXTANNOTATION_H
#define PLACEMARKTEXTANNOTATION_H

#include "SceneGraphicsItem.h"

namespace Marble
{

class GeoWidgetBubble;
class TextEditor;

class PlacemarkTextAnnotation : public SceneGraphicsItem
{
public:
    explicit PlacemarkTextAnnotation( GeoDataPlacemark *placemark );
    ~PlacemarkTextAnnotation();

    virtual void paint( GeoPainter *painter, const ViewportParams *viewport );

    /**
     * @brief Provides information for downcasting a SceneGraphicsItem.
     */
    virtual const char *graphicType() const;

private:
    GeoWidgetBubble *bubble;

protected:
    virtual bool mousePressEvent( QMouseEvent *event );
    virtual bool mouseMoveEvent( QMouseEvent *event );
    virtual bool mouseReleaseEvent( QMouseEvent *event );
};

}

#endif // PLACEMARKTEXTANNOTATION_H
