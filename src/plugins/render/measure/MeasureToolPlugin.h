//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2006-2007 Torsten Rahn     <tackat@kde.org>
// Copyright 2007      Inge Wallin      <ingwa@kde.org>
// Copyright 2011      Michael Henning  <mikehenning@eclipse.net>
//

//
// MeasureToolPlugin enables Marble to set and display measure points
//

#ifndef MARBLE_MEASURETOOLPLUGIN_H
#define MARBLE_MEASURETOOLPLUGIN_H

#include "DialogConfigurationInterface.h"
#include "GeoDataLineString.h"
#include "RenderPlugin.h"
#include "MarbleWidget.h"
#include "MarbleWidgetPopupMenu.h"

#include <QObject>
#include <QFont>
#include <QPen>
#include <QAction>

namespace Ui {
    class MeasureConfigWidget;
}

namespace Marble
{

class MeasureToolPlugin : public RenderPlugin, public DialogConfigurationInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA( IID "org.kde.edu.marble.MeasureToolPlugin" )
    Q_INTERFACES( Marble::RenderPluginInterface )
    Q_INTERFACES( Marble::DialogConfigurationInterface )
    MARBLE_PLUGIN( MeasureToolPlugin )

 public:
    explicit MeasureToolPlugin( const MarbleModel *marbleModel = 0 );

    QStringList backendTypes() const;
    QString renderPolicy() const;
    QStringList renderPosition() const;
    QString name() const;
    QString guiString() const;
    QString nameId() const;

    QString version() const;

    QString description() const;

    QString copyrightYears() const;

    QList<PluginAuthor> pluginAuthors() const;

    QIcon icon () const;

    void initialize ();

    bool isInitialized () const;

    bool render( GeoPainter *painter, ViewportParams *viewport, const QString& renderPos, GeoSceneLayer * layer = 0 );

    QDialog *configDialog();
    QHash<QString,QVariant> settings() const;
    void setSettings( const QHash<QString,QVariant> &settings );

 Q_SIGNALS:
    void  numberOfMeasurePointsChanged( int newNumber );

 public Q_SLOTS:
    bool  eventFilter( QObject *object, QEvent *event );

 private:
    void  drawMeasurePoints( GeoPainter *painter );
    void  drawTotalDistanceLabel( GeoPainter *painter,
                                  qreal totalDistance );
    void  drawSegments( GeoPainter *painter );
    void  addContextItems();
    void  removeContextItems();

 private Q_SLOTS:
    void  setNumberOfMeasurePoints( int number );
    void  addMeasurePointEvent();

    void  addMeasurePoint( qreal lon, qreal lat );
    void  removeLastMeasurePoint();
    void  removeMeasurePoints();

    void writeSettings();

 private:
    Q_DISABLE_COPY( MeasureToolPlugin )

    // The line strings in the distance path.
    GeoDataLineString m_measureLineString;

    const QPixmap m_mark;
    QFont   m_font_regular;
    int     m_fontascent;

    QPen    m_pen;

    QAction *m_addMeasurePointAction;
    QAction *m_removeLastMeasurePointAction;
    QAction *m_removeMeasurePointsAction;
    QAction *m_separator;

    MarbleWidget* m_marbleWidget;

    QDialog * m_configDialog;
    Ui::MeasureConfigWidget * m_uiConfigWidget;
    bool m_showDistanceLabel;
    bool m_showBearingLabel;
};

}

#endif // MARBLE_MEASURETOOLPLUGIN_H
