//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2007      Murad Tagirov <tmurad@gmail.com>
// Copyright 2009      Patrick Spendrin <ps_ml@gmx.de>
//


#include "GeoDataFeature.h"
#include "GeoDataFeature_p.h"

#include <QtCore/QDataStream>
#include <QtCore/QSize>
#include <QtGui/QPixmap>

#include "MarbleDirs.h"
#include "MarbleDebug.h"

#include "GeoDataStyle.h"
#include "GeoDataStyleMap.h"

#include "GeoDataContainer.h"
#include "GeoDataDocument.h"
#include "GeoDataFolder.h"
#include "GeoDataPlacemark.h"
#include "GeoDataRegion.h"


namespace Marble
{
QFont GeoDataFeature::s_defaultFont = QFont("Sans Serif");

bool GeoDataFeature::s_defaultStyleInitialized = false;
GeoDataStyle* GeoDataFeature::s_defaultStyle[GeoDataFeature::LastIndex];


GeoDataFeature::GeoDataFeature()
    :d( new GeoDataFeaturePrivate() )
{
    d->ref.ref();
}

GeoDataFeature::GeoDataFeature( const GeoDataFeature& other )
    : GeoDataObject( other ),
      d( other.d )
{
    d->ref.ref();
}

GeoDataFeature::GeoDataFeature( const QString& name )
    : d( new GeoDataFeaturePrivate() )
{
    d->ref.ref();
    d->m_name = name;
}

GeoDataFeature::GeoDataFeature( GeoDataFeaturePrivate *priv ) 
    : d( priv )
{
    d->ref.ref();
}
    
GeoDataFeature::~GeoDataFeature()
{
    if (!d->ref.deref()) {
        delete d;
    }
}

GeoDataFeaturePrivate* GeoDataFeature::p() const
{
    return static_cast<GeoDataFeaturePrivate*>(d);
}

GeoDataFeature& GeoDataFeature::operator=( const GeoDataFeature& other )
{
    GeoDataObject::operator=( other );
    
    if (!d->ref.deref()) {
        delete d;
    }

    d = other.d;
    d->ref.ref();
    
    return *this;
}

const char* GeoDataFeature::nodeType() const
{
    return p()->nodeType();
}

EnumFeatureId GeoDataFeature::featureId() const
{
    return d->featureId();
}

void GeoDataFeature::initializeDefaultStyles()
{
    // We need to do this similar to the way KCmdLineOptions works in
    // the future: Having a PlacemarkStyleProperty properties[] would
    // help here greatly.

    QString defaultFamily = s_defaultFont.family();

#ifdef Q_OS_MACX
    int defaultSize = 10;
#else
    int defaultSize = 8;
#endif

    s_defaultStyle[None]
        = new GeoDataStyle( QPixmap(),
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[Default]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/default_location.png" ) ),
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[Unknown]
        = new GeoDataStyle( QPixmap(),
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[SmallCity]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_4_white.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[SmallCountyCapital]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_4_yellow.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[SmallStateCapital]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_4_orange.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, true  ), QColor( Qt::black ) );

    s_defaultStyle[SmallNationCapital]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_4_red.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[MediumCity]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_3_white.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[MediumCountyCapital]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_3_yellow.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[MediumStateCapital]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_3_orange.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, true  ), QColor( Qt::black ) );

    s_defaultStyle[MediumNationCapital]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_3_red.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[BigCity]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_2_white.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[BigCountyCapital]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_2_yellow.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[BigStateCapital]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_2_orange.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, true  ), QColor( Qt::black ) );

    s_defaultStyle[BigNationCapital]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_2_red.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[LargeCity]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_1_white.png" ) ), 
              QFont( defaultFamily, defaultSize, 75, false ), QColor( Qt::black ) );

    s_defaultStyle[LargeCountyCapital]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_1_yellow.png" ) ), 
              QFont( defaultFamily, defaultSize, 75, false ), QColor( Qt::black ) );

    s_defaultStyle[LargeStateCapital]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_1_orange.png" ) ), 
              QFont( defaultFamily, defaultSize, 75, true  ), QColor( Qt::black ) );

    s_defaultStyle[LargeNationCapital]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/city_1_red.png" ) ), 
              QFont( defaultFamily, defaultSize, 75, false ), QColor( Qt::black ) );

    s_defaultStyle[Nation]
        = new GeoDataStyle( QPixmap(), 
              QFont( defaultFamily, (int)(defaultSize * 1.2 ), 75, false ), QColor( "#404040" ) );
    // Align area labels centered
    s_defaultStyle[Nation]->labelStyle().setAlignment( GeoDataLabelStyle::Center );

    s_defaultStyle[Mountain]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/mountain_1.png" ) ), 
              QFont( defaultFamily, (int)(defaultSize * 0.9 ), 50, false ), QColor( Qt::black ) );

    s_defaultStyle[Volcano]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/volcano_1.png" ) ), 
              QFont( defaultFamily, (int)(defaultSize * 0.9 ), 50, false ), QColor( Qt::black ) );

    s_defaultStyle[Mons]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/mountain_1.png" ) ), 
              QFont( defaultFamily, (int)(defaultSize * 0.9 ), 50, false ), QColor( Qt::black ) );

    s_defaultStyle[Valley]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/valley.png" ) ), 
              QFont( defaultFamily, (int)(defaultSize * 0.9 ), 50, false ), QColor( Qt::black ) );

    s_defaultStyle[Continent]
        = new GeoDataStyle( QPixmap(), 
              QFont( defaultFamily, (int)(defaultSize * 1.7 ), 50, false ), QColor( "#bf0303" ) );
    // Align area labels centered
    s_defaultStyle[Continent]->labelStyle().setAlignment( GeoDataLabelStyle::Center );

    s_defaultStyle[Ocean]
        = new GeoDataStyle( QPixmap(), 
              QFont( defaultFamily, (int)(defaultSize * 1.7 ), 50, true ), QColor( "#2c72c7" ) );
    // Align area labels centered
    s_defaultStyle[Ocean]->labelStyle().setAlignment( GeoDataLabelStyle::Center );

    s_defaultStyle[OtherTerrain]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/other.png" ) ), 
              QFont( defaultFamily, (int)(defaultSize * 0.9 ), 50, false ), QColor( Qt::black ) );

    s_defaultStyle[Crater]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/crater.png" ) ), 
              QFont( defaultFamily, (int)(defaultSize * 0.9 ), 50, false ), QColor( Qt::black ) );

    s_defaultStyle[Mare]
        = new GeoDataStyle( QPixmap(), 
              QFont( defaultFamily, (int)(defaultSize * 1.7 ), 50, false ), QColor( "#bf0303" ) );
    // Align area labels centered
    s_defaultStyle[Mare]->labelStyle().setAlignment( GeoDataLabelStyle::Center );

    s_defaultStyle[GeographicPole]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/pole_1.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[MagneticPole]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/pole_2.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[ShipWreck]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/shipwreck.png" ) ), 
              QFont( defaultFamily, (int)(defaultSize * 0.8 ), 50, false ), QColor( Qt::black ) );

    s_defaultStyle[AirPort]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/airport.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[Observatory]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/observatory.png" ) ),
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[Wikipedia]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/wikipedia.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[OsmSite]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/osm.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[Coordinate]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/coordinate.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );


    s_defaultStyle[MannedLandingSite]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/manned_landing.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[RoboticRover]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/robotic_rover.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[UnmannedSoftLandingSite]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/unmanned_soft_landing.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[UnmannedHardLandingSite]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/unmanned_hard_landing.png" ) ), 
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[Folder]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/folder.png" ) ),
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    s_defaultStyle[Bookmark]
        = new GeoDataStyle( QPixmap( MarbleDirs::path( "bitmaps/bookmark.png" ) ),
              QFont( defaultFamily, defaultSize, 50, false ), QColor( Qt::black ) );

    QFont const osmFont( defaultFamily, defaultSize, 50, false );
    s_defaultStyle[AccomodationCamping]      = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "accommodation_camping.p.16" );
    s_defaultStyle[AccomodationHostel]       = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "accommodation_hostel.p.16" );
    s_defaultStyle[AccomodationHotel]        = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "accommodation_hotel2.p.16" );
    s_defaultStyle[AccomodationMotel]        = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "accommodation_motel.p.16" );
    s_defaultStyle[AccomodationYouthHostel]  = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "accommodation_youth_hostel.p.16" );
    s_defaultStyle[AmenityLibrary]           = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "amenity_library.p.16" );
    s_defaultStyle[EducationCollege]         = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "education_college.p.16" );
    s_defaultStyle[EducationSchool]          = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "education_school.p.16" );
    s_defaultStyle[EducationUniversity]      = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "education_university.p.16" );
    s_defaultStyle[FoodBar]                  = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "food_bar.p.16" );
    s_defaultStyle[FoodBiergarten]           = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "food_biergarten.p.16" );
    s_defaultStyle[FoodCafe]                 = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "food_cafe.p.16" );
    s_defaultStyle[FoodFastFood]             = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "food_fastfood2.p.16" );
    s_defaultStyle[FoodPub]                  = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "food_pub.p.16" );
    s_defaultStyle[FoodRestaurant]           = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "food_restaurant.p.16" );
    s_defaultStyle[HealthDoctors]            = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "health_doctors2.p.16" );
    s_defaultStyle[HealthHospital]           = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "health_hospital.p.16" );
    s_defaultStyle[HealthPharmacy]           = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "health_pharmacy.p.16" );
    s_defaultStyle[MoneyBank]                = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "money_bank2.p.16" );
    s_defaultStyle[ShoppingBeverages]        = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "shopping_alcohol.p.16" );
    s_defaultStyle[ShoppingHifi]             = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "shopping_hifi.p.16" );
    s_defaultStyle[ShoppingSupermarket]      = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "shopping_supermarket.p.16" );
    s_defaultStyle[TouristAttraction]        = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "tourist_attraction.p.16" );
    s_defaultStyle[TouristCastle]            = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "tourist_castle2.p.16" );
    s_defaultStyle[TouristCinema]            = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "tourist_cinema.p.16" );
    s_defaultStyle[TouristMonument]          = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "tourist_monument.p.16" );
    s_defaultStyle[TouristMuseum]            = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "tourist_museum.p.16" );
    s_defaultStyle[TouristRuin]              = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "tourist_ruin.p.16" );
    s_defaultStyle[TouristTheatre]           = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "tourist_theatre.p.16" );
    s_defaultStyle[TouristThemePark]         = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "tourist_theme_park.p.16" );
    s_defaultStyle[TouristViewPoint]         = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "tourist_view_point.p.16" );
    s_defaultStyle[TouristZoo]               = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "tourist_zoo.p.16" );
    s_defaultStyle[TransportAerodrome]       = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "transport_aerodrome.p.16" );
    s_defaultStyle[TransportAirportTerminal] = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "transport_airport_terminal.p.16" );
    s_defaultStyle[TransportBusStation]      = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "transport_bus_station.p.16" );
    s_defaultStyle[TransportBusStop]         = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "transport_bus_stop.p.16" );
    s_defaultStyle[TransportCarShare]        = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "transport_car_share.p.16" );
    s_defaultStyle[TransportFuel]            = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "transport_fuel.p.16" );
    s_defaultStyle[TransportParking]         = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "transport_parking.p.16", "#F6EEB6", QColor( "#F6EEB6" ).darker() );
    s_defaultStyle[TransportTrainStation]    = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "transport_train_station.p.16" );
    s_defaultStyle[TransportTramStop]        = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "transport_tram_stop.p.16" );
    s_defaultStyle[TransportRentalBicycle]   = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "transport_rental_bicycle.p.16" );
    s_defaultStyle[TransportRentalCar]       = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "transport_rental_car.p.16" );
    s_defaultStyle[TransportTaxiRank]        = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "transport_taxi_rank.p.16" );
    s_defaultStyle[ReligionPlaceOfWorship]   = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "place_of_worship_unknown3.p.16" );
    s_defaultStyle[ReligionBahai]            = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "place_of_worship_bahai3.p.16" );
    s_defaultStyle[ReligionBuddhist]         = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "place_of_worship_buddhist3.p.16" );
    s_defaultStyle[ReligionChristian]        = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "place_of_worship_christian3.p.16" );
    s_defaultStyle[ReligionHindu]            = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "place_of_worship_hindu3.p.16" );
    s_defaultStyle[ReligionJain]             = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "place_of_worship_jain3.p.16" );
    s_defaultStyle[ReligionJewish]           = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "place_of_worship_jewish3.p.16" );
    s_defaultStyle[ReligionShinto]           = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "place_of_worship_shinto3.p.16" );
    s_defaultStyle[ReligionSikh]             = GeoDataFeaturePrivate::createOsmPOIStyle( osmFont, "place_of_worship_sikh3.p.16" );
    
    s_defaultStyle[HighwaySteps]             = GeoDataFeaturePrivate::createStyle( 1, 5, "#F98072", "#F98072", true, true, 
                                                                                   Qt::SolidPattern, Qt::CustomDashLine, Qt::FlatCap, 
                                                                                   false, QVector< qreal >() << 0.2 << 0.2 );

    s_defaultStyle[HighwayUnknown]           = GeoDataFeaturePrivate::createHighwayStyle( "#808080" );
    s_defaultStyle[HighwayPath]              = GeoDataFeaturePrivate::createHighwayStyle( "#F98072", 1.0, 2, Qt::DashLine );
    s_defaultStyle[HighwayTrack]             = GeoDataFeaturePrivate::createHighwayStyle( "#986600", 1.0, 3, Qt::DashLine );
    s_defaultStyle[HighwayPedestrian]        = GeoDataFeaturePrivate::createHighwayStyle( "#F98072", 1.0, 2, Qt::DashLine );
    s_defaultStyle[HighwayService]           = GeoDataFeaturePrivate::createHighwayStyle( "#FEFEFE", 1.0, 6 );
    s_defaultStyle[HighwayRoad]              = GeoDataFeaturePrivate::createHighwayStyle( "#FEFEFE", 1.5, 9 );
    s_defaultStyle[HighwayTertiary]          = GeoDataFeaturePrivate::createHighwayStyle( "#FEFEB3", 2.0, 11 );
    s_defaultStyle[HighwaySecondary]         = GeoDataFeaturePrivate::createHighwayStyle( "#FDD6A4", 2.0, 13 );
    s_defaultStyle[HighwayPrimary]           = GeoDataFeaturePrivate::createHighwayStyle( "#EB989A", 3.0, 15 );
    s_defaultStyle[HighwayTrunk]             = GeoDataFeaturePrivate::createHighwayStyle( "#A9DAA9", 3.0, 18 );
    s_defaultStyle[HighwayMotorway]          = GeoDataFeaturePrivate::createHighwayStyle( "#809BC0", 3.0, 20 );
    
    s_defaultStyle[HighwayTertiaryLink]      = GeoDataFeaturePrivate::createHighwayStyle( "#FEFEB3", 2.0, 9 );
    s_defaultStyle[HighwaySecondaryLink]     = GeoDataFeaturePrivate::createHighwayStyle( "#FDD6A4", 2.0, 11 );
    s_defaultStyle[HighwayPrimaryLink]       = GeoDataFeaturePrivate::createHighwayStyle( "#EB989A", 2.0, 13 );
    s_defaultStyle[HighwayTrunkLink]         = GeoDataFeaturePrivate::createHighwayStyle( "#A9DAA9", 3.0, 15 );
    s_defaultStyle[HighwayMotorwayLink]      = GeoDataFeaturePrivate::createHighwayStyle( "#809BC0", 3.0, 18 );
    
    s_defaultStyle[NaturalWater]             = GeoDataFeaturePrivate::createStyle( 2, 10, "#B5D0D0", "#B5D0D0", 
                                                                                   true, true, Qt::SolidPattern, Qt::SolidLine, Qt::RoundCap, false );
    s_defaultStyle[NaturalWood]              = GeoDataFeaturePrivate::createWayStyle( "#8DC46C", "#8DC46C" );
    
    s_defaultStyle[LeisurePark]              = GeoDataFeaturePrivate::createWayStyle( "#CDF6CA", "#CDF6CA" );
    
    s_defaultStyle[LanduseAllotments]        = GeoDataFeaturePrivate::createWayStyle( "#E4C6AA", "#E4C6AA" );
    s_defaultStyle[LanduseBasin]             = GeoDataFeaturePrivate::createWayStyle( QColor(0xB5, 0xD0, 0xD0, 0x80 ), QColor( 0xB5, 0xD0, 0xD0 ) );
    s_defaultStyle[LanduseCemetery]          = GeoDataFeaturePrivate::createWayStyle( "#A9C9AE", "#A9C9AE" );
    s_defaultStyle[LanduseCommercial]        = GeoDataFeaturePrivate::createWayStyle( Qt::transparent, Qt::transparent, false, false );
    s_defaultStyle[LanduseConstruction]      = GeoDataFeaturePrivate::createWayStyle( Qt::transparent, Qt::transparent, false, false );
    s_defaultStyle[LanduseFarmland]          = GeoDataFeaturePrivate::createWayStyle( Qt::transparent, Qt::transparent, false, false );
    s_defaultStyle[LanduseFarmyard]          = GeoDataFeaturePrivate::createWayStyle( Qt::transparent, Qt::transparent, false, false );
    s_defaultStyle[LanduseGarages]           = GeoDataFeaturePrivate::createWayStyle( "#E0DDCD", "#E0DDCD" );
    s_defaultStyle[LanduseGrass]             = GeoDataFeaturePrivate::createWayStyle( "#A8C8A5", "#A8C8A5" );
    s_defaultStyle[LanduseIndustrial]        = GeoDataFeaturePrivate::createWayStyle( "#DED0D5", "#DED0D5" );
    s_defaultStyle[LanduseLandfill]          = GeoDataFeaturePrivate::createWayStyle( Qt::transparent, Qt::transparent, false, false );
    s_defaultStyle[LanduseMeadow]            = GeoDataFeaturePrivate::createWayStyle( Qt::transparent, Qt::transparent, false, false );
    s_defaultStyle[LanduseMilitary]          = GeoDataFeaturePrivate::createWayStyle( "#F3D8D2", "#F3D8D2", true, true, Qt::BDiagPattern );
    s_defaultStyle[LanduseQuarry]            = GeoDataFeaturePrivate::createWayStyle( "#C4C2C2", "#C4C2C2" );
    s_defaultStyle[LanduseRailway]           = GeoDataFeaturePrivate::createWayStyle( "#DED0D5", "#DED0D5" );
    s_defaultStyle[LanduseReservoir]         = GeoDataFeaturePrivate::createWayStyle( "#B5D0D0", "#B5D0D0" );
    s_defaultStyle[LanduseResidential]       = GeoDataFeaturePrivate::createWayStyle( "#DCDCDC", "#DCDCDC" );
    s_defaultStyle[LanduseRetail]            = GeoDataFeaturePrivate::createWayStyle( Qt::transparent, Qt::transparent, false, false );
    
    s_defaultStyle[RailwayRail]              = GeoDataFeaturePrivate::createStyle( 2, 5, "#989898", "#E1E1E1", true, true, Qt::SolidPattern, Qt::DashLine, Qt::FlatCap, true );
    s_defaultStyle[RailwayTram]              = GeoDataFeaturePrivate::createStyle( 1, 4, "#989898", "#989898", true, true, Qt::SolidPattern, Qt::SolidLine, Qt::RoundCap, false );
    s_defaultStyle[RailwayLightRail]         = GeoDataFeaturePrivate::createWayStyle( Qt::transparent, Qt::transparent, false, false );
    s_defaultStyle[RailwayAbandoned]         = GeoDataFeaturePrivate::createWayStyle( Qt::transparent, Qt::transparent, false, false );
    s_defaultStyle[RailwaySubway]            = GeoDataFeaturePrivate::createWayStyle( Qt::transparent, Qt::transparent, false, false );
    s_defaultStyle[RailwayPreserved]         = GeoDataFeaturePrivate::createWayStyle( Qt::transparent, Qt::transparent, false, false );
    s_defaultStyle[RailwayMiniature]         = GeoDataFeaturePrivate::createWayStyle( Qt::transparent, Qt::transparent, false, false );
    s_defaultStyle[RailwayConstruction]      = GeoDataFeaturePrivate::createWayStyle( Qt::transparent, Qt::transparent, false, false );
    s_defaultStyle[RailwayMonorail]          = GeoDataFeaturePrivate::createWayStyle( Qt::transparent, Qt::transparent, false, false );
    s_defaultStyle[RailwayFunicular]         = GeoDataFeaturePrivate::createWayStyle( Qt::transparent, Qt::transparent, false, false );

    s_defaultStyle[Building]                 = GeoDataFeaturePrivate::createStyle( 1, 0, QColor( 0xBE, 0xAD, 0xAD ), QColor( 0xBE, 0xAD, 0xAD ).darker(), 
                                                                                   true, true, Qt::SolidPattern, Qt::SolidLine, Qt::RoundCap, false );

    //TODO
    s_defaultStyle[Satellite] = s_defaultStyle[Default];

    s_defaultStyleInitialized = true;
    s_defaultFont = QFont("Sans Serif");

    QFont tmp;


    // Fonts for areas ...
    tmp = s_defaultStyle[Continent]->labelStyle().font();
    tmp.setLetterSpacing( QFont::AbsoluteSpacing, 2 );
    tmp.setCapitalization( QFont::SmallCaps );
    tmp.setBold( true );
    s_defaultStyle[Continent]->labelStyle().setFont( tmp );

    // Fonts for areas ...
    tmp = s_defaultStyle[Mare]->labelStyle().font();
    tmp.setLetterSpacing( QFont::AbsoluteSpacing, 2 );
    tmp.setCapitalization( QFont::SmallCaps );
    tmp.setBold( true );
    s_defaultStyle[Mare]->labelStyle().setFont( tmp );

    // Now we need to underline the capitals ...

    tmp = s_defaultStyle[SmallNationCapital]->labelStyle().font();
    tmp.setUnderline( true );
    s_defaultStyle[SmallNationCapital]->labelStyle().setFont( tmp );

    tmp = s_defaultStyle[MediumNationCapital]->labelStyle().font();
    tmp.setUnderline( true );
    s_defaultStyle[MediumNationCapital]->labelStyle().setFont( tmp );

    tmp = s_defaultStyle[BigNationCapital]->labelStyle().font();
    tmp.setUnderline( true );
    s_defaultStyle[BigNationCapital]->labelStyle().setFont( tmp );

    tmp = s_defaultStyle[LargeNationCapital]->labelStyle().font();
    tmp.setUnderline( true );
    s_defaultStyle[LargeNationCapital]->labelStyle().setFont( tmp );
}

QFont GeoDataFeature::defaultFont()
{
    return s_defaultFont;
}

void GeoDataFeature::setDefaultFont( const QFont& font )
{
    s_defaultFont = font;
    s_defaultStyleInitialized = false;
}

QString GeoDataFeature::name() const
{
    return d->m_name;
}

void GeoDataFeature::setName( const QString &value )
{
    detach();
    d->m_name = value;
}

QString GeoDataFeature::address() const
{
    return d->m_address;
}

void GeoDataFeature::setAddress( const QString &value)
{
    detach();
    d->m_address = value;
}

QString GeoDataFeature::phoneNumber() const
{
    return d->m_phoneNumber;
}

void GeoDataFeature::setPhoneNumber( const QString &value)
{
    detach();
    d->m_phoneNumber = value;
}

QString GeoDataFeature::description() const
{
    return d->m_description;
}

void GeoDataFeature::setDescription( const QString &value)
{
    detach();
    d->m_description = value;
}

bool GeoDataFeature::descriptionIsCDATA() const
{
    return d->m_descriptionCDATA;
}

void GeoDataFeature::setDescriptionCDATA( bool cdata )
{
    detach();
    d->m_descriptionCDATA = cdata;
}

GeoDataAbstractView GeoDataFeature::abstractView() const
{
    return d->m_abstractView;
}

void GeoDataFeature::setAbstractView( const GeoDataAbstractView &abstractView )
{
    detach();
    d->m_abstractView = abstractView;
}

QString GeoDataFeature::styleUrl() const
{
    return d->m_styleUrl;
}

void GeoDataFeature::setStyleUrl( const QString &value)
{
    detach();
    d->m_styleUrl = value;
    QString styleUrl = value;
    styleUrl.remove('#');
    GeoDataObject *object = parent();
    bool found = false;
    while ( object && !found ) {
        if( object->nodeType() == GeoDataTypes::GeoDataDocumentType ) {
            GeoDataDocument *doc = static_cast<GeoDataDocument*> ( object );
            GeoDataStyleMap &styleMap = doc->styleMap( styleUrl );
            if( !styleMap.value( QString( "normal" ) ).isEmpty() ) {
                styleUrl = styleMap.value( QString( "normal" ) );
                styleUrl.remove('#');
            }
            setStyle( &doc->style( styleUrl ) );
            found = true;
        }
        object = object->parent();
    }
}

bool GeoDataFeature::isVisible() const
{
    return d->m_visible;
}

void GeoDataFeature::setVisible( bool value )
{
    detach();
    d->m_visible = value;
}

GeoDataTimeSpan& GeoDataFeature::timeSpan() const
{
    return d->m_timeSpan;
}

void GeoDataFeature::setTimeSpan( GeoDataTimeSpan timeSpan )
{
    detach();
    d->m_timeSpan = timeSpan;
}

GeoDataTimeStamp&  GeoDataFeature::timeStamp() const
{
    return d->m_timeStamp;
}

void GeoDataFeature::setTimeStamp( GeoDataTimeStamp timeStamp )
{
    detach();
    d->m_timeStamp = timeStamp;
}

GeoDataStyle* GeoDataFeature::style() const
{
    if ( d->m_style != 0 ) {
        return d->m_style;
    } else
    {
        if ( s_defaultStyleInitialized == false )
            initializeDefaultStyles();

        if ( d->m_visualCategory != None
             && s_defaultStyle[ d->m_visualCategory] )
        {
            return s_defaultStyle[ d->m_visualCategory ];
        }
        else
        {
            qWarning() << "No Style got assigned for " << d->m_visualCategory << ", using default! ";
            return s_defaultStyle[ GeoDataFeature::Default];
        }
    }
}

void GeoDataFeature::setStyle( GeoDataStyle* style )
{
    detach();
    d->m_style = style;
}

GeoDataExtendedData& GeoDataFeature::extendedData() const
{
    return d->m_extendedData;
}

void GeoDataFeature::setExtendedData( const GeoDataExtendedData& extendedData )
{
    detach();
    d->m_extendedData = extendedData;
}

GeoDataRegion& GeoDataFeature::region() const
{
    return d->m_region;
}

void GeoDataFeature::setRegion( const GeoDataRegion& region )
{
    detach();
    d->m_region = region;
}

GeoDataFeature::GeoDataVisualCategory GeoDataFeature::visualCategory() const
{
    return d->m_visualCategory;
}

void GeoDataFeature::setVisualCategory( GeoDataFeature::GeoDataVisualCategory index )
{
    detach();
    d->m_visualCategory = index;
}

const QString GeoDataFeature::role() const
{
    return d->m_role;
}

void GeoDataFeature::setRole( const QString &role )
{
    detach();
    d->m_role = role;
}

GeoDataStyleMap* GeoDataFeature::styleMap() const
{
    return d->m_styleMap;
}

void GeoDataFeature::setStyleMap( GeoDataStyleMap* styleMap )
{
    d->m_styleMap = styleMap;
}

int GeoDataFeature::popularityIndex() const
{
    return d->m_popularityIndex;
}

void GeoDataFeature::setPopularityIndex( int popularityIndex )
{
    detach();
    d->m_popularityIndex = popularityIndex;
}

qint64 GeoDataFeature::popularity() const
{
    return d->m_popularity;
}

void GeoDataFeature::setPopularity( qint64 popularity )
{
    detach();
    d->m_popularity = popularity;
}

const QSize GeoDataFeature::symbolSize() const
{
    if ( s_defaultStyleInitialized == false )
        initializeDefaultStyles();

    return style()->iconStyle().icon().size();
}

const QPixmap GeoDataFeature::symbolPixmap() const
{
    if ( s_defaultStyleInitialized == false )
        initializeDefaultStyles();

    return style()->iconStyle().icon();
}

void GeoDataFeature::resetDefaultStyles()
{
    s_defaultStyleInitialized = false;
}

void GeoDataFeature::detach()
{
    if(d->ref == 1)
        return;

    GeoDataFeaturePrivate* new_d = d->copy();

    if (!d->ref.deref()) {
        delete d;
    }

    d = new_d;
    
    d->ref.ref();
}

void GeoDataFeature::pack( QDataStream& stream ) const
{
    GeoDataObject::pack( stream );

    stream << d->m_name;
    stream << d->m_address;
    stream << d->m_phoneNumber;
    stream << d->m_description;
    stream << d->m_visible;
//    stream << d->m_visualCategory;
    stream << d->m_role;
    stream << d->m_popularity;
    stream << d->m_popularityIndex;
}

void GeoDataFeature::unpack( QDataStream& stream )
{
    detach();
    GeoDataObject::unpack( stream );

    stream >> d->m_name;
    stream >> d->m_address;
    stream >> d->m_phoneNumber;
    stream >> d->m_description;
    stream >> d->m_visible;
//    stream >> (int)d->m_visualCategory;
    stream >> d->m_role;
    stream >> d->m_popularity;
    stream >> d->m_popularityIndex;
}

}
