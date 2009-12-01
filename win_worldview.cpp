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

#include "win_worldview.h"
#include "settings.h"

#include <kmessagebox.h>
#include <klocale.h>

KFFWin_WorldView::KFFWin_WorldView( QWidget *parent )
	: QWidget( parent )
{
	
	setMinimumSize( 700, 600 );
	setWindowTitle( i18n( "KFreeFlight - Show airport location with Marble" ) );
	m_marble = new Marble::MarbleWidget( this );
	m_marble->setGeometry(0, 0, 700, 600 );
	loadSettings();
}


KFFWin_WorldView::~KFFWin_WorldView()
{
	delete m_marble;
}

void KFFWin_WorldView::loadSettings()
{
	QString buffer = "earth/";
	
	switch ( Settings::marble_theme() )
	{
		case 0:
		{
			buffer.append( "bluemarble/bluemarble" );
			break;
		}
		case 1:
		{
			buffer.append( "citylights/citylights" );
			break;
		}
		default:
		{
			buffer.append( "srtm/srtm" );
			break;
		}
	}
	buffer.append( ".dgml" );
	m_marble->setMapThemeId( buffer );
}

void KFFWin_WorldView::center( qreal longitude, qreal latitude, bool animated)
{
	m_marble->centerOn( longitude, latitude, animated );
	m_marble->update();
	show();
}
