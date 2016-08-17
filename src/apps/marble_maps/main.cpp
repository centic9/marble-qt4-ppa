//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2015      Gábor Péterffy <peterffy95@gmail.com>
//

#include <QApplication>

#include "QmlView.h"

using namespace Marble;

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);

    QmlView marbleMaps;
    marbleMaps.start();

    return app.exec();
}
