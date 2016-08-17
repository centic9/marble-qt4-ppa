// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2011 Dennis Nienhüser <earthwings@gentoo.org>
// Copyright 2011 Daniel Marth <danielmarth@gmx.at>

import QtQuick 1.0
import com.nokia.meego 1.0
import org.kde.edu.marble 0.11
import org.kde.edu.marble.qtcomponents 0.12

/*
 * Page for the virtual globe activity.
 */
Page {
    id: virtualGlobeActivityPage
    anchors.fill: parent

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back";
            onClicked: pageStack.pop()
        }
        ToolButton {
            id: searchButton
            checkable: true
            width: 60
            iconSource: "image://theme/icon-m-toolbar-search";
        }
    }

    Column {
        width: parent.width
        height: parent.height

        SearchField {
            id: searchField
            width: parent.width
            visible: searchButton.checked
            onSearch: {
                searchField.busy = true
                marbleWidget.find( term )
            }

            Component.onCompleted: {
                marbleWidget.getSearch().searchFinished.connect( searchFinished )
            }

            function searchFinished() {
                searchField.busy = false
            }
        }

        Item {
            id: mapContainer
            width: parent.width
            height: parent.height - searchField.height

            function embedMarbleWidget() {
                marbleWidget.parent = mapContainer
                settings.projection = "Spherical"
                settings.activeRenderPlugins = settings.defaultRenderPlugins
                settings.mapTheme = "earth/srtm/srtm.dgml"
                settings.gpsTracking = false
                settings.showPosition = false
                settings.showTrack = false
                marbleWidget.visible = true
            }

            Component.onDestruction: {
                if ( marbleWidget.parent === mapContainer ) {
                    marbleWidget.parent = null
                    marbleWidget.visible = false
                }
            }
        }
    }

    onStatusChanged: {
        if ( status === PageStatus.Activating ) {
            mapContainer.embedMarbleWidget()
        }
    }
}
