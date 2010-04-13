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

#include "opt_flightplan.h"
#include "settings.h"

KFFOpt_flightplan::KFFOpt_flightplan( QWidget *parent )
		: KFFOpt_skeleton( parent )
{
	

	ui_widget.setupUi( this );
	//* ffs - removing svg image
	//QString img = Settings::data_dir() + "/world.svg";
	//ui_widget.widgetLogo->load( img );

	m_grp = new QButtonGroup( this );
	m_grp->addButton( ui_widget.kcfg_WayPoint_none, 0 );
	m_grp->addButton( ui_widget.kcfg_WayPoint_edit, 1 );
	
	connect( ui_widget.btn_atlas,
	         SIGNAL( clicked() ),
	         SIGNAL( queryAtlas() )
	       );

	connect( ui_widget.btn_WayPoint_Editor,
	         SIGNAL( clicked() ),
	         SIGNAL( queryFlightPlanWin() )
	       );
}


KFFOpt_flightplan::~KFFOpt_flightplan()
{
}

void KFFOpt_flightplan::saveSettings()
{
	Settings::setFlightplan_selected( m_grp->checkedId() );
	Settings::self()->writeConfig();
}

void KFFOpt_flightplan::loadSettings()
{
	m_grp->button( Settings::flightplan_selected() )->setChecked( true );
}

bool KFFOpt_flightplan::getOptions( QStringList & list )
{
	QStringList waypoints;
	QStringList::Iterator it;
	
	waypoints = Settings::flightplan_list();

	if ( ui_widget.kcfg_WayPoint_edit->isChecked() )
	{
		for ( it = waypoints.begin() ; it != waypoints.end() ; it++ )
		{
			list << "--wp=" + it->section( "|", 0, 0 ) + "@" + it->section( "|", 3, 3 );
		}
	}

	return true;
}

//void KFFOpt_flightplan::setOutput( KFFWin_messages* )

