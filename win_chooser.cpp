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

#include "win_chooser.h"

#include<QPushButton>
#include<QLineEdit>
#include<QLabel>
#include <QFile>
#include <QDebug>

#include <kmessagebox.h>
#include <kmenu.h>
#include <kiconloader.h>
#include <kstandarddirs.h>

KFFWin_Chooser::KFFWin_Chooser( QWidget *parent )
		: QWidget( parent )
{
	ui_widget.setupUi( this );

	m_type = KFFDLG_SAVE;

	connect( ui_widget.pushButton_action,
	         SIGNAL( clicked() ),
	         SLOT( sendSignal() )
	       );
	connect( ui_widget.listWidget_filename,
	         SIGNAL( itemClicked( QListWidgetItem * ) ),
	         SLOT( setCurrentText( QListWidgetItem * ) )
	       );

	ui_widget.listWidget_filename->setContextMenuPolicy( Qt::CustomContextMenu );
	connect( ui_widget.listWidget_filename,
	         SIGNAL( customContextMenuRequested( const QPoint & ) ),
	         this,
	         SLOT( showContextMenu( const QPoint & ) )
	       );
}

KFFWin_Chooser::~KFFWin_Chooser()
{
}

void KFFWin_Chooser::setType( int type )
{
	m_type = type;
}

void KFFWin_Chooser::showContextMenu( const QPoint & pos )
{
	KIconLoader loader;
	QPixmap pixmap;
	QIcon icon;
	QAction* remove;
	KMenu menu( this );

	pixmap = loader.loadIcon( "edit-delete", KIconLoader::Small );
	icon.addPixmap( pixmap );
	remove = new QAction( icon, i18n( "&Remove flightplan" ), this );
	remove->setStatusTip( i18n( "Remove this flightplan" ) );
	connect( remove, SIGNAL( triggered() ), this, SLOT( remove() ) );

	menu.addAction( remove );
	menu.exec( mapToGlobal( pos + ui_widget.listWidget_filename->pos() ) );
}
void KFFWin_Chooser::remove()
{
	QFile file;
	KStandardDirs stddirs;

	file.setFileName( stddirs.saveLocation( "data" ) +
			"kfreeflight/flightplans/" + ui_widget.listWidget_filename->currentItem()->text() );
	qDebug() << stddirs.saveLocation( "data" ) +
			"kfreeflight/flightplans/" + ui_widget.listWidget_filename->currentItem()->text();
	if ( !file.remove() )
	{
		KMessageBox::information( this, i18n( "Cannot delete file" ) );
	}
	emit ( haveDirtyList() );
}

void KFFWin_Chooser::setTitle( const QString & text )
{
	ui_widget.label_title->setText( text );
}

void KFFWin_Chooser::setButtonText( const QString & text )
{
	ui_widget.pushButton_action->setText( text );
}

void KFFWin_Chooser::setButtonIcon( const QIcon & icon )
{
	ui_widget.pushButton_action->setIcon( icon );
}

void KFFWin_Chooser::setDefaultText( const QString & text )
{
	ui_widget.lineEdit_filename->setText( text );
}

void KFFWin_Chooser::insertStringList( const QStringList & list )
{
	ui_widget.listWidget_filename->clear();
	ui_widget.listWidget_filename->insertItems( 0, list );
}

void KFFWin_Chooser::sendSignal()
{
	QList<QListWidgetItem *> list;

	if ( m_type == KFFDLG_SAVE )
	{
		list = ui_widget.listWidget_filename->findItems( ui_widget.lineEdit_filename->text(),
				Qt::MatchExactly );

		if ( list.count() )
		{
			if ( KMessageBox::questionYesNo( this,
				 i18n( "Overwrite existing file ?" ) ) == KMessageBox::No )
			{
				return;
			}
		}
	}

	emit( selected( ui_widget.lineEdit_filename->text() ) );
}

void KFFWin_Chooser::setCurrentText( QListWidgetItem * item )
{
	if ( item )
	{
		ui_widget.lineEdit_filename->setText( item->text() );
	}
}
