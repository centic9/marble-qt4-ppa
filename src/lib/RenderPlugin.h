//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2008 Torsten Rahn <tackat@kde.org>
// Copyright 2008 Inge Wallin  <inge@lysator.liu.se>
//

#ifndef MARBLE_RENDERPLUGIN_H
#define MARBLE_RENDERPLUGIN_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/Qt>
#include <QtGui/QStandardItem>

#include "RenderPluginInterface.h"
#include "marble_export.h"


class QAction;
class QActionGroup;
class QStandardItem;

namespace Marble
{

class RenderPluginPrivate;
class MarbleModel;

/**
 * @short The abstract class that creates a renderable Item.
 *
 */

class MARBLE_EXPORT RenderPlugin : public QObject, public RenderPluginInterface
{
    Q_OBJECT

 public:
    /**
     * This enum contains the data roles for the QStandardItem that is returned by item().
     * TODO: This should get moved into PluginInterface.h
     */
    enum ItemDataRole {
        NameId = Qt::UserRole + 2,       // a QString
        AboutDialogAvailable,            // a bool
        ConfigurationDialogAvailable,    // a bool
        BackendTypes                     // a QStringList
    };

    enum RenderType {
        Unknown,
        Online
    };

    RenderPlugin();
    virtual ~RenderPlugin();

    const MarbleModel* marbleModel() const;
    void  setMarbleModel( const MarbleModel* );

    QAction       *action() const;
    /**
     *This method is used by the main window to get all of the actions that this
     *plugin defines. There is no guarantee where the main window will place the
     *actions but it will generally be in a Menu. The returned QList should
     *also contain all of the actions returned by @see toolbarActions().
     *@return A QList of grouped actions
     */
    virtual QList<QActionGroup*>*   actionGroups() const;

    /**
     *This method returns a subset of the actions returned by @see actions() which
     *are intended to be placed in a more prominent place such as a toolbar above
     *the Marble Widget. You are not guaranteed that they will be in an actual
     *toolbar but they will be visible and discoverable
     *@return A QList of grouped toolbar actions
     */
    virtual QList<QActionGroup*>*   toolbarActionGroups() const;
    
    QStandardItem *item();

    void applyItemState();
    void retrieveItemState();

    bool    enabled() const;
    bool    visible() const;
    
    /**
     * Function for getting a pointer to the about dialog of the plugin.
     *
     * @return: The about dialog or, if no about dialog exists, 0.
     */
    virtual QDialog *aboutDialog();
    /**
     * Function for getting a pointer to the configuration dialog of the plugin.
     *
     * @return: The configuration dialog or, if no configuration dialog exists, 0.
     */
    virtual QDialog *configDialog();

    /**
     * @return: The settings of the item.
     */
    virtual QHash<QString,QVariant> settings() const;

    /**
     * Set the settings of the item.
     */
    virtual void setSettings( QHash<QString,QVariant> settings );

    /**
     * Function for returning the type of plugin this is for.
     * This affects where in the menu tree the action() is placed.
     *
     * @return: The type of render plugin this is.
     */
    virtual RenderType renderType() const;

 public Q_SLOTS:
    void    setEnabled( bool enabled );
    void    setVisible( bool visible );
    void    restoreDefaultSettings();

 Q_SIGNALS:
    /**
     * This signal is emitted if the visibility is changed with setVisible.
     */
    void visibilityChanged( QString nameId, bool visible );
    
    void enabledChanged( bool enable );

    /**
     * This signal is emitted if the settings of the RenderPlugin changed.
     */
    void settingsChanged( QString nameId );

    /**
     * This signal is emitted if the actions that the plugin supports change in
     * any way
     */
    void actionGroupsChanged();

    /**
     * This signal is emitted if an update of the view is needed. If available with the
     * @p dirtyRegion which is the region the view will change in. If dirtyRegion.isEmpty() returns
     * true, the whole viewport has to be repainted.
     */
    void repaintNeeded( QRegion dirtyRegion = QRegion() );

 protected:
    bool eventFilter( QObject *, QEvent * );

 private:
    Q_DISABLE_COPY( RenderPlugin )
    RenderPluginPrivate * const d;
};

#define MARBLE_PLUGIN(T) public:\
    virtual RenderPlugin* newInstance() { return new T(); }
}

#endif
