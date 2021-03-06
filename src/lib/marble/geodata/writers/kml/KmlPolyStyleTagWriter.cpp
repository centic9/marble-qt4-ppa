//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2013 Thibaut Gridel <tgridel@free.fr>

#include "KmlPolyStyleTagWriter.h"

#include "GeoDataPolyStyle.h"
#include "GeoDataTypes.h"
#include "GeoWriter.h"
#include "KmlElementDictionary.h"

namespace Marble
{

static GeoTagWriterRegistrar s_writerLineStyle(
    GeoTagWriter::QualifiedName( GeoDataTypes::GeoDataPolyStyleType,
                                 kml::kmlTag_nameSpaceOgc22 ),
    new KmlPolyStyleTagWriter );

KmlPolyStyleTagWriter::KmlPolyStyleTagWriter() : KmlColorStyleTagWriter( kml::kmlTag_PolyStyle )
{
}

bool KmlPolyStyleTagWriter::writeMid( const GeoNode *node, GeoWriter& writer ) const
{
    const GeoDataPolyStyle *style = static_cast<const GeoDataPolyStyle*>( node );

    writer.writeElement( "fill", QString::number( style->fill() ) );
    writer.writeElement( "outline", QString::number( style->outline() ) );

    return true;
}

}
