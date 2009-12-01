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

#include "win_calculator.h"
#include "shared.h"

KFFWin_Calculator::KFFWin_Calculator( QWidget *parent )
		: QWidget( parent )
{
	ui_widget.setupUi( this );
	connect( ui_widget.btn_calculate,
	         SIGNAL( clicked() ),
	         SLOT( calculate() )
	       );
	connect( ui_widget.comboBox_distance,
	         SIGNAL( activated( int ) ),
	         SLOT( convertCalc( int ) )
	       );

	connect( ui_widget.comboBox_distanceIn,
	         SIGNAL( activated( int ) ),
	         SLOT( convertUnit1( int ) )
	       );
	connect( ui_widget.comboBox_distanceOut,
	         SIGNAL( activated( int ) ),
	         SLOT( convertUnit2( int ) )
	       );
	connect( ui_widget.btn_convert,
	         SIGNAL( clicked() ),
	         SLOT( convertWUnit() )
	       );
	connect( ui_widget.kdn_longitude1,
	         SIGNAL( valueChanged( double ) ),
	         SLOT( calculate() )
	       );
	connect( ui_widget.kdn_longitude2,
	         SIGNAL( valueChanged( double ) ),
	         SLOT( calculate() )
	       );
	connect( ui_widget.kdn_latitude1,
	         SIGNAL( valueChanged( double ) ),
	         SLOT( calculate() )
	       );
	connect( ui_widget.kdn_latitude2,
	         SIGNAL( valueChanged( double ) ),
	         SLOT( calculate() )
	       );
	connect( ui_widget.kdn_input,
	         SIGNAL( valueChanged( double ) ),
	         SLOT( convertWUnit() )
	       );
	connect( ui_widget.kdn_output,
	         SIGNAL( valueChanged( double ) ),
	         SLOT( convertWUnit() )
	       );
}

KFFWin_Calculator::~KFFWin_Calculator()
{
}

void KFFWin_Calculator::calculate()
{
	convertCalc( ui_widget.comboBox_distance->currentIndex() );
}

void KFFWin_Calculator::convertCalc( int unit )
{
	double longi1, longi2, lat1, lat2, distance;

	longi1 = ui_widget.kdn_longitude1->value();
	longi2 = ui_widget.kdn_longitude2->value();
	lat1 = ui_widget.kdn_latitude1->value();
	lat2 = ui_widget.kdn_latitude2->value();

	distance = calculateDistance( longi1, lat1, longi2, lat2 );

	switch ( unit )
	{

		case US_MILE:
		{
			distance = kmToUSMile( distance );
			break;
		}

		case NAUTIC_MILE:
		{
			distance = kmToNauticMile( distance );
			break;
		}
	}

	ui_widget.kdn_distance->setValue( distance );
}

void KFFWin_Calculator::convertWUnit()
{
	convert( ui_widget.comboBox_distanceIn->currentIndex(),
	         ui_widget.comboBox_distanceOut->currentIndex()
	       );
}

void KFFWin_Calculator::convertUnit1( int unit )
{
	convert( unit, ui_widget.comboBox_distanceOut->currentIndex() );
}

void KFFWin_Calculator::convertUnit2( int unit )
{
	convert( ui_widget.comboBox_distanceIn->currentIndex(), unit );
}

void KFFWin_Calculator::convert( int unit1, int unit2 )
{
	double distance = ui_widget.kdn_input->value();

	switch ( unit1 )
	{

		case KILOMETER:
		{
			switch ( unit2 )
			{

				case US_MILE:
				{
					distance = kmToUSMile( distance );
					break;
				}

				case NAUTIC_MILE:
				{
					distance = kmToNauticMile( distance );
					break;
				}

				case METER:
				{
					distance = 1000.0 * ( distance );
					break;
				}

				case FEET:
				{
					distance = meterToFoot( distance * 1000.0 );
					break;
				}
			}

			break;
		}

		case US_MILE:
		{
			switch ( unit2 )
			{

				case KILOMETER:
				{
					distance = usMileToKm( distance );
					break;
				}

				case NAUTIC_MILE:
				{
					distance = usMileToNauticMile( distance );
					break;
				}

				case METER:
				{
					distance = usMileToKm( distance ) * 1000.0;
					break;
				}

				case FEET:
				{
					distance = usMileToKm( distance );
					distance = meterToFoot( distance * 1000.0 );
					break;
				}
			}

			break;
		}

		case NAUTIC_MILE:
		{
			switch ( unit2 )
			{

				case US_MILE:
				{
					distance = nauticMileToUSMile( distance );
					break;
				}

				case KILOMETER:
				{
					distance = nauticMileToKm( distance );
					break;
				}

				case METER:
				{
					distance = nauticMileToKm( distance ) * 1000.0;
					break;
				}

				case FEET:
				{
					distance = nauticMileToKm( distance );
					distance = meterToFoot( distance * 1000.0 );
					break;
				}
			}

			break;
		}
		case METER:
		{
			switch ( unit2 )
			{

				case NAUTIC_MILE:
				{
					distance = nauticMileToKm( distance / 1000.0 );
					break;
				}

				case US_MILE:
				{
					distance = usMileToKm( distance / 1000.0 );
					break;
				}

				case KILOMETER:
				{
					distance = ( distance / 1000.0 );
					break;
				}

				case FEET:
				{
					distance = meterToFoot( distance );
					break;
				}
			}

			break;
		}
		
		case FEET:
		{
			switch ( unit2 )
			{

				case NAUTIC_MILE:
				{
					distance = footToMeter( distance );
					distance = nauticMileToKm( distance * 1000.0 );
					break;
				}

				case US_MILE:
				{
					distance = footToMeter( distance );
					distance = usMileToKm( distance * 1000.0 );
					break;
				}

				case KILOMETER:
				{
					distance = footToMeter( distance * 1000.0 );
					break;
				}

				case METER:
				{
					distance = footToMeter( distance );
					break;
				}
			}

			break;
		}
	}

	ui_widget.kdn_output->setValue( distance );
}
