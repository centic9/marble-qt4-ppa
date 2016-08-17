//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2013       Adrian Draghici <draghici.adrian.b@gmail.com>
//

#include "KmlPlaylistTagWriter.h"

#include "GeoDataPlaylist.h"
#include "GeoDataTypes.h"
#include "GeoWriter.h"
#include "KmlElementDictionary.h"

namespace Marble
{

static GeoTagWriterRegistrar s_writerPlaylist(
        GeoTagWriter::QualifiedName( GeoDataTypes::GeoDataPlaylistType,
                                     kml::kmlTag_nameSpace22 ),
        new KmlPlaylistTagWriter );

bool KmlPlaylistTagWriter::write( const GeoNode *node, GeoWriter& writer ) const
{
    const GeoDataPlaylist *playlist = static_cast<const GeoDataPlaylist*>( node );

    writer.writeStartElement( "gx:Playlist" );

    for ( int i = 0; i < playlist->size(); i++ ) {
        writeTourPrimitive( playlist->primitive( i ), writer );
    }

    writer.writeEndElement();

    return true;
}

void KmlPlaylistTagWriter::writeTourPrimitive( const GeoNode *primitive, GeoWriter& writer ) const
{

    if ( primitive->nodeType() == GeoDataTypes::GeoDataTourControlType ) {
        writeTourControl( static_cast<const GeoDataTourControl*>( primitive ), writer );
    }
    else if ( primitive->nodeType() == GeoDataTypes::GeoDataWaitType ) {
        writeWait( static_cast<const GeoDataWait*>( primitive ), writer );
    }
    else if ( primitive->nodeType() == GeoDataTypes::GeoDataFlyToType ) {
        writeElement( primitive, writer );
    }
    else if ( primitive->nodeType() == GeoDataTypes::GeoDataSoundCueType ) {
        writeSoundCue( static_cast<const GeoDataSoundCue*>(primitive), writer );
    }
}

void KmlPlaylistTagWriter::writeTourControl( const GeoDataTourControl* tourControl, GeoWriter& writer ) const
{
    writer.writeStartElement( kml::kmlTag_TourControl );
    if ( !tourControl->id().isEmpty() ) {
        writer.writeAttribute( "id", tourControl->id() );
    }

    writer.writeElement( kml::kmlTag_playMode, playModeToString( tourControl->playMode() ) );

    writer.writeEndElement();
}

void KmlPlaylistTagWriter::writeWait( const GeoDataWait* wait, GeoWriter& writer ) const
{
    writer.writeStartElement( kml::kmlTag_nameSpaceGx22, kml::kmlTag_Wait );
    if ( !wait->id().isEmpty() ) {
        writer.writeAttribute( "id", wait->id() );
    }

    writer.writeElement( kml::kmlTag_nameSpaceGx22, kml::kmlTag_duration, QString::number( wait->duration() ) );

    writer.writeEndElement();
}

void KmlPlaylistTagWriter::writeSoundCue(const GeoDataSoundCue *cue, GeoWriter &writer) const
{
    writer.writeStartElement( kml::kmlTag_nameSpaceGx22, kml::kmlTag_SoundCue );
    if (!cue->id().isEmpty()) {
        writer.writeAttribute( "id", cue->id() );
    }

    writer.writeElement( kml::kmlTag_href, cue->href() );
    writer.writeElement( kml::kmlTag_nameSpaceGx22, kml::kmlTag_delayedStart,
                         QString::number(cue->delayedStart()) );

    writer.writeEndElement();
}

QString KmlPlaylistTagWriter::playModeToString( GeoDataTourControl::PlayMode playMode ) const
{
    switch (playMode)
    {
    case GeoDataTourControl::Play:   return "play";
    case GeoDataTourControl::Pause:  return "pause";
    default:                         return "";
    }
}

}
