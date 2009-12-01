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
 *     (___)_)   File : pref_page3.cpp                      ||--|| *         *
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
 
#include "pref_page3.h"

#include <kmessagebox.h>
#include <kfiledialog.h>
#include <keditlistbox.h>

KFFPref_page3::KFFPref_page3( QWidget *parent )
	: QFrame ( parent )
{
	ui_prefs3_base.setupUi ( this );
	connect ( ui_prefs3_base.btn_terraSearch,
			  SIGNAL ( clicked() ),
			  SLOT ( chooseTerraSlot() )
			);
}


KFFPref_page3::~KFFPref_page3()
{
}

void KFFPref_page3::chooseTerraSlot()
{
	QString buffer;
	KUrl url = KUrl::fromPath ( QDir::homePath() );

	buffer = KFileDialog::getExistingDirectory ( url, this );
	if ( !buffer.isEmpty() )
	{
		ui_prefs3_base.kcfg_terrasync_dir->setText ( buffer );
	}
}
