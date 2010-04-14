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

#include "opt_position.h"
#include "settings.h"

KFFOpt_position::KFFOpt_position( QWidget *parent )
		: KFFOpt_skeleton( parent )
{
	//QString img = Settings::data_dir() + "/aircraft2.svg" ;  pete@ffs nuked image

	ui_widget.setupUi ( this );
	wSetupHeader(ui_widget.wHeaderLabel);
	//ui_widget.widgetLogo->load ( img );  pete@ffs nuked image

	m_grp = new QButtonGroup( this );
	m_grp->addButton( ui_widget.RB_Ground, 0 );
	m_grp->addButton( ui_widget.RB_Carrier, 1 );
	m_grp->addButton( ui_widget.RB_InAir, 2 );
	m_grp->addButton( ui_widget.RB_GPS, 3 );

	connect( m_grp, SIGNAL( buttonClicked( int ) ), SLOT( enableWidget( int ) ) );
	m_startPos = 0;
}

KFFOpt_position::~KFFOpt_position()
{
}

void KFFOpt_position::saveSettings()
{
	Settings::setPosition_altitude( ui_widget.SpinBox_Altitude->value() );
	Settings::setPosition_speed( ui_widget.SpinBox_Speed->value() );
	Settings::setPosition_heading( ui_widget.SpinBox_Heading->value() );
	Settings::setPosition_longitude( ui_widget.kdn_longitude->value() );
	Settings::setPosition_latitude( ui_widget.kdn_latitude->value() );
	Settings::setPosition_selected( m_grp->checkedId() );
	Settings::self()->writeConfig();
}

void KFFOpt_position::loadSettings()
{
	ui_widget.SpinBox_Altitude->setValue( Settings::position_altitude() );
	ui_widget.SpinBox_Speed->setValue( Settings::position_speed() );
	ui_widget.SpinBox_Heading->setValue( Settings::position_heading() );
	ui_widget.kdn_longitude->setValue( Settings::position_longitude() );
	ui_widget.kdn_latitude->setValue( Settings::position_latitude() );
	m_grp->button( Settings::position_selected() )->setChecked(true);
	enableWidget(Settings::position_selected());
}

bool KFFOpt_position::getOptions(QStringList & list)
{
	QString buffer;

	if (m_startPos >= 2)
	{
		list << "--heading=" + ui_widget.SpinBox_Heading->text();
		list << "--altitude=" + ui_widget.SpinBox_Altitude->text();
		list << "--vc=" + ui_widget.SpinBox_Speed->text();
	}
	if (m_startPos == 3)
	{
		buffer.setNum(ui_widget.kdn_longitude->value(), 'f', 6);
		list << "--lon=" + buffer;
		buffer.clear();
		buffer.setNum(ui_widget.kdn_latitude->value(), 'f', 6);
		list << "--lat=" + buffer;
	}
	return true;
}

void KFFOpt_position::enableWidget( int button )
{
	switch ( button )
	{

		case 0:
		{
			ui_widget.groupBox_option->setEnabled( false );
			break;
		}

		case 1:
		{
			ui_widget.groupBox_option->setEnabled( false );
			break;
		}

		case 2:
		{
			ui_widget.groupBox_option->setEnabled( true );
			ui_widget.TXTLabel_GPS_long->setEnabled( false );
			ui_widget.TXTLabel_GPS_lat->setEnabled( false );
			ui_widget.kdn_longitude->setEnabled( false );
			ui_widget.kdn_latitude->setEnabled( false );
			break;
		}

		case 3:
		{
			ui_widget.groupBox_option->setEnabled( true );
			ui_widget.TXTLabel_GPS_long->setEnabled( true );
			ui_widget.TXTLabel_GPS_lat->setEnabled( true );
			ui_widget.kdn_longitude->setEnabled( true );
			ui_widget.kdn_latitude->setEnabled( true );
			break;
		}
	}

	m_startPos = button;
}

void KFFOpt_position::getStartPlace()
{
	emit( startPlace(m_startPos) );
}

