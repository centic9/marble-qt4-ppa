//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2011 Utku Aydın <utkuaydin34@gmail.com>
//

#include "DgmlDocumentTagWriter.h"

#include "GeoWriter.h"
#include "GeoSceneDocument.h"
#include "GeoSceneHead.h"
#include "GeoSceneMap.h"
#include "GeoSceneSettings.h"
#include "GeoSceneLegend.h"
#include "DgmlElementDictionary.h"

namespace Marble
{

static GeoTagWriterRegistrar s_writerDocument( GeoTagWriter::QualifiedName( "GeoSceneDocument", dgml::dgmlTag_nameSpace20 ),
                                               new DgmlDocumentTagWriter() );

bool DgmlDocumentTagWriter::write( const GeoNode *node, GeoWriter& writer ) const
{
    const GeoSceneDocument *document = static_cast<const GeoSceneDocument*>( node );
    
    writer.writeStartElement( dgml::dgmlTag_Document );
    
    const GeoSceneHead *head = document->head();
    writeElement( head, writer );
    
    const GeoSceneMap *map = document->map() ;
    writeElement( map, writer );
    
    const GeoSceneSettings *settings = document->settings();
    writeElement( settings, writer );
    
    const GeoSceneLegend *legend = document->legend();
    writeElement( legend, writer );
    
    writer.writeEndDocument();
    return true;
}

}
