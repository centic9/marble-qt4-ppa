//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2011 Guillaume Martres <smarter@ubuntu.com>
//

#include "SatellitesConfigLeafItem.h"

#include <QtCore/QVariant>

using namespace Marble;

SatellitesConfigLeafItem::SatellitesConfigLeafItem( const QString &name, const QString &url )
    : SatellitesConfigAbstractItem( name ),
      m_url( url ),
      m_isChecked( false ),
      m_isOrbitDisplayed( false )
{ 
}

SatellitesConfigLeafItem::~SatellitesConfigLeafItem()
{
}

void SatellitesConfigLeafItem::loadSettings( QHash<QString, QVariant> settings )
{
    QStringList tleList = settings.value( "tleList" ).toStringList();
    m_isChecked = tleList.contains( m_url );
}

QVariant SatellitesConfigLeafItem::data( int column, int role ) const
{
    QVariant base = SatellitesConfigAbstractItem::data( column, role );
    if ( base.isValid() ) {
        return base;
    }

    switch ( role ) {
    case UrlListRole:
        return QVariant( QStringList() << m_url );
    case Qt::CheckStateRole:
        switch ( column ) {
        case 0:
            return QVariant( m_isChecked ? Qt::Checked : Qt::Unchecked );
        case 1:
            return QVariant( m_isOrbitDisplayed ? Qt::Checked : Qt::Unchecked );
        }
    }

    return QVariant();
}

bool SatellitesConfigLeafItem::setData( int column, int role, const QVariant& data )
{
    if ( role == Qt::CheckStateRole ) {
        switch ( column ) {
        case 0:
            m_isChecked = data.toBool();
            return true;
        case 1:
            m_isOrbitDisplayed = data.toBool();
            return true;
        }
    }

    return false;
}

bool SatellitesConfigLeafItem::isLeaf() const
{
    return true;
}

SatellitesConfigAbstractItem *SatellitesConfigLeafItem::childAt( int row ) const
{
    Q_UNUSED( row )
    return 0;
}

int SatellitesConfigLeafItem::indexOf( const SatellitesConfigAbstractItem *child ) const
{
    Q_UNUSED( child )
    return -1;
}

int SatellitesConfigLeafItem::childrenCount() const
{
    return 0;
}
