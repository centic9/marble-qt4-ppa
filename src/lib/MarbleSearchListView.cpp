//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2005-2007 Torsten Rahn <tackat@kde.org>
// Copyright 2007      Inge Wallin  <ingwa@kde.org>
//

#include "MarbleSearchListView.h"

#include "MarbleDebug.h"
#include <QtGui/QStandardItemModel>

using namespace Marble;

MarbleSearchListView::MarbleSearchListView(QWidget* parent)
    : QListView( parent ),
      d( 0 )
{
}


void MarbleSearchListView::selectItem(const QString& text)
{
    if ( text.isEmpty() ) {
        clearSelection();
        scrollToTop();
        emit activated( QModelIndex() );
        return;
    }

    QModelIndexList  resultlist;

    if ( model() )
    {
        QModelIndex firstIndex = model()->index( 0, 0 );
        resultlist = model()->match( firstIndex,
                                     Qt::DisplayRole, text, 1,
                                     Qt::MatchStartsWith );
    }

    if ( resultlist.size() > 0 ) {
        setCurrentIndex( resultlist[0] );
        scrollTo( resultlist[0] );
    }
    else
        mDebug() << "noitem!";
}


void MarbleSearchListView::activate()
{
    if ( selectedIndexes().size() > 0 )
        emit activated( currentIndex() );
}


#include "MarbleSearchListView.moc"
