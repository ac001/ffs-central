/*****************************************************************************
 *      ____              ____    _       _   _                              *
 *     /# /_\_           |  _ \  (_)   __| | (_)   ___   _ __                *
 *    |  |/o\o\          | | | | | |  / _` | | |  / _ \ | '__|               *
 *    |  \\_/_/          | |_| | | | | (_| | | | |  __/ | |                  *
 *   / |_   |            |____/  |_|  \__,_| |_|  \___| |_|                  *
 *  |  ||\_ ~|                                                               *
 *  |  ||| \/                                                                *
 *  |  |||       Project : KFreeFlight : a KDE4 GUI frontend for FlightGear  *
 *  \//  |                                                                   *
 *   ||  |       Developper : Didier FABERT <didier.fabert@gmail.com>        *
 *   ||_  \      Date : 2009, April                                          *
 *   \_|  o|                                             ,__,                *
 *    \___/      Copyright (C) 2009 by didier fabert     (oo)____            *
 *     ||||__                                            (__)    )\          *
 *     (___)_)   File :                                     ||--|| *         *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *****************************************************************************/

#ifndef METAR_H
#define METAR_H

#include <QString>
#include <QStringList>
#include <QDate>
#include <QTime>
#include <QMap>

/**
 * @author Didier Fabert <didier.fabert@gmail.com>
 * \p
 * MI Shallow
 * PR Partial
 * BC Patches
 * DR Low Drifting
 * BL Blowing
 * SH Shower(s)
 * TS Thunderstorm
 * FZ Freezing
 * \p
 * DZ Drizzle
 * RA Rain
 * SN Snow
 * SG Snow Grains
 * IC Ice Crystals
 * PL Ice Pellets
 * GR Hail
 * GS Small Hail and/or Snow Pellets
 * UP Unknown Precipitation
 * \p
 * BR Mist
 * FG Fog
 * FU Smoke
 * VA Volcanic Ash
 * DU Widespread Dust
 * SA Sand
 * HZ Haze
 * PY Spray
 * \p
 * PO Well-Developed Dust/Sand Whirls
 * SQ Squalls
 * FC Funnel Cloud, Tornado, Waterspout
 * SS Sandstorm
 * SS Duststorm
 * 
 */

class KFFCloudsLayer
{
public:
	KFFCloudsLayer() {};
	~KFFCloudsLayer() {};

	QString altitude;
	QString clouds;


	void clear() { altitude.clear(); clouds.clear(); }
};

class KFFPhenomena
{
public:
	KFFPhenomena() {};
	~KFFPhenomena() {};

	QString prefix;
	QString descriptor;
	QString phenomena;


	void clear() { prefix.clear(); descriptor.clear(); phenomena.clear(); }
};

typedef QMap<int, KFFCloudsLayer> KFFCloudsLayerMap;
typedef QList<KFFPhenomena> KFFPhenomenaList;

/**
 * @author Didier Fabert <didier.fabert@gmail.com>
 */
class KFFMetar
{

public:
	KFFMetar();

	~KFFMetar();

	enum
	{
		UNIT_METRIC,
		UNIT_IMPERIAL,
	};
		
	void clear();

	void setUnitSystem( int sys ) { m_unitsystem = sys ; }
	
	void setMetar( QString metar );
	QString& getMetar();

	void encode();
	void decode();

	void setDate( QDate date );
	QDate& getDate();

	void setTime( QTime time );
	QTime& getTime();

	void setID( QString id );
	QString& getID();

	void setWindDirection( QString windDirection );
	QString& getWindDirection();

	void setWindSpeed( QString windSpeed );
	QString& getWindSpeed();

	void setWindDirGrp( QString windGrpMin, QString windGrpMax );
	QString getWindDirGrp();

	void setWindSpeedMax( QString windSpeedMax );
	QString& getWindSpeedMax();

	void setPresure( QString presure );
	QString& getPresure();

	void setTemperature( QString temperature );
	QString& getTemperature();

	void setDewpoint( QString dewpoint );
	QString& getDewpoint();

	QString& getHumidity();

	void setPhenomena( KFFPhenomenaList phenomenaList );
	void addPhenomena( KFFPhenomena phenomena );
	KFFPhenomenaList & getPhenomena();
	QStringList getPhenomenaStr();
	bool isPhenomenaValid( KFFPhenomena & phenomena, QString & errorstr );

	void setVisibility( QString visibility );
	QString& getVisibility();
	
	void setVerticalVisibility( QString verticalVisibility );
	QString& getVerticalVisibility();

	void setAutoReport( bool autoReport );
	bool getAutoReport();

	void setClouds( QString clouds, QString altitude, int layer = 0 );
	void setClouds( KFFCloudsLayer cloudLayer, int layer = 0 );
	KFFCloudsLayer& getClouds( int layer );
	QString& getCloudsStr( int layer );
	QString& getCloudsAltitude( int layer );
	
	QStringList & getPhenomenaListStr();
	QStringList & getPhenomenaDescriptorListStr();
	QStringList & getPhenomenaPrefixListStr();
	QStringList & getCloudsListStr();

private:
	/// The original METAR
	QString m_metar;
	/// The airport ID
	QString m_id;
	QString m_windDirection;
	QString m_windSpeed;
	QString m_windGrpVal1;
	QString m_windGrpVal2;
	QString m_windSpeedMax;
	QString m_presure;
	QString m_temperature;
	QString m_dewpoint;
	QString m_humidity;
	QString m_visibility;
	QString m_verticalVisibility;
	KFFPhenomenaList m_phenomenas;
	QDate m_date;
	QTime m_time;
	KFFCloudsLayerMap m_clouds;
	bool m_autoReport;
	bool m_skyclear;
	int m_unitsystem;
	QMap<QString, QString> m_phenomena;
	QMap<QString, QString> m_phenomenaDesc;
	QMap<QString, QString> m_phenomenaPrefix;
	QMap<QString, QString> m_rphenomena;
	QMap<QString, QString> m_rphenomenaDesc;
	QMap<QString, QString> m_rphenomenaPrefix;
	QMap<QString, QString> m_cloudsMap;
	QMap<QString, QString> m_rcloudsMap;
	QStringList m_phenomenaList;
	QStringList m_phenomenaDescList;
	QStringList m_phenomenaPrefixList;
	QStringList m_rphenomenaList;
	QStringList m_rphenomenaDescList;
	QStringList m_rphenomenaPrefixList;
	QStringList m_cloudList;
	QStringList m_rcloudList;
};

#endif // METAR_H
