//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009       Andrew Manson           <g.real.ate@gmail.com>
// Copyright 2013       Thibaut Gridel          <tgridel@free.fr>
// Copyright 2014       Calin-Cristian Cruceru  <crucerucalincristian@gmail.com>
//


#ifndef MARBLE_ANNOTATEPLUGIN_H
#define MARBLE_ANNOTATEPLUGIN_H

#include "RenderPlugin.h"
#include "SceneGraphicsItem.h"
#include "GeoDataLatLonBox.h"
#include "GeoDataGroundOverlay.h"
#include "GeoDataPolygon.h"
#include "GroundOverlayFrame.h"
#include "AreaAnnotation.h"

#include <QObject>
#include <QErrorMessage>
#include <QMenu>
#include <QSortFilterProxyModel>


class QNetworkAccessManager;
class QNetworkReply;

namespace Marble
{

class MarbleWidget;
class TextureLayer;
class PlacemarkTextAnnotation;
class GeoDataDocument;
class GeoDataLinearRing;
class GeoDataLineString;


/**
 * @brief This class specifies the Marble layer interface of a plugin which
 * annotates maps with polygons and placemarks.
 */
class AnnotatePlugin :  public RenderPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA( IID "org.kde.edu.marble.AnnotatePlugin" )
    Q_INTERFACES( Marble::RenderPluginInterface )
    MARBLE_PLUGIN( AnnotatePlugin )

public:
    explicit AnnotatePlugin(const MarbleModel *model = 0);
    virtual ~AnnotatePlugin();

    QStringList backendTypes() const;

    QString renderPolicy() const;

    QStringList renderPosition() const;

    QString name() const;

    QString guiString() const;

    QString nameId() const;

    QString version() const;

    QString description() const;

    QIcon icon () const;

    QString copyrightYears() const;

    QList<PluginAuthor> pluginAuthors() const;

    void initialize ();

    bool isInitialized () const;

    virtual QString runtimeTrace() const;

    virtual const QList<QActionGroup*> *actionGroups() const;
    virtual const QList<QActionGroup*> *toolbarActionGroups() const;

    bool render( GeoPainter *painter, ViewportParams *viewport,
                 const QString &renderPos, GeoSceneLayer *layer = 0 );

signals:
    void placemarkAdded();
    void overlayAdded();
    void itemRemoved();

public slots:
    void enableModel( bool enabled );

    void setAddingPlacemark( bool );
    void setDrawingPolygon( bool );
    void setAddingPolygonHole( bool );
    void setMergingNodes( bool );
    void setAddingOverlay( bool );
    void setRemovingItems( bool );

    void addOverlay();

    //    void receiveNetworkReply( QNetworkReply* );
    //    void downloadOsmFile();

    void clearAnnotations();
    void saveAnnotationFile();
    void loadAnnotationFile();


private slots:
    void editOverlay();
    void removeOverlay();
    void updateOverlayFrame( GeoDataGroundOverlay *overlay );

    void editPolygon();
    void removePolygon();
    void selectNode();
    void deleteNode();
    void unselectNodes();
    void deleteSelectedNodes();


protected:
    bool eventFilter( QObject *watched, QEvent *event );

private:
    void setupActions( MarbleWidget *marbleWidget );

    void setupGroundOverlayModel();
    void setupOverlayRmbMenu();
    void showOverlayRmbMenu( GeoDataGroundOverlay *overlay, qreal x, qreal y );
    void displayOverlayEditDialog( GeoDataGroundOverlay *overlay );
    void displayPolygonEditDialog( GeoDataPlacemark *placemark );
    void displayOverlayFrame( GeoDataGroundOverlay *overlay );
    void clearOverlayFrames();

    void setupPolygonRmbMenu();
    void setupNodeRmbMenu();
    void showPolygonRmbMenu( AreaAnnotation *selectedArea, qreal x, qreal y );
    void showNodeRmbMenu( AreaAnnotation *area, qreal x, qreal y );


    void handleUncaughtEvents( QMouseEvent *mouseEvent );
    void handleReleaseOverlay( QMouseEvent *mouseEvent );

    bool handleAddingPlacemark( QMouseEvent *mouseEvent );
    bool handleAddingPolygon( QMouseEvent *mouseEvent );
    bool handleMovingSelectedItem( QMouseEvent *mouseEvent );

    bool handleMousePressEvent( QMouseEvent *mouseEvent, SceneGraphicsItem *item );
    bool handleMouseReleaseEvent( QMouseEvent *mouseEvent, SceneGraphicsItem *item );

    bool handleRemovingItem( QMouseEvent *mouseEvent, SceneGraphicsItem *item );
    bool handleAddingHole( QMouseEvent *mouseEvent, SceneGraphicsItem *item );
    bool handleMergingNodes( QMouseEvent *mouseEvent, SceneGraphicsItem *item );
    bool handleShowingRmbMenus( QMouseEvent *mouseEvent, SceneGraphicsItem *item );


    //    void readOsmFile( QIODevice* device, bool flyToFile );

    bool m_widgetInitialized;
    MarbleWidget *m_marbleWidget;

    QMenu *m_overlayRmbMenu;
    QMenu *m_polygonRmbMenu;
    QMenu *m_nodeRmbMenu;

    QList<QActionGroup*>    m_actions;
    QList<QActionGroup*>    m_toolbarActions;
    QSortFilterProxyModel   m_groundOverlayModel;
    QMap<GeoDataGroundOverlay*, SceneGraphicsItem*> m_groundOverlayFrames;

    GeoDataDocument*          m_annotationDocument;
    QList<SceneGraphicsItem*> m_graphicsItems;

    GeoDataPlacemark     *m_polygonPlacemark;
    SceneGraphicsItem    *m_movedItem;
    GeoDataGroundOverlay *m_rmbOverlay;
    AreaAnnotation       *m_rmbSelectedArea;
    GeoDataPolygon       *m_holedPolygon;

    AreaAnnotation       *m_mergedArea;
    int                   m_mergedNodeIndex;

    //    QNetworkAccessManager* m_networkAccessManager;
    //    QErrorMessage m_errorMessage;

    bool m_addingPlacemark;
    bool m_drawingPolygon;
    bool m_addingPolygonHole;
    bool m_mergingNodes;
    bool m_addingOverlay;
    bool m_removingItem;
    bool m_isInitialized;
};


}

#endif // MARBLE_ANNOTATEPLUGIN_H
