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

#include "opt_common.h"
#include "settings.h"

#include <klocale.h>
#include <kmessagebox.h>


KFFOpt_common::KFFOpt_common( QWidget *parent )
		: KFFOpt_skeleton( parent )
{
	QString img = Settings::data_dir() + "/accueil.svg";

	ui_widget.setupUi ( this );
	ui_widget.widgetLogo->load ( img );

	connect ( ui_widget.btn_stopTerrasync,
	          SIGNAL( clicked() ),
	          SIGNAL( queryCloseTerrasync() )
	        );
}

KFFOpt_common::~KFFOpt_common()
{
}

void KFFOpt_common::saveSettings()
{
	Settings::setCommon_splashscreen( ui_widget.kcfg_common_splashscreen->isChecked() );
	Settings::setCommon_gameMode( ui_widget.kcfg_common_gameMode->isChecked() );
	Settings::setCommon_fullscreen( ui_widget.kcfg_common_fullscreen->isChecked() );
	Settings::setCommon_introMusic( ui_widget.kcfg_common_introMusic->isChecked() );
	Settings::setCommon_sound( ui_widget.kcfg_common_sound->isChecked() );
	Settings::setCommon_joystick( ui_widget.kcfg_common_joystick->isChecked() );
	Settings::setCommon_autoCoordon( ui_widget.kcfg_common_autoCoordon->isChecked() );
	Settings::setCommon_unitMeter( ui_widget.kcfg_common_unitMeter->isChecked() );
	Settings::setCommon_NMEA( ui_widget.kcfg_common_NMEA->isChecked() );
	Settings::setCommon_AtlasToo( ui_widget.kcfg_common_AtlasToo->isChecked() );
	Settings::setCommon_serverHttp( ui_widget.kcfg_common_serverHttp->isChecked() );
	Settings::setCommon_terrasync( ui_widget.kcfg_common_terrasync->isChecked() );
	Settings::self()->writeConfig();
}

void KFFOpt_common::loadSettings()
{
	ui_widget.kcfg_common_splashscreen->setChecked( Settings::common_splashscreen() );
	ui_widget.kcfg_common_gameMode->setChecked( Settings::common_gameMode() );
	ui_widget.kcfg_common_fullscreen->setChecked( Settings::common_fullscreen() );
	ui_widget.kcfg_common_introMusic->setChecked( Settings::common_introMusic() );
	ui_widget.kcfg_common_sound->setChecked( Settings::common_sound() );
	ui_widget.kcfg_common_joystick->setChecked( Settings::common_joystick() );
	ui_widget.kcfg_common_autoCoordon->setChecked( Settings::common_autoCoordon() );
	ui_widget.kcfg_common_unitMeter->setChecked( Settings::common_unitMeter() );
	ui_widget.kcfg_common_NMEA->setChecked( Settings::common_NMEA() );
	ui_widget.kcfg_common_AtlasToo->setChecked( Settings::common_AtlasToo() );
	ui_widget.kcfg_common_serverHttp->setChecked( Settings::common_serverHttp() );
	ui_widget.kcfg_common_terrasync->setChecked( Settings::common_terrasync() );
}

bool KFFOpt_common::getOptions( QStringList & list )
{
	QString buffer, buffer2;

	if ( ui_widget.kcfg_common_AtlasToo->isChecked() ) emit( queryLaunchAtlas() );

	//checkNMEASlot();

	if ( ui_widget.kcfg_common_splashscreen->isChecked() )
	{
		list << "--enable-splash-screen";
	}
	else
	{
		list << "--disable-splash-screen";
	}

	if ( ui_widget.kcfg_common_gameMode->isChecked() )
	{
		list << "--enable-game-mode";
	}
	else
	{
		list << "--disable-game-mode";
	}

	if ( ui_widget.kcfg_common_introMusic->isChecked() )
	{
		list << "--enable-intro-music";
	}
	else
	{
		list << "--disable-intro-music";
	}

	if ( ui_widget.kcfg_common_unitMeter->isChecked() )
	{
		list << "--units-meters";
	}
	else
	{
		list << "--units-feet";
	}

	if ( Settings::http_host() == QString() )
	{
		buffer = i18n( "No host or port configured, the http server will not be launched\n"
		               "and the NMEA protocol will not be actived!" );

		switch ( KMessageBox::warningYesNo( this,
		                                    buffer + "\n" + tr2i18n( "Continue ?" ) ) )
		{

			case KMessageBox::Yes:
			{
				break;
			}

			default:
			{
				list.clear();
				return false;
			}
		}
	}
	else
	{
		if ( Settings::http_port() == 0 )
		{
			buffer = i18n( "No host or port configured, the http server will not be launched\n"
			               "and the NMEA protocol will not be actived!" );

			switch ( KMessageBox::warningYesNo( this,
			                                    buffer + "\n" + tr2i18n( "Continue ?" ) ) )
			{

				case KMessageBox::Yes:
				{
					break;
				}


				default:
				{
					list.clear();
					return false;
				}
			}
		}
		else
		{
			if ( ui_widget.kcfg_common_serverHttp->isChecked() )
			{
				list << "--httpd=" + buffer.setNum( Settings::http_port() );
			}

			if ( ui_widget.kcfg_common_NMEA->isChecked() )
			{
				list << "--nmea=socket,out,0.5," + Settings::http_host() + "," + buffer + ",udp";
			}

			if ( ui_widget.kcfg_common_terrasync->isChecked() )
			{
				buffer.setNum( Settings::http_port() + 1 );
				list << "--nmea=socket,out,0.5," + Settings::http_host() + "," + buffer + ",udp";
				emit ( queryLaunchTerrasync() );
			}
		}
	}

	if ( ui_widget.kcfg_common_joystick->isChecked() )
	{
		list << "--control=joystick";
	}

	if ( ui_widget.kcfg_common_fullscreen->isChecked() )
	{
		list << "--enable-fullscreen";
	}
	else
	{
		list << "--disable-fullscreen";
	}

	if ( ui_widget.kcfg_common_autoCoordon->isChecked() )
	{
		list << "--enable-auto-coordination";
	}
	else
	{
		list << "--disable-auto-coordination";
	}

	if ( ui_widget.kcfg_common_sound->isChecked() )
	{
		list << "--enable-sound";
	}
	else
	{
		list << "--disable-sound";
	}

	return true;
}

void KFFOpt_common::checkNMEASlot()
{
	if ( ( ui_widget.kcfg_common_AtlasToo->isChecked() ) && ( !ui_widget.kcfg_common_NMEA->isChecked() ) )
	{
		KMessageBox::information( this,
		                          tr2i18n( "NMEA protocol must be checked\nThis option will be automatically added" ) );
		ui_widget.kcfg_common_NMEA->setChecked( true );
	}
}
