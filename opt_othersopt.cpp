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

#include "opt_othersopt.h"
#include "settings.h"

#include <kactionselector.h>
#include <kmessagebox.h>
#include <kiconloader.h>
#include <kmenu.h>

#include <QLineEdit>

KFFOpt_othersopt::KFFOpt_othersopt( QWidget *parent )
		: KFFOpt_skeleton( parent )
{
	ui_widget.setupUi ( this );
	wSetupHeader(ui_widget.wHeaderLabel);
	
	m_available = ui_widget.selector->availableListWidget();
	m_selected = ui_widget.selector->selectedListWidget();
	m_available->setContextMenuPolicy( Qt::CustomContextMenu );
	m_selected->setContextMenuPolicy( Qt::CustomContextMenu );
	connect( m_available,
	         SIGNAL( customContextMenuRequested( const QPoint & ) ),
	         this,
	         SLOT( showAvailableMenu( const QPoint & ) )
	       );
	connect( ui_widget.btn_add,
	         SIGNAL( clicked() ),
	         this,
	         SLOT( newAvailableITem() )
	       );

	connect( ui_widget.edit,
	         SIGNAL( returnPressed() ),
	         this,
	         SLOT( newAvailableITem() )
	       );
}


KFFOpt_othersopt::~KFFOpt_othersopt()
{
}

void KFFOpt_othersopt::showAvailableMenu( const QPoint & pt )
{
	QAction* editItem;
	QAction* removeItem;
	KMenu menu( this );

	editItem = new QAction( tr2i18n( "Edit" ), this );
	editItem->setStatusTip( tr2i18n( "Edit this property" ) );
	connect( editItem, SIGNAL( triggered() ), this, SLOT( editAvailableITem() ) );

	removeItem = new QAction( tr2i18n( "Remove" ), this );
	removeItem->setStatusTip( tr2i18n( "Remove property from list" ) );
	connect( removeItem, SIGNAL( triggered() ), this, SLOT( removeAvailableITem() ) );

	menu.addAction( editItem );
	menu.addSeparator();
	menu.addAction( removeItem );
	menu.exec( mapToGlobal( pt + ui_widget.selector->pos() + m_available->pos() ) );
}

void KFFOpt_othersopt::newAvailableITem()
{
	QListWidgetItem* item;

	item = new QListWidgetItem( ui_widget.edit->text() );
	m_available->addItem( item );
	m_available->setCurrentItem( item );
	ui_widget.edit->clear();
}

void KFFOpt_othersopt::editAvailableITem()
{
	QListWidgetItem* item;

	item = m_available->currentItem();
	ui_widget.edit->setText( item->text() );
	delete item;
}

void KFFOpt_othersopt::removeAvailableITem()
{
	QListWidgetItem* item;

	item = m_available->currentItem();
	delete item;
}

void KFFOpt_othersopt::saveSettings()
{
	QListWidgetItem* item;
	QStringList list;
	int i = 0;

	item = m_available->item( i );

	while ( item )
	{
		list << item->text();
		item = m_available->item( ++i );
	}

	Settings::setPersonnal_available( list );

	i = 0;
	list.clear();
	item = m_selected->item( i );

	while ( item )
	{
		list << item->text();
		item = m_selected->item( ++i );
	}

	Settings::setPersonnal_selected( list );

	Settings::self()->writeConfig();
}

void KFFOpt_othersopt::loadSettings()
{
	QStringList list;
	QStringList::Iterator it;
	QListWidgetItem* item;

	list = Settings::personnal_available();

	for ( it = list.begin() ; it != list.end() ; it++ )
	{
		item = new QListWidgetItem( *it );
		m_available->addItem( item );
	}

	list.clear();

	list = Settings::personnal_selected();

	for ( it = list.begin() ; it != list.end() ; it++ )
	{
		item = new QListWidgetItem( *it );
		m_selected->addItem( item );
	}
}

bool KFFOpt_othersopt::getOptions( QStringList & list )
{
	QListWidgetItem* item;
	int i = 0;

	item = m_selected->item( i );

	while ( item )
	{
		list << item->text();
		item = m_selected->item( ++i );
	}

	return true;
}

