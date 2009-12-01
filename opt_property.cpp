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
 *     (___)_)   File : opt_property.cpp                    ||--|| *         *
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

#include "opt_property.h"
#include "settings.h"

#include <kactionselector.h>
#include <kmessagebox.h>
#include <kiconloader.h>
#include <kmenu.h>

#include <QLineEdit>

KFFOpt_property::KFFOpt_property( QWidget *parent )
		: KFFOpt_skeleton( parent )
{
	ui_widget.setupUi ( this );
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
	//opt_othersopt
	//selector_property
}


KFFOpt_property::~KFFOpt_property()
{
}

void KFFOpt_property::showAvailableMenu( const QPoint & pt )
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

void KFFOpt_property::newAvailableITem()
{
	QListWidgetItem* item;

	item = new QListWidgetItem( ui_widget.edit->text() );
	m_available->addItem( item );
	m_available->setCurrentItem( item );
	ui_widget.edit->clear();
}

void KFFOpt_property::editAvailableITem()
{
	QListWidgetItem* item;

	item = m_available->currentItem();
	ui_widget.edit->setText( item->text() );
	delete item;
}

void KFFOpt_property::removeAvailableITem()
{
	QListWidgetItem* item;

	item = m_available->currentItem();
	delete item;
}

void KFFOpt_property::saveSettings()
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

	Settings::setProperty_available( list );

	i = 0;
	list.clear();
	item = m_selected->item( i );

	while ( item )
	{
		list << item->text();
		item = m_selected->item( ++i );
	}

	Settings::setProperty_selected( list );

	Settings::self()->writeConfig();
}

void KFFOpt_property::loadSettings()
{
	QStringList list;
	QStringList::Iterator it;
	QListWidgetItem* item;

	m_available->clear();
	list = Settings::property_available();

	for ( it = list.begin() ; it != list.end() ; it++ )
	{
		item = new QListWidgetItem( *it );
		m_available->addItem( item );
	}

	list.clear();

	m_selected->clear();
	list = Settings::property_selected();
	
	for ( it = list.begin() ; it != list.end() ; it++ )
	{
		item = new QListWidgetItem( *it );
		m_selected->addItem( item );
	}
}

bool KFFOpt_property::getOptions( QStringList & list )
{
	QListWidgetItem* item;
	uint i = 0;

	item = m_selected->item( i );

	while ( item )
	{
		list << "--prop:" + item->text();
		item = m_selected->item( ++i );
	}

	return true;
}
