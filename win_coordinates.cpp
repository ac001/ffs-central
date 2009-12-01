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
 *     (___)_)   File : win_coordinate.cpp                  ||--|| *         *
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

#include "win_coordinates.h"

#include <QDebug>

KFFWin_Coordinates::KFFWin_Coordinates( QWidget *parent )
		: QWidget( parent )
{
	ui_widget.setupUi( this );
	
	m_longitudeGrp = new QButtonGroup( this );
	m_longitudeGrp->addButton( ui_widget.radiobutton_LongitudeEast, 0 );
	m_longitudeGrp->addButton( ui_widget.radiobutton_LongitudeWest, 1 );
	ui_widget.radiobutton_LongitudeEast->setChecked( true );
	
	m_latitudeGrp = new QButtonGroup( this );
	m_latitudeGrp->addButton( ui_widget.radiobutton_LatitudeNorth, 0 );
	m_latitudeGrp->addButton( ui_widget.radiobutton_LatitudeSouth, 1 );
	ui_widget.radiobutton_LatitudeNorth->setChecked( true );
	
	connect( ui_widget.btn_OK,
	         SIGNAL( clicked() ),
	         SLOT( getCoordinates() )
	       );
}


KFFWin_Coordinates::~KFFWin_Coordinates()
{
}

void KFFWin_Coordinates::getCoordinates()
{
	double longitude, latitude;
	
	longitude = ui_widget.kdn_longitude->value();
	if ( ui_widget.radiobutton_LongitudeWest->isChecked() )
	{
		longitude = longitude * -1.0;
	}
	latitude = ui_widget.kdn_latitude->value();
	if ( ui_widget.radiobutton_LatitudeSouth->isChecked() )
	{
		latitude = latitude * -1.0;
	}
	
	m_coordinates.setCoordinates(longitude, latitude);
	emit( queryCoordinates(m_coordinates.toString()) );
	hide();
}

/******************************************************************************
 *                                                                            *
 ******************************************************************************/

KFFCoordinates::KFFCoordinates()
{
}

KFFCoordinates::~KFFCoordinates()
{
}


QString KFFCoordinates::toString()
{
	QString buffer, coord;
	
	buffer.setNum(m_longitude, 'f', 4).remove("-");
	if (m_longitude < 0)
	{
		buffer.prepend("W");
	}
	else
	{
		buffer.prepend("E");
	}
	coord = buffer + " ";
	
	buffer.clear();
	buffer.setNum(m_latitude, 'f', 4).remove("-");
	if (m_latitude < 0)
	{
		buffer.prepend("S");
	}
	else
	{
		buffer.prepend("N");
	}
	coord.append(buffer);
	
	return coord;
}

void KFFCoordinates::setCoordinates( double longitude, double latitude )
{
	m_longitude = longitude;
	m_latitude = latitude;
}

