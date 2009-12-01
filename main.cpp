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
 *     (___)_)   File : main.cpp                            ||--|| *         *
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

#include "config.h"
#include "kfreeflight.h"
#include "kfreeflightview.h"

#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <KDE/KLocale>

#include <iostream>

static const char description[] =
    I18N_NOOP( "A FlightGear GUI-frontend designed for KDE4 user" );

static const char version[] = KFREEFLIGHT_VERSION;
static const char homepage[] = "http://kfreeflight.sourceforge.net";

int main( int argc, char **argv )
{
	KAboutData * m_about;

	m_about = new KAboutData( "kfreeflight", 0,
	                          ki18n( "kfreeflight" ),
	                          version,
	                          ki18n( description ),
	                          KAboutData::License_GPL,
	                          ki18n( "(C) 2009 Didier Fabert" ),
	                          KLocalizedString(),
	                          homepage,
	                          "didier.fabert@gmail.com" );

	m_about->addAuthor( ki18n( "Didier Fabert" ),
	                    ki18n( "Project manager and main developer" ),
	                    "didier.fabert@gmail.com" );

	m_about->addCredit( ki18n( "Gerard Robin" ),
	                    ki18n( "Main Beta testeur and 3D modeler" ),
	                    "ghrobin@laposte.net",
	                    "http://perso.orange.fr/GRTux" );

	m_about->addCredit( ki18n( "Andrea Sciucca" ),
	                    ki18n( "Italian translation (application) and Slackware package" ),
	                    "gohanz@infinito.it" );

	m_about->addCredit( ki18n( "Mauro Toffanin" ),
	                    ki18n( "Gentoo ebuild maker" ),
	                    "info@wiredtek.info" );

	m_about->addCredit( ki18n( "Fanta" ),
	                    ki18n( "German translation (application and website)" ),
						"fanta23@gmail.com" );
	
	/*m_about->addCredit( ki18n( "Martin Bantz" ),
						ki18n( "Danish translation (application)" ),
						"martin.bantz@gmail.com" );*/
	KCmdLineArgs::init( argc, argv, m_about );

	KCmdLineOptions options;
	options.add( "+[PROFILE]", ki18n( "Profile to open" ) );
	options.add( "no-airport", ki18n( "Do not load airport list" ) );
	options.add( "no-carrier", ki18n( "Do not make carrier list" ) );
	options.add("d").add( "debug", ki18n( "Do not launch programs, see only the command line" ) );

	KCmdLineArgs::addCmdLineOptions( options );
	KApplication app;

	KFreeFlight *widget = new KFreeFlight;
	int fl = KFreeFlightView::DEFAULT;

	// see if we are starting with session management

	if ( app.isSessionRestored() )
	{
		RESTORE( KFreeFlight );
	}
	else
	{
		// no session.. just start up normally
		KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
		if (!args->isSet("-carrier"))
		{
			fl += KFreeFlightView::DISABLE_CARIER;
		}
		if (!args->isSet("-airport"))
		{
			fl += KFreeFlightView::DISABLE_AIRPORT;
		}
		if (args->isSet("debug"))
		{
			fl += KFreeFlightView::DEBUG_ONLY;
		}
		if ( args->count() == 1 )
		{
			widget->setProfile( args->arg(0) );
		}
		widget->setFlag( fl );
		widget->hide();
		widget->loadSettings();

		args->clear();
	}

	return app.exec();
}
