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

#include "opt_datetime.h"
#include "settings.h"

KFFOpt_datetime::KFFOpt_datetime( QWidget *parent )
		: KFFOpt_skeleton( parent )
{
	//Removed by pete@ffs
	//QString img = Settings::data_dir() + "/clouds.svg";
	//QString img2 = Settings::data_dir() + "/x29.svg";

	ui_widget.setupUi ( this );
	//ui_widget.widgetLogo->load ( img ); nuked by pete@ffs
	//ui_widget.widgetLogo2->load ( img2 );

	m_grp = new QButtonGroup( this );
	m_grp->addButton( ui_widget.RB_Real_Time, 0 );
	m_grp->addButton( ui_widget.RB_TimeOfDay, 1 );
	m_grp->addButton( ui_widget.RB_Fixed_Time, 2 );

	connect( m_grp, SIGNAL( buttonClicked( int ) ), SLOT( enableWidget( int ) ) );
	connect( ui_widget.btn_current,
	         SIGNAL( clicked() ),
	         SLOT( setCurrentTime() )
	       );
}

KFFOpt_datetime::~KFFOpt_datetime()
{
}

void KFFOpt_datetime::setCurrentTime()
{
	ui_widget.timeEdit->setTime(QTime::currentTime());
	ui_widget.kdatepicker->setDate(QDate::currentDate() );
}

void KFFOpt_datetime::enableWidget( int button )
{
	switch ( button )
	{

		case 0:
		{
			ui_widget.ComboBox_Time->setEnabled( false );
			ui_widget.kdatepicker->setEnabled( false );
			ui_widget.timeEdit->setEnabled( false );
			ui_widget.label->setEnabled( false );
			ui_widget.btn_current->setEnabled( false );
			break;
		}

		case 1:
		{
			ui_widget.ComboBox_Time->setEnabled( true );
			ui_widget.kdatepicker->setEnabled( false );
			ui_widget.timeEdit->setEnabled( false );
			ui_widget.label->setEnabled( false );
			ui_widget.btn_current->setEnabled( false );
			break;
		}

		case 2:
		{
			ui_widget.ComboBox_Time->setEnabled( false );
			ui_widget.kdatepicker->setEnabled( true );
			ui_widget.timeEdit->setEnabled( true );
			ui_widget.label->setEnabled( true );
			ui_widget.btn_current->setEnabled( true );
			break;
		}
	}
}

void KFFOpt_datetime::saveSettings()
{
	Settings::setDatetime_selected( m_grp->checkedId() );
	Settings::setDatetime_timeofday(ui_widget.ComboBox_Time->currentIndex());
	Settings::setDatetime_season(ui_widget.ComboBox_Season->currentIndex());
	Settings::self()->writeConfig();
}

void KFFOpt_datetime::loadSettings()
{
	ui_widget.ComboBox_Time->setCurrentIndex(Settings::datetime_timeofday());
	ui_widget.ComboBox_Season->setCurrentIndex(Settings::datetime_season());
	m_grp->button( Settings::datetime_selected() )->setChecked(true);
	enableWidget(Settings::datetime_selected());
}

bool KFFOpt_datetime::getOptions( QStringList & list )
{
	QString buffer;

	if ( ui_widget.RB_Fixed_Time->isChecked() )
	{
		buffer = ui_widget.kdatepicker->date().toString( Qt::ISODate ).replace( '-', ":" );
		buffer.append( ":" );
		buffer.append( ui_widget.timeEdit->time().toString( Qt::TextDate ) );
		list << "--start-date-lat=" + buffer;
	}

	if ( ui_widget.RB_TimeOfDay->isChecked() )
	{
		switch ( ui_widget.ComboBox_Time->currentIndex() )
		{

			case 0:
				buffer = "dawn";
				break;

			case 1:
				buffer = "morning";
				break;

			case 2:
				buffer = "noon";
				break;

			case 3:
				buffer = "afternoon";
				break;

			case 4:
				buffer = "dusk";
				break;

			case 5:
				buffer = "evening";
				break;

			case 6:
				buffer = "midnight";
				break;

			default:
				buffer = "noon";
		}

		list << "--timeofday=" + buffer;
	}

	if ( ui_widget.ComboBox_Season->currentIndex() == 1 )
	{
		list << "--season=winter";
	}

	return true;
}

