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

#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>

#include "sgcoremag.h"
/**
 * @author Didier Fabert <didier.fabert@gmail.com>
 */


/**
 * Return the current date in julian calendar
 * http://pagesperso-orange.fr/jean-paul.cornec/formule_jj.htm
 */
inline long getCurrentJulianDate()
{
	long julianDate = 0;
	int month, day, year;

	time_t now = time( NULL );

	struct tm *gmt;
	gmt = gmtime( &now );

	month = gmt->tm_mon + 1;
	day = gmt->tm_mday;
	year = gmt->tm_year + 1900;

	if ( month <= 2 )
	{
		year = year - 1;
		month = month + 12;
	}

	int c = year / 100;

	int b = 2 - c + ( c / 4 );

	double t = gmt->tm_mday + ( gmt->tm_hour / 24 ) + ( gmt->tm_min / 1440 )
	           + ( gmt->tm_sec / 86400 );

	int x = ( 365.25 * ( year + 4716 ) );
	int y = ( 30.6001 * ( month + 1 ) );

	julianDate = ( x + y + t + b - 1524.5 );

	return julianDate;
}

/**
 * Calculate the magnetic variation for a place
 * @param longitude : the place longitude in degrees
 * @param latitude : the place latitude in degrees
 * @param altitude : the place elevation in feets
 * @return place magnetic variation in degrees
 */
inline double getMagneticOffset( double longitude, double latitude, double altitude )
{
	double declinaison;
	double field[6];
	long jdate = getCurrentJulianDate();

	longitude = M_PI * ( longitude ) / 180.0; //convert degrees to radians
	latitude = M_PI * ( latitude ) / 180.0; //convert degrees to radians
	altitude = ( altitude * 0.3048006 ) / 1000.0; //convert feets to kilometers
	declinaison = calc_magvar( latitude, longitude, altitude, jdate, field );
	declinaison = ( declinaison * 180.0 ) / M_PI; //convert radians to meters
	return declinaison;
}

/**
 * Calculate distance between two know coordinate places
 * @param lon1 the first place longitude in degrees
 * @param lat1 the first place latitude in degrees
 * @param lon2 the second place longitude in degrees
 * @param lat2 the second place latitude in degrees
 * @return the distance in kilometers
 */
inline double calculateDistance( double lon1, double lat1, double lon2, double lat2 )
{
	double earthRadius = 6371.0; // earth's mean radius in km
	double dLat, dLong, a, c, d;

	//convert angle in radians and calculate the delta
	lon1 = M_PI * ( lon1 ) / 180;
	lat1 = M_PI * ( lat1 ) / 180;
	lon2 = M_PI * ( lon2 ) / 180;
	lat2 = M_PI * ( lat2 ) / 180;
	dLat  = lat2 - lat1;
	dLong = lon2 - lon1;

	//apply the very very simple math formula :-)
	//found at http://www.movable-type.co.uk/scripts/LatLong.html
	a = ( sin( dLat / 2 ) * sin( dLat / 2 ) ) + ( cos( lat1 ) * cos( lat2 ) * sin( dLong / 2 ) * sin( dLong / 2 ) );
	c = 2 * atan2( sqrt( a ), sqrt( 1 - a ) );
	d = earthRadius * c;

	return d;
}

inline double kmToUSMile( double val )
{
	return ( val / 1.60934 );
}

inline double kmToNauticMile( double val )
{
	return ( val / 1.832 );
}

inline double mToNauticMile( double val )
{
	return ( val / 1609.34 );
}

inline double mToUSMile( double val )
{
	return ( val / 1832.0 );
}

inline double usMileToKm( double val )
{
	return ( val * 1.60934 );
}

inline double usMileToM( double val )
{
	return ( val * 1609.34 );
}

inline double nauticMileToKm( double val )
{
	return ( val * 1.832 );
}

inline double nauticMileToM( double val )
{
	return ( val * 1832.0 );
}

inline double usMileToNauticMile( double val )
{
	return ( ( val * 1.60934 ) / 1.832 );
}

inline double nauticMileToUSMile( double val )
{
	return ( ( val * 1.832 ) / 1.60934 );
}

/// Formula found at http://csgnetwork.com/pressinmbcvt.html
inline double inHgTomBars( double val )
{
	return ( val / 0.0295301);
}

/// Formula found at http://csgnetwork.com/pressinmbcvt.html
inline double mBarsToinHg( double val )
{
	return ( val / 33.8637526);
}

inline double footToMeter( double val )
{
	return ( val * 0.3048 );
}

inline double meterToFoot( double val )
{
	return ( val / 0.3048 );
}

#endif // SHARED_H
