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

#include "opt_scenery.h"
#include "settings.h"

#include <kactionselector.h>
#include <kmessagebox.h>
#include <kiconloader.h>

#include <QButtonGroup>
#include <QListWidget>
#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomElement>
#include <QMap>

KFFOpt_scenery::KFFOpt_scenery( QWidget *parent )
		: KFFOpt_skeleton( parent )
{
	KIconLoader loader;
	
	ui_widget.setupUi ( this );
	wSetupHeader(ui_widget.wHeaderLabel);
	

	m_aircraftIcon = loader.loadIcon( "kffplane", KIconLoader::Small );
	m_weatherIcon = loader.loadIcon( "kffweather", KIconLoader::Small );
	m_shipIcon = loader.loadIcon( "kffboat", KIconLoader::Small );
	m_trainIcon = loader.loadIcon( "kfftrain", KIconLoader::Small );
	m_unknowIcon = KIconLoader::unknown();
	
	connect( ui_widget.btn_refresh,
	         SIGNAL( clicked() ),
	         SLOT( reload() )
	       );
}


KFFOpt_scenery::~KFFOpt_scenery()
{
}


void KFFOpt_scenery::reload()
{
	reloadScenarii( true );
}

void KFFOpt_scenery::reloadScenarii( bool showMessage )
{
	QListWidget* selected = ui_widget.selector_scenarii->selectedListWidget();
	QListWidget* available = ui_widget.selector_scenarii->availableListWidget();
	QStringList::Iterator ite;
	QIcon icon;
	QStringList list;
	int i = 0;
	bool found;

	selected->clear();
	available->clear();
	m_scenarii.clear();
	getScenarii();


	QMapIterator<QString, KFFScenarioData> it( m_scenarii );

	list = Settings::scenarii_selected();

	while ( it.hasNext() )
	{
		found = false;
		it.next();

		if ( it.value().type == "aircraft" || it.value().type == "tanker" ||
		        it.value().type == "wingman" || it.value().type == "ballistic" )
		{
			icon.addPixmap( m_aircraftIcon );
		}
		else if ( it.value().type == "thunderstorm" || it.value().type == "thermal" )
		{
			icon.addPixmap( m_weatherIcon );
		}
		else if ( it.value().type == "ship" || it.value().type == "carrier" )
		{
			icon.addPixmap( m_shipIcon );
		}
		else if (it.value().type == "groundvehicle" )
		{
			icon.addPixmap( m_trainIcon );
		}
		else
		{
			icon.addPixmap( m_unknowIcon );
		}

		QListWidgetItem* item = new QListWidgetItem( icon, it.key() );
		item->setToolTip(it.value().description);

		ite = list.begin();

		while ( !found && ite != list.end() )
		{
			if ( it.key() == *ite )
			{
				found = true;
			}

			ite++;
		}

		if ( found )
		{
			selected->insertItem( i++, item );
		}
		else
		{
			available->insertItem( i++, item );
		}

	}

	//loadSettings();
	if ( showMessage )
	{
		KMessageBox::information( this, i18n( "Reloaded" ) );
	}
}

void KFFOpt_scenery::saveSettings()
{
	QListWidget* listWidget = ui_widget.selector_scenarii->selectedListWidget();
	QListWidgetItem* item;
	QStringList list;
	int i = 0;

	item = listWidget->item( i );

	while ( item )
	{
		list << item->text();
		item = listWidget->item( ++i );
	}

	Settings::setScenarii_selected( list );

	Settings::self()->writeConfig();
}

void KFFOpt_scenery::loadSettings()
{
	reloadScenarii( false );
}

bool KFFOpt_scenery::getOptions( QStringList & list )
{
	QListWidget* selected = ui_widget.selector_scenarii->selectedListWidget();
	QListWidgetItem* item;
	QString buffer;
	uint i = 0;

	item = selected->item( i );

	while ( item )
	{
		buffer.clear();
		buffer = buffer.setNum(i, 10);
		list << "--prop:sim/ai/scenario[" + buffer + "]=" + item->text();
		item = selected->item( ++i );
	}
	return true;
}

void KFFOpt_scenery::getScenarii()
{
	QDir directory;
	QString buffer, filename;
	QStringList list, filter;
	QStringList::Iterator it;
	QFile file;

	// make list of all xml file in $FG_ROOT/AI directory
	directory.setPath( Settings::fg_root() + "/AI" );
	filter << "*.xml";
	list = directory.entryList ( filter, QDir::Files, QDir::Name );

	// For each file

	for ( it = list.begin(); it != list.end(); ++it )
	{
		filename = Settings::fg_root() + "/AI/" + *it;
		file.setFileName( filename );

		if ( file.open( QFile::ReadOnly ) )
		{
			searchData( &file );
			file.close();
		}
	}
}

void KFFOpt_scenery::searchData( QFile* file )
{
	QDomDocument doc;
	QDomElement root;
	QDomNode parent;
	QDomNode child;
	QDomElement e_parent;
	QDomElement e_child;
	KFFScenarioData scenario;
	QString name;
	QStringList list;
	QStringList::Iterator it;

	if ( doc.setContent( file ) )
	{
		root = doc.documentElement();
		parent = root.firstChild();
		e_parent = parent.toElement();
		if ( !e_parent.isNull() )
		{
			if ( e_parent.tagName() == "description" )
			{
				list = e_parent.text().split("\n");
				for (it = list.begin() ; it != list.end() ; it++ )
				{
					*it = it->simplified();
				}
				scenario.description = list.join("\n");
				parent = parent.nextSibling();
				
			}
		}
		
		parent = parent.firstChild();
		
		name = file->fileName().section( '/', -1, -1 ).remove( ".xml" );

		while ( !parent.isNull() )
		{
			e_parent = parent.toElement();

			if ( !e_parent.isNull() )
			{
				if ( e_parent.tagName() == "entry" )
				{
					child = parent.firstChild();

					while ( !child.isNull() )
					{
						e_child = child.toElement();

						if ( !e_child.isNull() )
						{
							if ( e_child.tagName() == "type" )
							{
								scenario.type = e_child.text();
							}
						}

						child = child.nextSibling();
					}
				}

				if ( e_parent.tagName() == "description" )
				{
					list = e_parent.text().split("\n");
					for (it = list.begin() ; it != list.end() ; it++ )
					{
						*it = it->simplified();
					}
					scenario.description = list.join("\n");
				}
			}

			parent = parent.nextSibling();

		}

		if ( !m_scenarii.contains( name ) )
		{
			m_scenarii[name] = scenario;
		}

	}
	else
	{
		qDebug() << file->fileName() << "is not a valide xml file" ;
	}
}
