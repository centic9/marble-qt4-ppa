/*
    Copyright (C) 2008 Jens-Michael Hoffmann <jensmh@gmx.de>

    This file is part of the KDE project

    This library is free software you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    aint with this library see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/
#ifndef MARBLE_GEOONFPARSER_H
#define MARBLE_GEOONFPARSER_H

#include <geodata_export.h>
#include "GeoParser.h"

namespace Marble
{

class GeoDocument;

class GEODATA_EXPORT GeoOnfParser : public GeoParser
{
public:
    GeoOnfParser();

private:
    bool isValidRootElement();
    GeoDocument* createDocument() const;
    bool isValidElement(const QString& tagName) const;
};

}

#endif
