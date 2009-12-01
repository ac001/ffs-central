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
 *     (___)_)   File : pref_page4.cpp                      ||--|| *         *
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

#include "pref_page4.h"

#include <QLineEdit>

#include <kmessagebox.h>
#include <kfiledialog.h>

KFFPref_page4::KFFPref_page4( QWidget *parent )
		: QFrame( parent )
{
	ui_prefs4_base.setupUi( this );
	connect ( ui_prefs4_base.btn_imgSearch,
	          SIGNAL ( clicked() ),
	          SLOT ( chooseImageSlot() )
	        );
	connect ( ui_prefs4_base.btn_exeSearch,
	          SIGNAL ( clicked() ),
	          SLOT ( chooseExeSlot() )
	        );
}


KFFPref_page4::~KFFPref_page4()
{
}

void KFFPref_page4::chooseImageSlot()
{
	QString buffer;
	KUrl url = KUrl::fromPath ( QDir::homePath() );

	buffer = KFileDialog::getExistingDirectory ( url, this );

	if ( !buffer.isEmpty() )
	{
		//kcfg_fg_addon_sceneries
		ui_prefs4_base.kcfg_img_dir->setText ( buffer );
	}
}

void KFFPref_page4::chooseExeSlot()
{
	QString buffer;
	KUrl url = KUrl::fromPath ( QDir::homePath() );

	buffer = KFileDialog::getSaveFileName ( url, QString(), this );

	if ( !buffer.isEmpty() )
	{
		ui_prefs4_base.kcfg_atlas_exe->setText ( buffer );
	}
}

