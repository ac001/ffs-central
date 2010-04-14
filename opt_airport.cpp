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
 *     (___)_)   File : opt_airport.cpp                     ||--|| *         *
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


#include "opt_airport.h"
#include "settings.h"
#include "shared.h"

#include <kfilterdev.h>
#include <kiconloader.h>
#include <kmessagebox.h>
#include <kmenu.h>

#include <QIODevice>
#include <QTextStream>

KFFOpt_airport::KFFOpt_airport ( QWidget *parent )
		: KFFOpt_skeleton ( parent )
{
	KIconLoader loader;

	ui_widget.setupUi ( this );
	wSetupHeader(ui_widget.wHeaderLabel);

	m_progress = 0;
	m_metarView = 0;
	m_searchAirport = 0;

	qRegisterMetaType<AirportItem>();

	m_towerIcon = loader.loadIcon ( "kfftower", KIconLoader::Small );
	m_runwayIcon = loader.loadIcon ( "kffwindsock", KIconLoader::Small );

	m_thread = new ReadingThread();

	connect ( ui_widget.btn_Refresh,
	          SIGNAL ( clicked() ),
	          SLOT ( loadAirport( ) )
	        );

	connect ( ui_widget.btn_ShowPlace,
	          SIGNAL ( clicked() ),
	          SLOT ( whereIsIt( ) )
	        );

	connect ( ui_widget.btn_WebInfo,
	          SIGNAL ( clicked() ),
	          SLOT ( webInfo( ) )
	        );

	connect ( m_thread,
	          SIGNAL ( insertItem ( AirportItem ) ),
	          SLOT ( insertItem ( AirportItem ) )
	        );

	connect ( m_thread,
	          SIGNAL ( finished() ),
	          SLOT ( loadFinished() )
	        );

	connect ( ui_widget.lineEdit_search,
	          SIGNAL ( textChanged ( const QString & ) ),
	          SLOT ( find ( const QString & ) )
	        );

	ui_widget.airportList->setContextMenuPolicy ( Qt::CustomContextMenu );
	connect ( ui_widget.airportList,
	          SIGNAL ( customContextMenuRequested ( const QPoint & ) ),
	          this,
	          SLOT ( showContextMenu ( const QPoint & ) )
	        );
	connect ( ui_widget.airportList,
	          SIGNAL ( itemClicked ( QTreeWidgetItem*, int ) ),
	          this,
	          SLOT ( setAirport ( QTreeWidgetItem*, int ) )
	        );

	ui_widget.favorite->setContextMenuPolicy ( Qt::CustomContextMenu );
	connect ( ui_widget.favorite,
	          SIGNAL ( customContextMenuRequested ( const QPoint & ) ),
	          this,
	          SLOT ( showFavoriteContextMenu ( const QPoint & ) )
	        );
	connect ( ui_widget.favorite,
	          SIGNAL ( itemClicked ( QTreeWidgetItem*, int ) ),
	          this,
	          SLOT ( showFavorite ( QTreeWidgetItem* ) )
	        );
}


KFFOpt_airport::~KFFOpt_airport()
{
	m_thread->quit();
	delete m_thread;
}

void KFFOpt_airport::loadAirport()
{
	loadAirport ( true );
}

void KFFOpt_airport::loadAirport ( bool showDialog )
{
	ui_widget.airportList->clear();

	if ( showDialog )
	{
		if ( !m_progress )
		{
			m_progress = new KProgressDialog ( this,
			                                   i18n ( "Airport List" ),
			                                   i18n ( "Construct airport list" )
			                                 );
		}

		m_progress->setAttribute ( Qt::WA_DeleteOnClose );

		m_progress->setAutoClose ( false );
		m_progress->setAutoReset ( false );
		m_progress->setAllowCancel ( false );
		m_progress->progressBar()->setRange ( 0, NB_AIRPORT );
		m_progress->show();
	}

	m_thread->start();

	m_thread->setPriority ( QThread::NormalPriority );
	//loadFinished();
}

void KFFOpt_airport::insertItem ( AirportItem item )
{
	QTreeWidgetItem* parent;
	QTreeWidgetItem* child;

	if ( item.parent.count() )
	{
		parent = new QTreeWidgetItem ( ui_widget.airportList, item.parent );
		parent->setIcon ( 0, m_towerIcon );
		parent->setText ( 1, item.coordinates );
		ui_widget.airportList->addTopLevelItem ( parent );

		QListIterator<QStringList> iterator ( item.childs );

		while ( iterator.hasNext() )
		{
			child = new QTreeWidgetItem ( parent, iterator.next() );
			child->setIcon ( 0, m_runwayIcon );
			parent->addChild ( child );
		}
	}

	if ( m_progress )
	{
		m_progress->progressBar()->setValue ( m_progress->progressBar()->value() + 1 );
	}
}

void KFFOpt_airport::loadFinished()
{
	QString buffer;
	QList<QTreeWidgetItem*> items;

	emit ( finished() );
	m_thread->terminate();
	m_thread->wait();
	ui_widget.airportList->sortItems(0, Qt::AscendingOrder);

	find ( m_airport );
	
	if ( m_progress )
	{
		m_progress->close();
		m_progress = 0;
		buffer.setNum ( ui_widget.airportList->topLevelItemCount() );

		buffer.prepend ( "\n" );
		buffer.prepend ( i18n ( "finished" ) );
		buffer.append ( " " + i18n ( "airports loaded" ) );
		KMessageBox::information ( this,  buffer );
	}
}

void KFFOpt_airport::whereIsIt()
{
	QTreeWidgetItem* item;
	QTreeWidgetItem* parent;
	QString buffer;
	qreal longitude = 0.0, latitude = 0.0;

	item = ui_widget.airportList->currentItem();

	if ( item )
	{
		parent = item->parent();

		if ( parent )
		{
			buffer = parent->text ( 1 );
		}
		else
		{
			buffer = item->text ( 1 );
		}
	}

	qDebug() << "longitude = " << buffer.section ( " ", 1, 1 ).remove ( "E" ).replace ( "W", "-" );
	qDebug() << "latitude = " << buffer.section ( " ", 0, 0 ).remove ( "N" ).replace ( "S", "-" );
	longitude = buffer.section ( " ", 1, 1 ).remove ( "E" ).replace ( "W", "-" ).toDouble();
	latitude = buffer.section ( " ", 0, 0 ).remove ( "N" ).replace ( "S", "-" ).toDouble();
	qDebug() << "emit " << longitude << " " << latitude << " ;";
	emit ( showPlace ( longitude, latitude, true ) );
}

void KFFOpt_airport::webInfo()
{
	KMessageBox::information ( this, i18n ( "Not implemented yet" ) );
}

void KFFOpt_airport::getWeather()
{
	QTreeWidgetItem* item;
	QTreeWidgetItem* parent;
	QString buffer;

	item = ui_widget.airportList->currentItem();

	if ( item )
	{
		parent = item->parent();

		if ( parent )
		{
			buffer = parent->text ( 0 );
		}
		else
		{
			buffer = item->text ( 0 );
		}

		if ( m_metarView )
		{
			m_metarView->show();
			m_metarView->setAirport ( buffer );
			m_metarView->download();
		}
	}
}

void KFFOpt_airport::removeFavorite()
{
	QTreeWidgetItem* item;

	item = ui_widget.favorite->currentItem();
	ui_widget.favorite->takeTopLevelItem ( ui_widget.favorite->indexOfTopLevelItem ( item ) );
}

void KFFOpt_airport::showFavoriteContextMenu ( const QPoint &pos )
{
	KIconLoader loader;
	QPixmap pixmap;
	QIcon icon;
	QAction* remove;
	KMenu menu ( this );

	pixmap = loader.loadIcon ( "edit-delete", KIconLoader::Small );
	icon.addPixmap ( pixmap );
	remove = new QAction ( icon, tr2i18n ( "&Remove" ), this );
	remove->setStatusTip ( tr2i18n ( "Remove this favorite airport" ) );
	connect ( remove, SIGNAL ( triggered() ), this, SLOT ( removeFavorite() ) );

	menu.addAction ( remove );
	menu.exec ( mapToGlobal ( pos + ui_widget.favorite->pos() ) );
}

void KFFOpt_airport::showContextMenu ( const QPoint &pos )
{
	KIconLoader loader;
	QPixmap pixmap;
	QIcon icon;
	QAction* select;
	QAction* where;
	QAction* more;
	QAction* search;
	QAction* favorite;
	QAction* weather;
	KMenu menu ( this );

	pixmap = loader.loadIcon ( "dialog-ok", KIconLoader::Small );
	icon.addPixmap ( pixmap );
	select = new QAction ( icon, tr2i18n ( "&Select" ), this );
	select->setStatusTip ( tr2i18n ( "Select this airport for starting place" ) );
	connect ( select, SIGNAL ( triggered() ), this, SLOT ( selectAirport() ) );

	pixmap = loader.loadIcon ( "help-about", KIconLoader::Small );
	icon.addPixmap ( pixmap );
	search = new QAction ( icon, tr2i18n ( "&More infos" ), this );
	search->setStatusTip ( tr2i18n ( "Search more informations about this airport" ) );
	connect ( search, SIGNAL ( triggered() ), this, SLOT ( search() ) );

	pixmap = loader.loadIcon ( "konqueror", KIconLoader::Small );
	icon.addPixmap ( pixmap );
	more = new QAction ( icon, tr2i18n ( "&Web infos" ), this );
	more->setStatusTip ( tr2i18n ( "Search informations about this airport on web" ) );
	connect ( more, SIGNAL ( triggered() ), this, SLOT ( webInfo() ) );

	pixmap = loader.loadIcon ( "edit-find", KIconLoader::Small );
	icon.addPixmap ( pixmap );
	where = new QAction ( icon, tr2i18n ( "&Where is it" ), this );
	where->setStatusTip ( tr2i18n ( "Show place in map" ) );
	connect ( where, SIGNAL ( triggered() ), this, SLOT ( whereIsIt() ) );

	pixmap = loader.loadIcon ( "rating", KIconLoader::Small );
	icon.addPixmap ( pixmap );
	favorite = new QAction ( icon, tr2i18n ( "&Favorite" ), this );
	favorite->setStatusTip ( tr2i18n ( "Add this airport to favorite" ) );
	connect ( favorite, SIGNAL ( triggered() ), this, SLOT ( addToFavorite() ) );

	pixmap = loader.loadIcon ( "kffweather", KIconLoader::Small );
	icon.addPixmap ( pixmap );
	weather = new QAction ( icon, tr2i18n ( "&Weather" ), this );
	weather->setStatusTip ( tr2i18n ( "Download real weather for this airport" ) );
	connect ( weather, SIGNAL ( triggered() ), this, SLOT ( getWeather() ) );

	menu.addAction ( select );
	menu.addAction ( search );
	menu.addSeparator();
	menu.addAction ( more );
	menu.addSeparator();
	menu.addAction ( where );
	menu.addAction ( favorite );
	menu.addSeparator();
	menu.addAction ( weather );
	menu.exec ( mapToGlobal ( pos + ui_widget.airportList->pos() ) );
}

QString KFFOpt_airport::getParentCurrentText ( int column )
{
	QTreeWidgetItem* item;
	QTreeWidgetItem* parent;
	QString buffer;

	item = ui_widget.airportList->currentItem();

	if ( item )
	{
		parent = item->parent();

		if ( parent )
		{
			buffer = parent->text ( column );
		}
		else
		{
			buffer = item->text ( column );
		}
	}

	return buffer;
}

void KFFOpt_airport::search()
{
	AirportDescription desc;
	QTreeWidgetItem* item;
	QTreeWidgetItem* parent;
	QTreeWidgetItem* child;
	QStringList runway;
	QString buffer;
	int i = 0;

	item = ui_widget.airportList->currentItem();

	if ( item )
	{
		parent = item->parent();

		if ( parent )
		{
			desc.id = parent->text ( 0 );
			desc.name = parent->text ( 2 );
			desc.elevation = parent->text ( 3 );
			buffer = parent->text ( 1 );
			desc.longitude = buffer.section ( ' ', 1 );
			desc.latitude = buffer.section ( ' ', 0, 0 );
			child = parent->child ( i );

			while ( child )
			{
				runway << child->text ( 1 );
				buffer = child->text ( 2 );
				runway << buffer.section ( '°', 0, 0 );
				buffer = buffer.section ( '(', 1 ).remove ( ')' );
				runway << buffer.section ( 'x', 0, 0 ).simplified();
				runway << buffer.section ( 'x', 1 ).simplified();
				desc.runway << runway;
				runway.clear();
				child = parent->child ( ++i );
			}
		}
		else
		{
			desc.id = item->text ( 0 );
			desc.name = item->text ( 2 );
			desc.elevation = item->text ( 3 );
			buffer = item->text ( 1 );
			desc.longitude = buffer.section ( ' ', 1 );
			desc.latitude = buffer.section ( ' ', 0, 0 );
			child = item->child ( i );

			while ( child )
			{
				runway << child->text ( 1 );
				buffer = child->text ( 2 );
				runway << buffer.section ( '°', 0, 0 );
				buffer = buffer.section ( '(', 1 ).remove ( ')' );
				runway << buffer.section ( 'x', 0, 0 ).simplified();
				runway << buffer.section ( 'x', 1 ).simplified();
				desc.runway << runway;
				runway.clear();
				child = item->child ( ++i );
			}
		}
	}

	m_searchAirport->show();

	emit ( searchAirport ( desc ) );
}
void KFFOpt_airport::selectAirport()
{
	setAirport ( ui_widget.airportList->currentItem(), 0 );
}

void KFFOpt_airport::setAirport ( QTreeWidgetItem* item, int v )
{
	QTreeWidgetItem* parent;

	if ( item )
	{
		parent = item->parent();

		if ( parent )
		{
			m_airport = parent->text ( 0 );
			m_runway = item->text ( 1 );
		}
		else
		{
			m_airport = item->text ( 0 );
			m_runway.clear();
		}
	}
}

void KFFOpt_airport::addToFavorite ( QStringList list )
{
	QTreeWidgetItem* item;
	QList<QTreeWidgetItem*> items;

	items = ui_widget.favorite->findItems ( *list.begin(), Qt::MatchCaseSensitive, 0 );

	if ( items.isEmpty() )
	{
		item = new QTreeWidgetItem ( ui_widget.favorite, list );
		item->setIcon ( 0, m_towerIcon );
		ui_widget.favorite->addTopLevelItem ( item );
		saveSettings();
	}
}

void KFFOpt_airport::addToFavorite()
{
	QTreeWidgetItem* item;
	QTreeWidgetItem* parent;
	QTreeWidgetItem* favorite;
	QStringList list;
	QString buffer;
	QList<QTreeWidgetItem*> items;

	item = ui_widget.airportList->currentItem();

	if ( item )
	{
		parent = item->parent();

		if ( parent )
		{
			buffer = parent->text ( 0 );
			list << buffer;
			list << parent->text ( 2 );
		}
		else
		{
			buffer = item->text ( 0 );
			list << buffer;
			list << item->text ( 2 );
		}

		items = ui_widget.favorite->findItems ( buffer, Qt::MatchCaseSensitive, 0 );

		if ( items.isEmpty() )
		{
			favorite = new QTreeWidgetItem ( ui_widget.favorite, list );
			favorite->setIcon ( 0, m_towerIcon );
			ui_widget.favorite->addTopLevelItem ( favorite );
		}
	}
}

void KFFOpt_airport::showFavorite ( QTreeWidgetItem* selected )
{
	QString buffer;

	buffer = selected->text ( 0 );
	find ( buffer );
}

void KFFOpt_airport::find ( const QString & text )
{
	QString buffer = text;
	QList<QTreeWidgetItem*> items;
	QTreeWidgetItem* parent = ui_widget.airportList->currentItem();
	QTreeWidgetItem* item;
	int maxItem = 0;

	if ( parent )
	{
		ui_widget.airportList->collapseItem( parent );
	}
	items = ui_widget.airportList->findItems ( buffer.toUpper(), Qt::MatchStartsWith | Qt::MatchCaseSensitive );

	if ( items.count() )
	{
		parent = items.first();
		ui_widget.airportList->expandItem( parent );
		ui_widget.airportList->setCurrentItem ( parent );
		maxItem = parent->childCount();
		item = parent->child ( maxItem - 1 );
		if ( item )
		{
			ui_widget.airportList->setCurrentItem ( item );

			if ( !m_runway.isEmpty() )
			{
				for ( int i = 0 ; i < maxItem ; ++i )
				{
					if ( parent->child( i )->text( 1 ) == m_runway )
					{
						item = parent->child( i );
						ui_widget.airportList->setCurrentItem ( item );
						break;
					}
				}
			}
		}
	}
}

bool KFFOpt_airport::getOptions ( QStringList & list )
{
	QString buffer;

	if ( m_airport.isEmpty() )
	{
		buffer = i18n ( "No airport found\n""Try with the default one ?" );

		switch ( KMessageBox::warningYesNo ( this, buffer ) )
		{

			case KMessageBox::Yes:
			{
				m_airport = "KSFO";
				break;
			}

			default:
			{
				list.clear();
				return false;
			}
		}
	}

	list << "--airport=" + m_airport;

	if ( !m_runway.isEmpty() )
	{
		list << "--runway=" + m_runway.toUpper();
	}

	return true;
}

void KFFOpt_airport::saveSettings()
{
	QStringList list;
	QTreeWidgetItem* item;

	item = ui_widget.favorite->topLevelItem ( 0 );

	while ( item )
	{
		list << item->text ( 0 ) + ":" + item->text ( 1 );
		item = ui_widget.favorite->itemBelow ( item );
	}

	Settings::setAirport_favorite ( list );

	Settings::setAirport_id ( m_airport );
	Settings::setAirport_runway ( m_runway );
	Settings::self()->writeConfig();
}

void KFFOpt_airport::loadSettings()
{
	QTreeWidgetItem* favorite;
	QStringList list, airport;
	QStringList::Iterator it;
	QString buffer;

	list = Settings::airport_favorite();

	for ( it = list.begin() ; it != list.end() ; it++ )
	{
		buffer = *it;
		airport = buffer.split ( ":", QString::SkipEmptyParts );
		favorite = new QTreeWidgetItem ( ui_widget.favorite, airport );
		favorite->setIcon ( 0, m_towerIcon );
		ui_widget.favorite->addTopLevelItem ( favorite );
	}

	m_airport = Settings::airport_id();

	m_runway = Settings::airport_runway();
	m_searchAirport->setPixmap ( m_towerIcon, m_runwayIcon );
	loadAirport ( false );
}

void KFFOpt_airport::getAirportList ( QString id )
{
	QList<QTreeWidgetItem*> items;
	QTreeWidgetItem* item;
	QTreeWidgetItem* child;
	AirportDescription desc;
	AirportDescList list;
	QStringList runway;
	QString buffer;
	int i;

	items = ui_widget.airportList->findItems ( id, Qt::MatchContains );
	QListIterator<QTreeWidgetItem*> it ( items );

	while ( it.hasNext() )
	{
		i = 0;
		item = it.next();
		desc.id = item->text ( 0 );
		desc.name = item->text ( 2 );
		desc.elevation = item->text ( 3 );
		buffer = item->text ( 1 );
		desc.longitude = buffer.section ( ' ', 1 );
		desc.latitude = buffer.section ( ' ', 0, 0 );
		child = item->child ( i );

		while ( child )
		{
			runway << child->text ( 1 );
			buffer = child->text ( 2 );
			runway << buffer.section ( '°', 0, 0 );
			buffer = buffer.section ( '(', 1 ).remove ( ')' );
			runway << buffer.section ( 'x', 0, 0 ).simplified();
			runway << buffer.section ( 'x', 1 ).simplified();
			desc.runway << runway;
			runway.clear();
			child = item->child ( ++i );
		}

		list << desc;

		desc.clear();
	}

	emit ( foundAirports ( list ) );
}

void KFFOpt_airport::getAirport()
{
	emit ( selected ( m_airport ) );
}

void KFFOpt_airport::setSearchAirport ( KFFWin_Airports* widget )
{
	m_searchAirport = widget;
	connect ( ui_widget.btn_FindAirport,
	          SIGNAL ( clicked() ),
	          m_searchAirport,
	          SLOT ( show() )
	        );
	connect ( this,
	          SIGNAL ( searchAirport ( AirportDescription ) ),
	          m_searchAirport,
	          SLOT ( searchAirport ( AirportDescription ) )
	        );

	connect ( m_searchAirport,
	          SIGNAL ( needList ( QString ) ),
	          this,
	          SLOT ( getAirportList ( QString ) )
	        );

	connect ( m_searchAirport,
	          SIGNAL ( addFavorite ( QStringList ) ),
	          this,
	          SLOT ( addToFavorite ( QStringList ) )
	        );

	connect ( this,
	          SIGNAL ( foundAirports ( AirportDescList ) ),
	          m_searchAirport,
	          SLOT ( setList ( AirportDescList ) )
	        );
}

void KFFOpt_airport::setMetarView ( KFFWin_metarView* widget )
{
	m_metarView = widget;
}

/******************************************************************************
 *                                                                            *
 ******************************************************************************/
ReadingThread::ReadingThread()
{
}

ReadingThread::~ReadingThread()
{
}

void ReadingThread::run()
{
	QIODevice *file;
	QTextStream stream;
	QString line, buffer, letterID, tmpInfo, tmpHeading, Coordinates, airportID;
	AirportItem item;
	int number = 0;
	QStringList runway;
	double length, width;
	double longitude, latitude, altitude, declinaison, radial;

	emit ( finished() );
	return;  /// Sniffing out loading ######################
	buffer = Settings::fg_root() + "/Airports/apt.dat.gz";
	file = KFilterDev::deviceForFile ( buffer );

	if ( !file -> open ( QIODevice::ReadOnly ) )

	{
		qDebug() << i18n ( "Cannot open airport file" ) << " " << buffer;
		emit ( finished() );
		return;
	}

	stream.setDevice ( file );

	while ( !stream.atEnd() )
	{
		line = stream.readLine();
		line = line.simplified();

		if ( ( line.left ( 2 ) == "1 " ) || ( line.left ( 2 ) == "17" ) )
		{
			item.parent << line.section ( ' ', 4, 4 ); //airport id
			item.parent << "";
			item.parent << line.section ( ' ', 5 ); //airport name

			buffer = line.section ( ' ', 1, 1 );
			altitude = buffer.toDouble();

			if ( buffer.contains ( '-' ) == 0 )
			{
				buffer = buffer.rightJustified ( 5, '0' );
			}
			else
			{
				buffer = "M" + buffer.remove ( '-' ).rightJustified ( 4, '0' );
			}

			item.parent << buffer; //airport elevation

			while ( !line.isEmpty() )
			{
				line = stream.readLine();

				if ( ( line.left ( 2 ) == "10" ) &&
				        ( line.contains ( "xxx", Qt::CaseSensitive ) == 0 ) )
				{
					line = line.simplified();
					runway << "";
					runway << line.section ( ' ', 3, 3 );

					length = line.section ( ' ', 5, 5 ).toDouble() * 0.3048006;
					width = line.section ( ' ', 8, 8 ).toDouble() * 0.3048006;

					buffer.clear();
					tmpInfo.clear();
					tmpInfo = "(";
					tmpInfo.append ( buffer.setNum ( length, 'f', 0 ) );
					buffer.clear();
					tmpInfo.append ( "m x " );
					tmpInfo.append ( buffer.setNum ( width, 'f', 0 ) );
					tmpInfo.append ( "m)" );

					latitude = line.section ( ' ', 1, 1 ).toDouble();
					longitude = line.section ( ' ', 2, 2 ).toDouble();
					declinaison = getMagneticOffset ( longitude, latitude, altitude );
					radial = line.section ( ' ', 4, 4 ).simplified().toDouble();
					radial = radial - declinaison;
					tmpHeading = buffer.setNum ( radial, 'f', 0 );

					if ( line.section ( ' ', 3, 3 ).contains ( 'H' ) > 0 )
					{
						runway << tmpInfo;
					}
					else
					{
						runway << tmpHeading + "° " + tmpInfo;
					}

					radial = radial + 180.0;

					tmpHeading = buffer.setNum ( radial, 'f', 0 );

					tmpInfo = tmpHeading + "° " + tmpInfo;

					Coordinates.clear();
					latitude = line.section ( ' ', 1, 1 ).toDouble();

					if ( latitude < 0 )
					{
						Coordinates = Coordinates.append ( "S" );
					}
					else
					{
						Coordinates = Coordinates.append ( "N" );
					}

					Coordinates = Coordinates.append ( buffer.setNum ( latitude, 'f', 3 ).remove ( '-' ) );

					Coordinates = Coordinates.append ( " " );
					longitude = line.section ( ' ', 2, 2 ).toDouble();

					if ( longitude < 0 )
					{
						Coordinates = Coordinates.append ( "W" );
					}
					else
					{
						Coordinates = Coordinates.append ( "E" );
					}

					item.coordinates = Coordinates.append ( buffer.setNum ( longitude, 'f', 3 ).remove ( '-' ) );

					//runway << Coordinates;
					item.childs << runway;
					runway.clear();

					//next is because runway have two side

					if ( line.section ( ' ', 3, 3 ).toInt() > 0 )
					{
						if ( line.section ( ' ', 3, 3 ).toInt() <= 18 )
						{
							buffer = buffer.setNum ( line.section ( ' ', 3, 3 ).toInt() + 18, 10 );
						}
						else
						{
							buffer = buffer.setNum ( line.section ( ' ', 3, 3 ).toInt() - 18, 10 );
						}
					}
					else
					{
						letterID = line.section ( ' ', 3, 3 );

						if ( letterID.right ( 1 ) == "L" )
						{
							if ( line.section ( ' ', 3, 3 ).remove ( 'L' ).toInt() <= 18 )
							{
								buffer = buffer.setNum ( line.section ( ' ', 3, 3 ).remove ( 'L' ).toInt() + 18, 10 ) + "R";
							}

							if ( line.section ( ' ', 3, 3 ).remove ( 'L' ).toInt() > 18 )
							{
								buffer = buffer.setNum ( line.section ( ' ', 3, 3 ).remove ( 'L' ).toInt() - 18, 10 ) + "R";
							}
						}

						if ( letterID.right ( 1 ) == "R" )
						{
							if ( line.section ( ' ', 3, 3 ).remove ( 'R' ).toInt() <= 18 )
							{
								buffer = buffer.setNum ( line.section ( ' ', 3, 3 ).remove ( 'R' ).toInt() + 18, 10 ) + "L";
							}

							if ( line.section ( ' ', 3, 3 ).remove ( 'R' ).toInt() > 18 )
							{
								buffer = buffer.setNum ( line.section ( ' ', 3, 3 ).remove ( 'R' ).toInt() - 18, 10 ) + "L";
							}
						}

						if ( ( letterID.right ( 1 ) != "R" ) && ( letterID.right ( 1 ) != "L" ) )
						{
							if ( line.section ( ' ', 3, 3 ).remove ( letterID.right ( 1 ) ).toInt() <= 18 )
							{
								buffer = buffer.setNum (
								             line.section ( ' ', 3, 3 ).remove ( letterID.right ( 1 ) ).toInt() + 18, 10 )
								         + letterID.right ( 1 );
							}

							if ( line.section ( ' ', 3, 3 ).remove ( letterID.right ( 1 ) ).toInt() > 18 )
							{
								buffer = buffer.setNum (
								             line.section ( ' ', 3, 3 ).remove ( letterID.right ( 1 ) ).toInt() - 18, 10 )
								         + letterID.right ( 1 );
							}

							if ( line.section ( ' ', 3, 3 ).contains ( 'H' ) > 0 )
							{
								buffer.clear();
							}
						}
					}

					if ( !buffer.isEmpty() )
					{
						runway << "";
						runway << buffer;
						runway << tmpInfo;
						item.childs << runway;
						runway.clear();
					}
				}
			}

			emit ( insertItem ( item ) );

			item.clear();
		}

		number++;

		if ( number > 20 )
		{
			// To let main window updating
			QCoreApplication::processEvents();

			msleep ( 1 );
			number = 0;
		}
	}

	file->close();

	delete file;
	emit ( finished() );
}


/******************************************************************************
 *                                                                            *
 ******************************************************************************/
AirportItem::AirportItem()
{
}

AirportItem::~AirportItem()
{
}

void AirportItem::clear()
{
	parent.clear();
	childs.clear();
}
