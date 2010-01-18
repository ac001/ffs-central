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
 *     (___)_)   File : pref_page2.cpp                      ||--|| *         *
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

#include "pref_page2.h"
#include "settings.h"
#include "config.h"

#include <kmessagebox.h>
#include <kfiledialog.h>
#include <keditlistbox.h>

#include <QDebug>
#include <QDir>

KFFPref_page2::KFFPref_page2 ( QWidget *parent )
		: QFrame ( parent )
{
	ui_prefs2_base.setupUi ( this );
	connect ( ui_prefs2_base.btn_rootSearch,
	          SIGNAL ( clicked() ),
	          SLOT ( chooseRootSlot() )
	        );
	connect ( ui_prefs2_base.btn_dataSearch,
	          SIGNAL ( clicked() ),
	          SLOT ( chooseScenerySlot() )
	        );
	connect ( ui_prefs2_base.btn_exeSearch,
	          SIGNAL ( clicked() ),
	          SLOT ( chooseExeSlot() )
	        );
}


KFFPref_page2::~KFFPref_page2()
{
}

void KFFPref_page2::chooseRootSlot()
{
	QString buffer;
	KUrl url = KUrl::fromPath ( Settings::fg_root() );

	buffer = KFileDialog::getExistingDirectory ( url, this );
	if ( !buffer.isEmpty() )
	{
		ui_prefs2_base.kcfg_fg_root->setText ( buffer );
	}
}

void KFFPref_page2::chooseScenerySlot()
{
	QStringList dirlist;
	QStringList::Iterator it;
	QString buffer = FG_SCENERY, dirname;
	KUrl url;
	QDir dir;
	bool found = false;
	
	if ( buffer.isEmpty() )
	{
		url = KUrl::fromPath ( Settings::fg_root() );
	}
	else
	{
		buffer = FG_SCENERY;
		url = KUrl::fromPath ( buffer.section(',', 0, 0 ) );
	}
	
	//TODO Auto fill if selected directory contains more than one scenery dir
	dirname = KFileDialog::getExistingDirectory ( url, this );
	qDebug() << dirname;
	if ( !dirname.isEmpty() )
	{
		dir.cd( dirname );
		dirlist = dir.entryList( QDir::Dirs, QDir::Name );
		for( it = dirlist.begin() ; it != dirlist.end() ; ++it )
		{
			qDebug() << *it;
			if ( ( *it == "." ) || ( *it == ".." ) || ( it->toUpper() == "CVS" ) ) continue;
			if ( isValid ( *it ) )
			{
				ui_prefs2_base.kcfg_fg_addon_sceneries->insertItem ( dirname + "/" + *it );
				found = true;
			}
		}
		if ( !found && isValid( dirname ) )
		{
			ui_prefs2_base.kcfg_fg_addon_sceneries->insertItem ( dirname + "/" + buffer );
		}
	}
}

bool KFFPref_page2::isValid( QString& dirname )
{
	QString bufdirname, buffer;
	bool valid = true;
	
	bufdirname = dirname.toUpper();
	buffer = bufdirname.left( 1 );
	qDebug() << "buffer = " << buffer;
	if ( ( buffer != "E" ) && ( buffer != "W" ) )
	{
		qDebug() << "first letter seem not good : " << buffer;
		valid = false;
	}
	buffer = bufdirname.mid( 1, 3 );
	if ( ( buffer != "000" ) && ( buffer.toUShort() == 0 ) )
	{
		qDebug() << "first number seem not good : " << buffer;
		valid = false;
	}
	buffer = bufdirname.mid( 4, 1 );
	if ( ( buffer.toUpper() != "N" ) && ( buffer.toUpper() != "S" ) )
	{
		qDebug() << "second letter seem not good : " << buffer;
		valid = false;
	}
	buffer = bufdirname.mid( 5, 3 );
	if ( ( buffer != "000" ) && ( buffer.toUShort() == 0 ) )
	{
		qDebug() << "second number seem not good : " << buffer;
		valid = false;
	}
	return valid;
}

void KFFPref_page2::chooseExeSlot()
{
	QString buffer;
	KUrl url = KUrl::fromPath ( QDir::homePath() );

	buffer = KFileDialog::getSaveFileName ( url, QString(), this );
	if ( !buffer.isEmpty() )
	{
		ui_prefs2_base.kcfg_fg_exe->insertItem ( buffer );
	}
}

