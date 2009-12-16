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

#include "metar.h"
#include "shared.h"

#include <QDebug>
#include <QStringList>

#include <klocale.h>

KFFMetar::KFFMetar()
{
	m_phenomenaPrefix[ i18n ( "Heavy" ) ] = "+";
	m_phenomenaPrefixList << "+";
	m_phenomenaPrefix[ i18n ( "Light" ) ] = "-";
	m_phenomenaPrefixList << "-";

	m_phenomenaDesc[ i18n ( "Shallow" ) ] = "MI";
	m_phenomenaDescList << "MI";
	m_phenomenaDesc[ i18n ( "Partial" ) ] = "PR";
	m_phenomenaDescList << "PR";
	m_phenomenaDesc[ i18n ( "Patches" ) ] = "BC";
	m_phenomenaDescList << "BC";
	m_phenomenaDesc[ i18n ( "Low Drifting" ) ] = "DR";
	m_phenomenaDescList << "DR";
	m_phenomenaDesc[ i18n ( "Blowing" ) ] = "BL";
	m_phenomenaDescList << "BL";
	m_phenomenaDesc[ i18n ( "Shower(s)" ) ] = "SH";
	m_phenomenaDescList << "SH";
	m_phenomenaDesc[ i18n ( "Thunderstorm" ) ] = "TS";
	m_phenomenaDescList << "TS";
	m_phenomenaDesc[ i18n ( "Freezing" ) ] = "FZ";
	m_phenomenaDescList << "FZ";

	m_phenomena[ i18n ( "Drizzle" ) ] = "DZ";
	m_phenomenaList << "DZ";
	m_phenomena[ i18n ( "Rain" ) ] = "RA";
	m_phenomenaList << "RA";
	m_phenomena[ i18n ( "Snow" ) ] = "SN";
	m_phenomenaList << "SN";
	m_phenomena[ i18n ( "Snow Grains" ) ] = "SG";
	m_phenomenaList << "SG";
	m_phenomena[ i18n ( "Ice Crystals" ) ] = "IC";
	m_phenomenaList << "IC";
	m_phenomena[ i18n ( "Ice Pellets" ) ] = "PL";
	m_phenomenaList << "PL";
	m_phenomena[ i18n ( "Hail" ) ] = "GR";
	m_phenomenaList << "GR";
	m_phenomena[ i18n ( "Small Hail and/or Snow Pellets" ) ] = "GS";
	m_phenomenaList << "GS";
	m_phenomena[ i18n ( "Unknown Precipitation" ) ] = "UP";
	m_phenomenaList << "UP";

	m_phenomena[ i18n ( "Mist" ) ] = "BR";
	m_phenomenaList << "BR";
	m_phenomena[ i18n ( "Fog" ) ] = "FG";
	m_phenomenaList << "FG";
	m_phenomena[ i18n ( "Smoke" ) ] = "FU";
	m_phenomenaList << "FU";
	m_phenomena[ i18n ( "Volcanic Ash" ) ] = "VA";
	m_phenomenaList << "VA";
	m_phenomena[ i18n ( "Widespread Dust" ) ] = "DU";
	m_phenomenaList << "DU";
	m_phenomena[ i18n ( "Sand" ) ] = "SA";
	m_phenomenaList << "SA";
	m_phenomena[ i18n ( "Haze" ) ] = "HZ";
	m_phenomenaList << "HZ";
	m_phenomena[ i18n ( "Spray" ) ] = "PY";
	m_phenomenaList << "PY";

	m_phenomena[ i18n ( "Well Developed Dust/Sand Whirls" ) ] = "PO";
	m_phenomenaList << "PO";
	m_phenomena[ i18n ( "Squalls" ) ] = "SQ";
	m_phenomenaList << "SQ";
	m_phenomena[ i18n ( "Funnel Cloud, Tornado, Waterspout" ) ] = "FC";
	m_phenomenaList << "FC";
	m_phenomena[ i18n ( "Sandstorm or Duststorm" ) ] = "SS";
	m_phenomenaList << "SS";
	m_phenomena[ i18n ( "Standalone Thunderstorm" ) ] = "TS";
	m_phenomenaList << "TS";

	m_rphenomenaPrefixList << i18n ( "Moderate" );
	m_rphenomenaPrefix[ "-" ] = i18n ( "Light" );
	m_rphenomenaPrefixList << i18n ( "Light" );
	m_rphenomenaPrefix[ "+" ] = i18n ( "Heavy" );
	m_rphenomenaPrefixList << i18n ( "Heavy" );

	m_rphenomenaDescList << i18n ( "No Descriptor" );
	m_rphenomenaDesc[ "MI" ] = i18n ( "Shallow" );
	m_rphenomenaDescList << i18n ( "Shallow" );
	m_rphenomenaDesc[ "PR" ] = i18n ( "Partial" );
	m_rphenomenaDescList << i18n ( "Partial" );
	m_rphenomenaDesc[ "BC" ] = i18n ( "Patches" );
	m_rphenomenaDescList << i18n ( "Patches" );
	m_rphenomenaDesc[ "DR" ] = i18n ( "Low Drifting" );
	m_rphenomenaDescList << i18n ( "Low Drifting" );
	m_rphenomenaDesc[ "BL" ] = i18n ( "Blowing" );
	m_rphenomenaDescList << i18n ( "Blowing" );
	m_rphenomenaDesc[ "SH" ] = i18n ( "Shower(s)" );
	m_rphenomenaDescList << i18n ( "Shower(s)" );
	m_rphenomenaDesc[ "TS" ] = i18n ( "Thunderstorm" );
	m_rphenomenaDescList << i18n ( "Thunderstorm" );
	m_rphenomenaDesc[ "FZ" ] = i18n ( "Freezing" );
	m_rphenomenaDescList << i18n ( "Freezing" );

	m_rphenomena[ "DZ" ] = i18n ( "Drizzle" );
	m_rphenomenaList << i18n ( "Drizzle" );
	m_rphenomena[ "RA" ] = i18n ( "Rain" );
	m_rphenomenaList << i18n ( "Rain" );
	m_rphenomena[ "SN" ] = i18n ( "Snow" );
	m_rphenomenaList << i18n ( "Snow" );
	m_rphenomena[ "SG" ] = i18n ( "Snow Grains" );
	m_rphenomenaList << i18n ( "Snow Grains" );
	m_rphenomena[ "IC" ] = i18n ( "Ice Crystals" );
	m_rphenomenaList << i18n ( "Ice Crystals" );
	m_rphenomena[ "PL" ] = i18n ( "Ice Pellets" );
	m_rphenomenaList << i18n ( "Ice Pellets" );
	m_rphenomena[ "GR" ] = i18n ( "Hail" );
	m_rphenomenaList << i18n ( "Hail" );
	m_rphenomena[ "GS" ] = i18n ( "Small Hail and/or Snow Pellets" );
	m_rphenomenaList << i18n ( "Small Hail and/or Snow Pellets" );
	m_rphenomena[ "UP" ] = i18n ( "Unknown Precipitation" );
	m_rphenomenaList << i18n ( "Unknown Precipitation" );

	m_rphenomena[ "BR" ] = i18n ( "Mist" );
	m_rphenomenaList << i18n ( "Mist" );
	m_rphenomena[ "FG" ] = i18n ( "Fog" );
	m_rphenomenaList << i18n ( "Fog" );
	m_rphenomena[ "FU" ] = i18n ( "Smoke" );
	m_rphenomenaList << i18n ( "Smoke" );
	m_rphenomena[ "VA" ] = i18n ( "Volcanic Ash" );
	m_rphenomenaList << i18n ( "Volcanic Ash" );
	m_rphenomena[ "DU" ] = i18n ( "Widespread Dust" );
	m_rphenomenaList << i18n ( "Widespread Dust" );
	m_rphenomena[ "SA" ] = i18n ( "Sand" );
	m_rphenomenaList << i18n ( "Sand" );
	m_rphenomena[ "HZ" ] = i18n ( "Haze" );
	m_rphenomenaList << i18n ( "Haze" );
	m_rphenomena[ "PY" ] = i18n ( "Spray" );
	m_rphenomenaList << i18n ( "Spray" );

	m_rphenomena[ "PO" ] = i18n ( "Well Developed Dust/Sand Whirls" );
	m_rphenomenaList << i18n ( "Well Developed Dust/Sand Whirls" );
	m_rphenomena[ "SQ" ] = i18n ( "Squalls" );
	m_rphenomenaList << i18n ( "Squalls" );
	m_rphenomena[ "FC" ] = i18n ( "Funnel Cloud, Tornado, Waterspout" );
	m_rphenomenaList << i18n ( "Funnel Cloud, Tornado, Waterspout" );
	m_rphenomena[ "SS" ] = i18n ( "Sandstorm or Duststorm" );
	m_rphenomenaList << i18n ( "Sandstorm or Duststorm" );
	m_rphenomena[ "TS" ] = i18n ( "Stand Alone Thunderstorm" );
	m_rphenomenaList << i18n ( "Stand Alone Thunderstorm" );

	m_cloudList << "FEW";
	m_cloudsMap[ i18n ( "Few" ) ] = "FEW";
	m_cloudList << "SCT";
	m_cloudsMap[ i18n ( "Scattered" ) ] = "SCT";
	m_cloudList << "BKN";
	m_cloudsMap[ i18n ( "Broken" ) ] = "BKN";
	m_cloudList << "OVC";
	m_cloudsMap[ i18n ( "Overcast" ) ] = "OVC";
	m_cloudsMap[ i18n ( "Automatic METAR without cloud layer" ) ] = "CLR";

	m_rcloudsMap[ "FEW" ] = i18n ( "Few" );
	m_rcloudList << i18n ( "Few" );
	m_rcloudsMap[ "SCT" ] = i18n ( "Scattered" );
	m_rcloudList << i18n ( "Scattered" );
	m_rcloudsMap[ "BKN" ] = i18n ( "Broken" );
	m_rcloudList << i18n ( "Broken" );
	m_rcloudsMap[ "OVC" ] = i18n ( "Overcast" );
	m_rcloudList << i18n ( "Overcast" );
}

KFFMetar::~KFFMetar()
{
}

QStringList & KFFMetar::getPhenomenaListStr()
{
	return m_rphenomenaList;
}

QStringList & KFFMetar::getPhenomenaDescriptorListStr()
{
	return m_rphenomenaDescList;
}

QStringList & KFFMetar::getPhenomenaPrefixListStr()
{
	return m_rphenomenaPrefixList;
}

QStringList & KFFMetar::getCloudsListStr()
{
	return m_rcloudList;
}

void KFFMetar::clear()
{
	m_unitsystem = KFFMetar::UNIT_IMPERIAL;
	m_metar.clear();
	m_id.clear();
	m_windDirection.clear();
	m_windSpeed.clear();
	m_windGrpVal1.clear();
	m_windGrpVal2.clear();
	m_windSpeedMax.clear();
	m_presure.clear();
	m_temperature.clear();
	m_dewpoint.clear();
	m_humidity.clear();
	m_phenomenas.clear();
	m_date = QDate();
	m_time = QTime();
	m_clouds.clear();
	m_autoReport = false;
	m_skyclear = false;
}

void KFFMetar::setMetar ( QString metar )
{
	m_metar = metar;
	decode();
}

QString & KFFMetar::getMetar()
{
	encode();
	return m_metar;
}

void KFFMetar::setDate ( QDate date )
{
	m_date = date;
}

QDate& KFFMetar::getDate()
{
	return m_date;
}

void KFFMetar::setTime ( QTime time )
{
	m_time = time;
}

QTime& KFFMetar::getTime()
{
	return m_time;
}

void KFFMetar::setID ( QString id )
{
	m_id = id;
}

QString& KFFMetar::getID()
{
	return m_id;
}

void KFFMetar::setWindDirection ( QString windDirection )
{
	m_windDirection = windDirection;
}

QString& KFFMetar::getWindDirection()
{
	return m_windDirection;
}

void KFFMetar::setWindSpeed ( QString windSpeed )
{
	m_windSpeed = windSpeed;
}

QString& KFFMetar::getWindSpeed()
{
	return m_windSpeed;
}

void KFFMetar::setWindDirGrp ( QString windGrpMin, QString windGrpMax )
{
	m_windGrpVal1 = windGrpMin;
	m_windGrpVal2 = windGrpMax;
}

QString KFFMetar::getWindDirGrp()
{
	return ( m_windGrpVal1 + " - " + m_windGrpVal2 );
}

void KFFMetar::setWindSpeedMax ( QString windSpeedMax )
{
	m_windSpeedMax = windSpeedMax;
}

QString& KFFMetar::getWindSpeedMax()
{
	return m_windSpeedMax;
}

void KFFMetar::setPresure ( QString presure )
{
	m_presure = presure;
}

QString& KFFMetar::getPresure()
{
	return m_presure;
}

void KFFMetar::setTemperature ( QString temperature )
{
	m_temperature = temperature;
}

QString& KFFMetar::getTemperature()
{
	return m_temperature;
}

void KFFMetar::setDewpoint ( QString dewpoint )
{
	m_dewpoint = dewpoint;
}

QString& KFFMetar::getDewpoint()
{
	return m_dewpoint;
}

QString& KFFMetar::getHumidity()
{
	double dewpoint, temperature, humidity;
	QString buffer;

	temperature = m_temperature.toFloat();
	dewpoint = m_dewpoint.toFloat();

	dewpoint = pow ( 10.0, 7.5 * dewpoint / ( 237.7 + dewpoint ) );
	temperature = pow ( 10.0, 7.5 * temperature / ( 237.7 + temperature ) );
	humidity = dewpoint * 100 / temperature;
	buffer.setNum ( humidity, 'f', 2 );
	m_humidity = buffer;

	return m_humidity;
}

void KFFMetar::setPhenomena ( KFFPhenomenaList phenomenaList )
{
	m_phenomenas = phenomenaList;
}

void KFFMetar::addPhenomena ( KFFPhenomena phenomena )
{
	m_phenomenas << phenomena;
}

bool KFFMetar::isPhenomenaValid ( KFFPhenomena & phenomena, QString & errorstr )
{
	if ( m_phenomenaDesc[phenomena.descriptor] == "FZ" &&
	        ! ( m_phenomena[phenomena.phenomena] == "DZ" ||
	            m_phenomena[phenomena.phenomena] == "RA" ||
	            m_phenomena[phenomena.phenomena] == "FG" )
	   )
	{
		errorstr = m_rphenomenaDesc["FZ"];
		errorstr += " ";
		errorstr += i18n ( "must be associated with phenomena" );
		errorstr += " : ";
		errorstr += m_rphenomena["DZ"];
		errorstr += " or ";
		errorstr += m_rphenomena["RA"];
		errorstr += " or ";
		errorstr += m_rphenomena["FG"];
		errorstr += ".";
		return false;
	}

	if ( m_phenomenaDesc[phenomena.descriptor] == "SH" &&
			! ( m_phenomena[phenomena.phenomena] == "RA" ||
			m_phenomena[phenomena.phenomena] == "SN" ||
			m_phenomena[phenomena.phenomena] == "SG" ||
			m_phenomena[phenomena.phenomena] == "IC" ||
			m_phenomena[phenomena.phenomena] == "PL" ||
			m_phenomena[phenomena.phenomena] == "GR" ||
			m_phenomena[phenomena.phenomena] == "GS" )
	   )
	{
		errorstr = m_rphenomenaDesc["SH"];
		errorstr += " ";
		errorstr += i18n ( "must be associated with phenomena" );
		errorstr += " : ";
		errorstr += m_rphenomena["SN"];
		errorstr += " or ";
		errorstr += m_rphenomena["SG"];
		errorstr += " or ";
		errorstr += m_rphenomena["IC"];
		errorstr += " or ";
		errorstr += m_rphenomena["PL"];
		errorstr += " or ";
		errorstr += m_rphenomena["GR"];
		errorstr += " or ";
		errorstr += m_rphenomena["GS"];
		errorstr += ".";
		return false;
	}

	if ( ( m_phenomenaDesc[phenomena.descriptor] == "DR" ||
			  m_phenomenaDesc[phenomena.descriptor] == "BL") &&
			! ( m_phenomena[phenomena.phenomena] == "SN" ||
			m_phenomena[phenomena.phenomena] == "DU" ||
			m_phenomena[phenomena.phenomena] == "SA" )
	   )
	{
		errorstr = m_rphenomenaDesc["DR"];
		errorstr += " or ";
		errorstr += m_rphenomenaDesc["BL"];
		errorstr += " ";
		errorstr += i18n ( "must be associated with phenomena" );
		errorstr += " : ";
		errorstr += m_rphenomena["SN"];
		errorstr += " or ";
		errorstr += m_rphenomena["DU"];
		errorstr += " or ";
		errorstr += m_rphenomena["SA"];
		errorstr += ".";
		return false;
	}

	if ( ( m_phenomenaDesc[phenomena.descriptor] == "MI" ||
			  m_phenomenaDesc[phenomena.descriptor] == "PR" ||
			  m_phenomenaDesc[phenomena.descriptor] == "BC") &&
			  ! ( m_phenomena[phenomena.phenomena] == "FG" )
	   )
	{
		errorstr = m_rphenomenaDesc["MI"];
		errorstr += " or ";
		errorstr += m_rphenomenaDesc["PR"];
		errorstr += " or ";
		errorstr += m_rphenomenaDesc["BC"];
		errorstr += " ";
		errorstr += i18n ( "must be associated with phenomena" );
		errorstr += " : ";
		errorstr += m_rphenomena["FG"];
		errorstr += ".";
		return false;
	}
	errorstr.clear();
	return true;
}

KFFPhenomenaList& KFFMetar::getPhenomena()
{
	return m_phenomenas;
}

QStringList KFFMetar::getPhenomenaStr()
{
	QStringList list;
	QString buffer;
	KFFPhenomenaList::Iterator it;

	for ( it = m_phenomenas.begin() ; it != m_phenomenas.end() ; ++it )
	{
		buffer = it->prefix;
		if ( !buffer.isEmpty() )
		{
			buffer.append ( " " );
		}
		buffer.append ( it->descriptor );
		if ( !buffer.isEmpty() )
		{
			buffer.append ( " " );
		}
		buffer.append ( it->phenomena );
		list << buffer;
	}
	return list;
}

void KFFMetar::setVisibility ( QString visibility )
{
	m_visibility = visibility;
}

QString& KFFMetar::getVisibility()
{
	return m_visibility;
}

void KFFMetar::setVerticalVisibility ( QString verticalVisibility )
{
	m_verticalVisibility = verticalVisibility;
}

QString& KFFMetar::getVerticalVisibility()
{
	return m_verticalVisibility;
}

void KFFMetar::setClouds ( QString clouds, QString altitude, int layer )
{
	KFFCloudsLayer cloudsLayer;


	if ( ( layer < 0 ) || ( layer > 2 ) )
	{
		return;
	}

	cloudsLayer.clouds = clouds;

	cloudsLayer.altitude = altitude;
	m_clouds[layer] = cloudsLayer;
}

void KFFMetar::setClouds ( KFFCloudsLayer cloudsLayer, int layer )
{
	if ( ( layer < 0 ) || ( layer > 2 ) )
	{
		return;
	}
	m_clouds[layer] = cloudsLayer;
}

KFFCloudsLayer& KFFMetar::getClouds ( int layer )
{
	return m_clouds[layer];
}

QString& KFFMetar::getCloudsStr ( int layer )
{
	return m_clouds[layer].clouds;
}

QString& KFFMetar::getCloudsAltitude ( int layer )
{
	return m_clouds[layer].altitude;
}

void KFFMetar::setAutoReport ( bool autoReport )
{
	m_autoReport = autoReport;
}

bool KFFMetar::getAutoReport()
{
	return m_autoReport;
}

void KFFMetar::encode()
{
	QMapIterator<int, KFFCloudsLayer> it ( m_clouds );
	QString buffer;
	double val;
	bool cloudlayerfound = false;
	QStringList list, tmplist;

	m_metar = m_date.toString ( "yyyy/MM/dd" );
	m_metar += " ";
	m_metar += m_time.toString ( "hh:mm" );
	m_metar += "\n";
	m_metar += m_id;
	m_metar += " ";
	m_metar += m_date.toString ( "dd" );
	m_metar += m_time.toString ( "hhmm" );
	m_metar += "Z ";

	if ( m_autoReport )
	{
		m_metar += "AUTO ";
	}

	if ( m_windSpeed.toUShort() < 3 )
	{
		m_metar += "VRB";
	}
	else
	{
		m_metar += m_windDirection.rightJustified ( 3, '0' );
	}
	m_metar += m_windSpeed.rightJustified ( 2, '0' );
	if ( !m_windSpeedMax.isEmpty() )
	{
		m_metar += "G";
		m_metar += m_windSpeedMax;
	}
	m_metar += "KT ";

	if ( !m_windGrpVal1.isEmpty() && !m_windGrpVal2.isEmpty() )
	{
		m_metar += m_windGrpVal1.rightJustified ( 3, '0' );
		m_metar += "V";
		m_metar += m_windGrpVal2.rightJustified ( 3, '0' );
		m_metar += " ";
	}

	if ( m_unitsystem == UNIT_IMPERIAL )
	{
		m_metar += m_visibility;
		m_metar += "SM ";
	}
	else //if ( m_unitsystem == UNIT_METRIC )
	{
		if ( m_visibility.toUInt() > 9999 )
		{
			m_metar += "9999 ";
		}
		else
		{
			m_metar += m_visibility.rightJustified ( 4, '0' );
			m_metar += " ";
		}
	}

	while ( it.hasNext() )
	{
		cloudlayerfound = true;
		it.next();
		qDebug() << it.key();
		qDebug() << it.value().altitude << ":" << it.value().clouds;
		val = it.value().altitude.toDouble() / 100.0;
		buffer.setNum ( val, 'f', 0 );
		qDebug() << "buffer = " << buffer;
		m_metar += it.value().clouds;
		m_metar += buffer.rightJustified ( 3, '0' );
		m_metar += " ";
	}

	if ( !cloudlayerfound )
	{
		if ( m_autoReport )
		{
			m_metar += "CLR ";
		}
		else
		{
			m_metar += "SKC ";
		}
	}
	KFFPhenomenaList::Iterator itp;
	for ( itp = m_phenomenas.begin() ; itp != m_phenomenas.end() ; ++itp )
	{
		qDebug() << "--------------------------------------";
		qDebug() << "pref = " << itp->prefix;
		qDebug() << "desc = " << itp->descriptor;
		qDebug() << "phen = " << itp->phenomena;
		buffer.clear();
		buffer = m_phenomena[ itp->phenomena ];
		if ( !buffer.isEmpty() )
		{
			if ( itp->descriptor != i18n ( "No Descriptor" ) )
			{
				buffer.prepend ( m_phenomenaDesc[ itp->descriptor ] );
			}
			if ( itp->prefix != i18n ( "Moderate" ) )
			{
				buffer.prepend ( m_phenomenaPrefix[ itp->prefix ] );
			}
		}

		qDebug() << "### phenomena = " << buffer;
		m_metar += buffer;
		m_metar += " ";
	}

	if ( m_temperature.toShort() < 0 )
	{
		m_metar += "M";
	}
	m_metar += m_temperature.remove ( "-" ).rightJustified ( 2, '0' );
	m_metar += "/";
	if ( m_dewpoint.toShort() < 0 )
	{
		m_metar += "M";
	}
	m_metar += m_dewpoint.remove ( "-" ).rightJustified ( 2, '0' );
	m_metar += " ";

	if ( m_unitsystem == UNIT_IMPERIAL )
	{
		m_metar += "A";
		m_metar += m_presure.remove ( "." );
	}
	else //if ( m_unitsystem == UNIT_METRIC )
	{
		m_metar += "Q";
		m_metar += m_presure;
	}
}

void KFFMetar::decode()
{
	QStringList list, lines;
	QStringList::Iterator it, itl;
	QString buffer, buffer2, line;
	int i = 0;
	double buf1 = 0.0, buf2 = 0.0, buf3 = 0.0;
	int cloudsLayerNb = 0;
	bool searchAltitude = false, skyclear = false;
	KFFCloudsLayer cloudsLayer;
	KFFPhenomena phenomena;

	qDebug() << "decode METAR";
	lines = m_metar.split ( "\n" );

	for ( itl = lines.begin() ; itl != lines.end() ; ++itl )
	{
		line = *itl;

		if ( itl == lines.begin() )
		{
			setDate ( QDate::fromString ( line.section ( ' ', 0, 0 ), "yyyy/MM/dd" ) );
			setTime ( QTime::fromString ( line.section ( ' ', 1, 1 ), "hh:mm" ) );
			continue;
		}

		if ( line.isEmpty() )
		{
			break;
		}

		list = line.split ( " " );

		for ( it = list.begin() ; it != list.end() ; ++it, i++ )
		{

			switch ( i )
			{

				case 0:
				{
					setID ( *it );
					break;
				}

				case 1: //don't care about date time
				{
					break;
				}

				case 2:
				{
					if ( it->contains ( "auto", Qt::CaseInsensitive ) )
					{
						setAutoReport ( true );
						qDebug() << "auto = true";
						i--;
						break;
					}

					else if ( it->contains ( "cor", Qt::CaseInsensitive ) )
					{
						qDebug() << "cor = true";
						i--;
						break;
					}

					if ( it->contains ( "vrb", Qt::CaseInsensitive ) )
					{
						setWindDirection ( i18n ( "Variable" ) );
					}
					else
					{
						setWindDirection ( it->left ( 3 ) );
					}

					if ( it->contains ( "G", Qt::CaseSensitive ) )
					{
						buffer = it->section ( 'G', 1, 1 );

						if ( buffer.contains ( "KT" ) )
						{
							setWindSpeedMax ( buffer.remove ( "KT" ) );
						}
						else if ( buffer.contains ( "MPS" ) )
						{
							setWindSpeedMax ( buffer.remove ( "MPS" ) );
						}
						else
						{
							qDebug() << "Unknow unit for max speed wind";
						}
					}

					buffer = it->mid ( 3, 2 );

					//if contains MPS value must be multiplied by 2

					if ( it->contains ( "mps", Qt::CaseInsensitive ) )
					{
						buf1 = mToNauticMile ( buffer.toDouble() );
						buffer.clear();
						buffer.setNum ( buf1, 'f', 0 );
					}

					setWindSpeed ( buffer );

					break;
				}

				case 3:
				{
					if ( ( it->contains ( "v", Qt::CaseInsensitive ) ) &&
					        ( !it->contains ( "ndv", Qt::CaseInsensitive ) ) &&
					        ( !it->contains ( "cavok", Qt::CaseInsensitive ) ) )
					{
						setWindDirGrp ( it->section ( 'V', 0, 0 ), it->section ( 'V', 1, 1 ) );
						i--;
						break;
					}

					if ( it->toDouble() )
					{
						setVisibility ( *it );
						break;
					}

					if ( it->contains ( "sm", Qt::CaseInsensitive ) )
					{
						if ( it->contains ( "/", Qt::CaseInsensitive ) )
						{
							buf2 += ( it->left ( 1 ).toDouble() );
							buf3 = ( it->mid ( 2, 1 ).toDouble() );

							if ( !buf3 )
							{
								break;
							}

							buffer.setNum ( usMileToM ( buf1 + ( buf2 / buf3 ) ), 'f', 0 );
						}
						else
						{
							buffer.setNum ( usMileToM ( it->remove ( "SM" ).toDouble() ), 'f', 0 );
						}

						setVisibility ( buffer );
					}
					else
					{
					}

					break;
				}

				default:
				{
					qDebug() << *it;
					buffer.clear();
					searchAltitude = false;
					cloudsLayer.clear();
					skyclear = false;

					if ( ( it->left ( 1 ) == "R" ) && ( it->contains ( "/", Qt::CaseInsensitive ) ) )
					{
						// Runway visibility if visibility is less than 1
						break;
					}

					if ( *it == "CAVOK" )
					{
						buffer.clear();
					}

					else if ( it->contains ( "DZ", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Drizzle" );
					}

					else if ( it->contains ( "RA", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Rain" ) ;
					}

					else if ( it->contains ( "SN", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Snow" ) ;
					}

					else if ( it->contains ( "SG", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Snow Grains" ) ;
					}

					else if ( it->contains ( "IC", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Ice Crystals" ) ;
					}

					else if ( it->contains ( "PL", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Ice Pellets" ) ;
					}

					else if ( it->contains ( "GR", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Hail" ) ;
					}

					else if ( it->contains ( "GS", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Small Hail / Snow Pellets" ) ;
					}

					else if ( it->contains ( "UP", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Unknow Precipitation" ) ;
					}

					// Obscuring
					else if ( it->contains ( "BR", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Mist" );
					}

					else if ( it->contains ( "FG", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Fog" );
					}

					else if ( it->contains ( "FU", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Smoke" );
					}

					else if ( it->contains ( "VA", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Volcanic Ash" );
					}

					else if ( it->contains ( "DU", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Widespread Dust" );
					}

					else if ( it->contains ( "SA", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Sand" );
					}

					else if ( it->contains ( "HZ", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Haze" );
					}

					else if ( it->contains ( "PY", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Spray" );
					}

					else if ( it->contains ( "PO", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Well Developed Dust/Sand Whirls" );
					}

					else if ( it->contains ( "SQ", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Squalls" );
					}

					else if ( it->contains ( "FC", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Funnel Cloud, Tornado, Waterspout" );
					}

					else if ( it->contains ( "SS", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Sandstorm or Duststorm" );
					}
					qDebug() << "phenomena = " << buffer;
					phenomena.phenomena = buffer;


					// Descriptor
					buffer.clear();
					if ( it->contains ( "MI", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Shallow" );
					}

					else if ( it->contains ( "PR", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Partial" );
					}

					else if ( it->contains ( "BC", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Patches" );
					}

					else if ( it->contains ( "DR", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Low Drifting" );
					}

					else if ( it->contains ( "BL", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Blowing" );
					}

					else if ( it->contains ( "SH", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Shower(s)" );
					}

					else if ( it->contains ( "TS", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Thunderstorm" );
					}

					else if ( it->contains ( "FZ", Qt::CaseInsensitive ) )
					{
						buffer = i18n ( "Freezing" );
					}
					qDebug() << "descriptor = " << buffer;
					phenomena.descriptor = buffer;

					// Prefix
					buffer.clear();
					if ( it->contains ( '+', Qt::CaseInsensitive ) > 0 )
					{
						buffer = i18n ( "Heavy" );
					}

					if ( it->contains ( '-', Qt::CaseInsensitive ) > 0 )
					{
						buffer = i18n ( "Light" );
					}

					if ( it->contains ( "RE", Qt::CaseInsensitive ) > 0 )
					{
						buffer = i18n ( "Since Last report" ) + " : " ;
					}
					qDebug() << "prefix = " << buffer;
					phenomena.prefix = buffer;

					if ( !phenomena.phenomena.isEmpty() )
					{
						addPhenomena ( phenomena );
					}

					// Temperature
					if ( it->contains ( "/", Qt::CaseInsensitive ) )
					{
						buf1 = ( it->section ( "/", 0, 0 ).replace ( "M", "-" ).toDouble() );
						buf2 = ( it->section ( "/", 1, 1 ).replace ( "M", "-" ).toDouble() );

						buffer.setNum ( buf1, 'f', 0 );
						setTemperature ( buffer );
						buffer.clear();
						buffer.setNum ( buf2, 'f', 0 );
						setDewpoint ( buffer );
						break;
					}

					// Cloud layer
					if ( it->contains ( "SKC" ) )
					{
						cloudsLayer.clouds = i18n ( "Sky clear" );
						cloudsLayer.altitude.clear();
						skyclear = true;
						break;
					}

					if ( it->contains ( "CLR" ) )
					{
						m_autoReport = true;
						cloudsLayer.clouds = i18n ( "Automatic METAR without cloud layer" );
						cloudsLayer.altitude.clear();
						skyclear = true;
						break;
					}

					else if ( it->left ( 3 ) == "FEW" )
					{
						cloudsLayer.clouds = i18n ( "Few" );
						searchAltitude = true;
					}

					else if ( it->left ( 3 ) == "SCT" )
					{
						cloudsLayer.clouds = i18n ( "Scattered" );
						searchAltitude = true;
					}

					else if ( it->left ( 3 ) == "BKN" )
					{
						cloudsLayer.clouds = i18n ( "Broken" );
						searchAltitude = true;
					}

					else if ( it->left ( 3 ) == "OVC" )
					{
						cloudsLayer.clouds = i18n ( "Overcast" );
						searchAltitude = true;
					}

					if ( searchAltitude )
					{
						qDebug() << *it;
						cloudsLayer.altitude = it->mid ( 3, 2 ) + " " + it->mid ( 5, 1 ) + "00";

						if ( it->contains ( "CB" ) )
						{
							buffer2.append ( " " + i18n ( "Cumulonimbus" ) );
						}

						if ( it->contains ( "TCU" ) )
						{
							buffer2.append ( " " + i18n ( "Towering Cumulonimbus" ) );
						}

						if ( it->contains ( "ACC" ) )
						{
							buffer2.append ( " " + i18n ( "Altocumulus Castellanus" ) );
						}
					}
					if ( skyclear || searchAltitude )
					{
						setClouds ( cloudsLayer, cloudsLayerNb );
						cloudsLayerNb++;
					}

					if ( searchAltitude )
					{
						break;
					}

					// Pression
					if ( ( it->left ( 1 ) == "A" ) || ( it->left ( 1 ) == "Q" ) )
					{
						if ( it->left ( 1 ) == "A" )
						{
							buf1 = it->right ( 4 ).toDouble() / 100.0;
						}
						else
						{
							buf2 = it->right ( 4 ).toDouble();
							buf1 = mBarsToinHg ( buf2 );
						}
						if ( buf1 > 0.0 )
						{
							buffer.setNum ( buf1, 'f', 2 );
							setPresure ( buffer );
						}
						// OK we have all data
						return;

						break;
					}
				}
			}
		}
	}
}




