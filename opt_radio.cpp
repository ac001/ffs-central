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

#include "opt_radio.h"
#include "settings.h"

KFFOpt_radio::KFFOpt_radio( QWidget *parent )
		: KFFOpt_skeleton( parent )
{
	//QString img = Settings::data_dir() + "/clouds.svg"; pete@ffs - nuked image

	ui_widget.setupUi ( this );
	wSetupHeader(ui_widget.wHeaderLabel);
	//ui_widget.widgetLogo->load ( img );  pete@ffs - nuked image

	m_grp = new QButtonGroup( this );
	m_grp->addButton( ui_widget.rb_dmenav1, 0 );
	m_grp->addButton( ui_widget.rb_dmenav2, 1 );
	m_grp->addButton( ui_widget.rb_dmeother, 2 );
	connect( m_grp, SIGNAL( buttonClicked( int ) ), SLOT( enableWidget( int ) ) );

	ui_widget.kdn_nav1->setSteps( 0.025, 1.0 );
	ui_widget.kdn_nav1s->setSteps( 0.025, 1.0 );
	ui_widget.kdn_nav2->setSteps( 0.025, 1.0 );
	ui_widget.kdn_nav2s->setSteps( 0.025, 1.0 );
	ui_widget.kdn_com1->setSteps( 0.025, 1.0 );
	ui_widget.kdn_com1s->setSteps( 0.025, 1.0 );
	ui_widget.kdn_com2->setSteps( 0.025, 1.0 );
	ui_widget.kdn_com2s->setSteps( 0.025, 1.0 );
	ui_widget.kdn_dme->setSteps( 0.025, 1.0 );

}

KFFOpt_radio::~KFFOpt_radio()
{
}

void KFFOpt_radio::saveSettings()
{
	Settings::setRadio_nav1( ui_widget.kdn_nav1->value() );
	Settings::setRadio_nav1standby( ui_widget.kdn_nav1s->value() );
	Settings::setRadio_nav1radial( ui_widget.spinbox_nav1rad->value() );
	Settings::setRadio_nav2( ui_widget.kdn_nav2->value() );
	Settings::setRadio_nav2standby( ui_widget.kdn_nav2s->value() );
	Settings::setRadio_nav2radial( ui_widget.spinbox_nav2rad->value() );
	Settings::setRadio_adf( ui_widget.spinbox_adf->value() );
	Settings::setRadio_adfstandby( ui_widget.spinbox_adfs->value() );
	Settings::setRadio_adfrotation( ui_widget.spinbox_adfrot->value() );
	Settings::setRadio_selected_dme( m_grp->checkedId() );
	Settings::setRadio_dme( ui_widget.kdn_dme->value() );
	Settings::setRadio_tacan1( ui_widget.spinbox_tacan1->value() );
	Settings::setRadio_tacan2( ui_widget.spinbox_tacan2->value() );
	Settings::setRadio_tacan3( ui_widget.spinbox_tacan3->value() );
	Settings::setRadio_tacanletter( ui_widget.combobox_tacan->currentIndex() );
	Settings::setRadio_com1( ui_widget.kdn_com1->value() );
	Settings::setRadio_com1standby( ui_widget.kdn_com1s->value() );
	Settings::setRadio_com2( ui_widget.kdn_com2->value() );
	Settings::setRadio_com2standby( ui_widget.kdn_com2s->value() );
	Settings::setRadio_festival( ui_widget.cb_festival->isChecked() );
	Settings::setRadio_voices( ui_widget.cb_chatter->isChecked() );
	Settings::self()->writeConfig();
}

void KFFOpt_radio::loadSettings()
{
	ui_widget.kdn_nav1->setValue( Settings::radio_nav1() );
	ui_widget.kdn_nav1s->setValue( Settings::radio_nav1standby() );
	ui_widget.spinbox_nav1rad->setValue( Settings::radio_nav1radial() );
	ui_widget.kdn_nav2->setValue( Settings::radio_nav2() );
	ui_widget.kdn_nav2s->setValue( Settings::radio_nav2standby() );
	ui_widget.spinbox_nav2rad->setValue( Settings::radio_nav2radial() );
	ui_widget.spinbox_adf->setValue( Settings::radio_adf() );
	ui_widget.spinbox_adfs->setValue( Settings::radio_adfstandby() );
	ui_widget.spinbox_adfrot->setValue( Settings::radio_adfrotation() );
	ui_widget.kdn_dme->setValue( Settings::radio_dme() );
	ui_widget.kdn_com1->setValue( Settings::radio_com1() );
	ui_widget.kdn_com1s->setValue( Settings::radio_com1standby() );
	ui_widget.kdn_com2->setValue( Settings::radio_com2() );
	ui_widget.kdn_com2s->setValue( Settings::radio_com2standby() );
	ui_widget.spinbox_tacan1->setValue( Settings::radio_tacan1()    );
	ui_widget.spinbox_tacan2->setValue( Settings::radio_tacan2() );
	ui_widget.spinbox_tacan3->setValue( Settings::radio_tacan3() );
	ui_widget.combobox_tacan->setCurrentIndex( Settings::radio_tacanletter() );
	ui_widget.cb_festival->setChecked( Settings::radio_festival() );
	ui_widget.cb_chatter->setChecked( Settings::radio_voices() );
	m_grp->button( Settings::radio_selected_dme() )->setChecked( true );
	enableWidget( Settings::radio_selected_dme() );
}

bool KFFOpt_radio::getOptions( QStringList &list )
{
	QString freq, rad;

	// nav
	freq.setNum( ui_widget.kdn_nav1->value() ).replace( ",", "." );
	rad.setNum( ui_widget.spinbox_nav1rad->value() );
	list << "--nav1=" + rad + ":" + freq;

	freq.clear();
	freq.setNum( ui_widget.kdn_nav1s->value() ).replace( ",", "." );
	list << "--prop:instrumentation/nav/frequencies/standby-mhz="  + freq;

	freq.clear();
	rad.clear();
	freq.setNum( ui_widget.kdn_nav2->value() ).replace( ",", "." );
	rad.setNum( ui_widget.spinbox_nav2rad->value() );
	list << "--nav2=" + rad + ":" + freq;

	freq.clear();
	freq.setNum( ui_widget.kdn_nav2s->value() ).replace( ",", "." );
	list << "--prop:instrumentation/nav[1]/frequencies/standby-mhz="  + freq;

	freq.clear();
	rad.clear();
	freq.setNum( ui_widget.spinbox_adf->value() );
	rad.setNum( ui_widget.spinbox_adfrot->value() );
	list << "--adf=" + rad + ":" + freq;

	freq.clear();
	freq.setNum( ui_widget.spinbox_adfs->value() );
	list << "--prop:instrumentation/adf/frequencies/standby-khz=" + freq;

	freq.clear();
	freq.setNum( ui_widget.spinbox_tacan1->value() );
	list <<  "--prop:instrumentation/tacan/frequencies/selected-channel[1]=" + freq;

	freq.clear();
	freq.setNum( ui_widget.spinbox_tacan2->value() );
	list <<  "--prop:instrumentation/tacan/frequencies/selected-channel[2]=" + freq;

	freq.clear();
	freq.setNum( ui_widget.spinbox_tacan3->value() );
	list <<  "--prop:instrumentation/tacan/frequencies/selected-channel[3]=" + freq;

	freq = ui_widget.combobox_tacan->currentText();
	list <<  "--prop:instrumentation/tacan/frequencies/selected-channel[4]=" + freq;

	if ( ui_widget.rb_dmenav1->isChecked() )
	{
		list << "--dme=nav1" ;
	}

	if ( ui_widget.rb_dmenav2->isChecked() )
	{
		list << "--dme=nav2" ;
	}

	if ( ui_widget.rb_dmeother->isChecked() )
	{
		freq.clear();
		freq.setNum( ui_widget.kdn_dme->value() );
		list << "--dme=" + freq;
	}

	//comm
	freq.clear();

	freq.setNum( ui_widget.kdn_com1->value() );

	list << "--prop:instrumentation/comm/frequencies/selected-mhz=" + freq;

	freq.clear();

	freq.setNum( ui_widget.kdn_com1s->value() );

	list << "--prop:instrumentation/comm/frequencies/standby-mhz=" + freq;

	freq.clear();

	freq.setNum( ui_widget.kdn_com2->value() );

	list << "--prop:instrumentation/comm[1]/frequencies/selected-mhz=" + freq;

	freq.clear();

	freq.setNum( ui_widget.kdn_com2s->value() );

	list << "--prop:instrumentation/comm[1]/frequencies/standby-mhz=" + freq;

	if ( ui_widget.cb_chatter->isChecked() )
	{
		list << "--prop:sim/sound/atc-chatter[0]=true";
	}
	else
	{
		list << "--prop:sim/sound/atc-chatter[0]=false";
	}

	if ( ui_widget.cb_festival->isChecked() )
	{
		list << "--prop:/sim/sound/voices/enabled=true";
	}
	else
	{
		list << "--prop:/sim/sound/voices/enabled=false";
	}

	return true;
}

void KFFOpt_radio::enableWidget( int button )
{
	switch ( button )
	{

		case 2:
		{
			ui_widget.kdn_dme->setEnabled( true );
			break;
		}

		default:
		{
			ui_widget.kdn_dme->setEnabled( false );
		}
	}
}

void KFFOpt_radio::setRadioFrequency( int name, QString freq )
{
	switch ( name )
	{

		case NAV1_CURRENT:
		{
			ui_widget.kdn_nav1->setValue( freq.toDouble() );
			break;
		}

		case NAV1_STANDBY:
		{
			ui_widget.kdn_nav1s->setValue( freq.toDouble() );
			break;
		}

		case NAV1_RADIAL:
		{
			ui_widget.spinbox_nav1rad->setValue( freq.toInt() );
			break;
		}

		case NAV2_CURRENT:
		{
			ui_widget.kdn_nav2->setValue( freq.toDouble() );
			break;
		}

		case NAV2_STANDBY:
		{
			ui_widget.kdn_nav2s->setValue( freq.toDouble() );
			break;
		}

		case NAV2_RADIAL:
		{
			ui_widget.spinbox_nav2rad->setValue( freq.toInt() );
			break;
		}

		case ADF_CURRENT:
		{
			ui_widget.spinbox_adf->setValue( freq.toInt() );
			break;
		}

		case ADF_STANDBY:
		{
			ui_widget.spinbox_adfs->setValue( freq.toInt() );
			break;
		}

		case ADF_ROTATION:
		{
			ui_widget.spinbox_adfrot->setValue( freq.toInt() );
			break;
		}

		case DME_CURRENT:
		{
			ui_widget.kdn_dme->setValue( freq.toDouble() );
			break;
		}

		case COM1_CURRENT:
		{
			ui_widget.kdn_com1->setValue( freq.toDouble() );
			break;
		}

		case COM1_STANDBY:
		{
			ui_widget.kdn_com1s->setValue( freq.toDouble() );
			break;
		}

		case COM2_CURRENT:
		{
			ui_widget.kdn_com2->setValue( freq.toDouble() );
			break;
		}

		case COM2_STANDBY:
		{
			ui_widget.kdn_com2s->setValue( freq.toDouble() );
			break;
		}
	}
}
