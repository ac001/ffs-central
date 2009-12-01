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
 *     (___)_)   File : win_airports.cpp                    ||--|| *         *
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

#include "win_airports.h"
#include "settings.h"
#include "shared.h"

#include <kmessagebox.h>
#include <kfilterdev.h>
#include <kmenu.h>

#include <QIODevice>
#include <QFile>
#include <QTextStream>

#include <cmath>
#include <ctime>

KFFWin_Airports::KFFWin_Airports( QWidget *parent )
		: QWidget( parent )
{
	ui_widget.setupUi( this );
	qRegisterMetaType<AirportData>();
	qRegisterMetaType<AirportDescription>();
	qRegisterMetaType<AirportDescList>();

	m_thread = new SearchThread();
	m_coordinates = new KFFWin_Coordinates( 0 );
	m_progress = 0;

	connect( m_thread,
	         SIGNAL( finished( AirportData ) ),
	         SLOT( loadFinished( AirportData ) )
	       );

	connect( m_thread,
	         SIGNAL( progress() ),
	         SLOT( incrementProgress() )
	       );

	connect( m_thread,
	         SIGNAL( fileChanged( QString ) ),
	         SLOT( changeProgress( QString ) )
	       );

	connect( ui_widget.btn_Find,
	         SIGNAL( clicked() ),
	         SLOT( searchMyAirport() )
	       );

	connect( ui_widget.btn_AddToFavorite,
	         SIGNAL( clicked() ),
	         SLOT( favoriteRequest() )
	       );
	connect( ui_widget.treeWidget_Airport,
	         SIGNAL( itemDoubleClicked( QTreeWidgetItem*, int ) ),
	         this,
	         SLOT( setAirport( QTreeWidgetItem* ) )
	       );
	connect( ui_widget.RB_researchCoordinate,
	         SIGNAL( toggled( bool ) ),
	         m_coordinates,
	         SLOT( setVisible( bool ) )
	       );
	connect( m_coordinates,
	         SIGNAL( queryCoordinates( QString ) ),
	         SLOT( setCoordinates( QString ) )
	       );
	connect( ui_widget.RB_researchCoordinate,
	         SIGNAL( pressed( ) ),
	         ui_widget.lineedit_Airport,
	         SLOT( clear() )
	       );
	connect( ui_widget.RB_researchName,
	         SIGNAL( pressed( ) ),
	         ui_widget.lineedit_Airport,
	         SLOT( clear() )
	       );
	connect( ui_widget.lineedit_Airport,
	         SIGNAL( returnPressed( ) ),
	         SLOT( searchMyAirport() )
	       );
}

KFFWin_Airports::~KFFWin_Airports()
{
	m_thread->quit();
	delete m_thread;
}

void KFFWin_Airports::showContextMenu( const QPoint &pos )
{
	QAction* nav1;
	QAction* nav1stby;
	QAction* nav1radial;	
	QAction* nav2;
	QAction* nav2stby;
	QAction* nav2radial;
	QAction* dme;
	QAction* adf;
	QAction* adfstdby;
	QAction* adfrot;
	QAction* com1;
	QAction* com1stdby;
	QAction* com2;
	QAction* com2stdby;
	KMenu menu( this );

	nav1 = new QAction( tr2i18n( "NAV1" ), this );
	nav1->setStatusTip( tr2i18n( "Set this frequency to NAV1" ) );
	connect( nav1, SIGNAL( triggered() ), this, SLOT( setNav1() ) );
	
	nav1stby = new QAction( tr2i18n( "NAV1 standby" ), this );
	nav1stby->setStatusTip( tr2i18n( "Set this frequency to NAV1 standby" ) );
	connect( nav1stby, SIGNAL( triggered() ), this, SLOT( setNav1stby() ) );
	
	nav1radial = new QAction( tr2i18n( "NAV1 radial" ), this );
	nav1radial->setStatusTip( tr2i18n( "Set this radial to NAV1" ) );
	connect( nav1radial, SIGNAL( triggered() ), this, SLOT( setNav1radial() ) );

	nav2 = new QAction( tr2i18n( "NAV2" ), this );
	nav2->setStatusTip( tr2i18n( "Set this frequency to NAV2" ) );
	connect( nav2, SIGNAL( triggered() ), this, SLOT( setNav2() ) );
	
	nav2stby = new QAction( tr2i18n( "NAV2 standby" ), this );
	nav2stby->setStatusTip( tr2i18n( "Set this frequency to NAV2 standby" ) );
	connect( nav2stby, SIGNAL( triggered() ), this, SLOT( setNav2stby() ) );
	
	nav2radial = new QAction( tr2i18n( "NAV2 radial" ), this );
	nav2radial->setStatusTip( tr2i18n( "Set this radial to NAV2" ) );
	connect( nav2radial, SIGNAL( triggered() ), this, SLOT( setNav2radial() ) );

	dme = new QAction( tr2i18n( "DME" ), this );
	dme->setStatusTip( tr2i18n( "Set this frequency to DME" ) );
	connect( dme, SIGNAL( triggered() ), this, SLOT( setDme() ) );
	
	adf = new QAction( tr2i18n( "ADF" ), this );
	adf->setStatusTip( tr2i18n( "Set this frequency to ADF" ) );
	connect( adf, SIGNAL( triggered() ), this, SLOT( setAdf() ) );
	
	adfstdby = new QAction( tr2i18n( "ADF stanby" ), this );
	adfstdby->setStatusTip( tr2i18n( "Set this frequency to ADF standby" ) );
	connect( adfstdby, SIGNAL( triggered() ), this, SLOT( setAdfstdby() ) );
	
	adfrot = new QAction( tr2i18n( "ADF rotation" ), this );
	adfrot->setStatusTip( tr2i18n( "Set this rotation to ADF" ) );
	connect( adfrot, SIGNAL( triggered() ), this, SLOT( setAdfrot()() ) );
	
	com1 = new QAction( tr2i18n( "COM1" ), this );
	com1->setStatusTip( tr2i18n( "Set this frequency to COM1" ) );
	connect( com1, SIGNAL( triggered() ), this, SLOT( setCom1() ) );
	
	com1stdby = new QAction( tr2i18n( "COM1 standby" ), this );
	com1stdby->setStatusTip( tr2i18n( "Set this frequency to COM1 standby" ) );
	connect( com1stdby, SIGNAL( triggered() ), this, SLOT( setCom1stdby() ) );
	
	com2 = new QAction( tr2i18n( "COM2" ), this );
	com2->setStatusTip( tr2i18n( "Set this frequency to COM2" ) );
	connect( com2, SIGNAL( triggered() ), this, SLOT( setCom2() ) );
	
	com2stdby = new QAction( tr2i18n( "COM2 standby" ), this );
	com2stdby->setStatusTip( tr2i18n( "Set this frequency to COM2 standby" ) );
	connect( com2stdby, SIGNAL( triggered() ), this, SLOT( setCom2stdby() ) );
	
	menu.addAction( nav1 );
	menu.addAction( nav1stby );
	menu.addAction( nav1radial );	
	menu.addAction( nav2 );
	menu.addAction( nav2stby );
	menu.addAction( nav2radial );
	menu.addAction( dme );
	menu.addAction( adf );
	menu.addAction( adfstdby );
	menu.addAction( adfrot );
	menu.addAction( com1 );
	menu.addAction( com1stdby );
	menu.addAction( com2 );
	menu.addAction( com2stdby );
	menu.exec( );//mapToGlobal( pos + ui_widget.favorite->pos() ) );
}

void KFFWin_Airports::setPixmap( QPixmap& tower, QPixmap& runway )
{
	m_towerPixmap = tower;
	m_runwayPixmap = runway;
}

void KFFWin_Airports::searchMyAirport()
{
	searchAirport();
}

void KFFWin_Airports::setAirport( QTreeWidgetItem* item )
{
	if ( item )
	{
		ui_widget.lineedit_Airport->setText( item->text( 0 ) );
		searchAirport();
	}
}

void KFFWin_Airports::searchAirport( AirportDescription airport )
{
	bool searchlist = true;
	QStringList params;
	QTreeWidgetItem* item;
	QTreeWidgetItem* child;

	if ( !airport.id.isEmpty() )
	{
		ui_widget.lineedit_Airport->setText( airport.id );
		searchlist = false;
	}

	ui_widget.treeWidget_Airport->clear();

	ui_widget.lineedit_AirportID->clear();
	ui_widget.lineedit_AirportElevation->clear();
	ui_widget.lineedit_AirportName->clear();
	ui_widget.lineedit_Longitude->clear();
	ui_widget.lineedit_Latitude->clear();
	ui_widget.treeWidget_runway->clear();
	ui_widget.treeWidget_comOthers->clear();
	ui_widget.treeWidget_comAtis->clear();
	ui_widget.treeWidget_comTower->clear();
	ui_widget.treeWidget_NAV->clear();


	if ( !ui_widget.lineedit_Airport->text().isEmpty() )
	{
		if ( searchlist )
		{
			emit( needList( ui_widget.lineedit_Airport->text() ) );
		}
		else
		{
			params << airport.id << airport.name;
			item = new QTreeWidgetItem( ui_widget.treeWidget_Airport, params );
			item->setIcon( 0, m_towerPixmap );
			ui_widget.treeWidget_Airport->addTopLevelItem( item );
			ui_widget.lineedit_AirportID->setText( airport.id );
			ui_widget.lineedit_AirportElevation->setText( airport.elevation );
			ui_widget.lineedit_AirportName->setText( airport.name );
			ui_widget.lineedit_Longitude->setText( airport.longitude );
			ui_widget.lineedit_Latitude->setText( airport.latitude );
			QListIterator<QStringList> itl( airport.runway );

			while ( itl.hasNext() )
			{
				child = new QTreeWidgetItem( ui_widget.treeWidget_runway, itl.next() );
				child->setIcon( 0, m_runwayPixmap );
				ui_widget.treeWidget_runway->addTopLevelItem( child );
			}

			search( airport.id, airport.longitude, airport.latitude );
		}
	}
}

void KFFWin_Airports::search( QString id,
                              QString longitude,
                              QString latitude
                            )
{
	if ( !m_progress )
	{
		m_progress = new KProgressDialog( this,
		                                  i18n( "Airport informations" ),
		                                  i18n( "Search airport informations" )
		                                );
	}

	m_progress->setAttribute( Qt::WA_DeleteOnClose );

	m_progress->setAutoClose( false );
	m_progress->setAutoReset( true );
	m_progress->setAllowCancel( false );
	m_progress->progressBar()->setRange( 0, 1000 );
	m_progress->setMinimumDuration( 1000 );

	m_progress->show();

	m_thread->setAirport( id,
	                      longitude.replace( 'W', "-" ).remove( "E" ).toDouble(),
	                      latitude.replace( 'S', "-" ).remove( "N" ).toDouble()
	                    );
	m_thread->start();
	m_thread->setPriority( QThread::NormalPriority );
}

void KFFWin_Airports::incrementProgress()
{
	m_progress->progressBar()->setValue( m_progress->progressBar()->value() + 1 );
}

void KFFWin_Airports::changeProgress( QString text )
{
	m_progress->setLabelText( i18n( "Search airport in file" ) + " " + text );
}

void KFFWin_Airports::loadFinished( AirportData data )
{
	QTreeWidgetItem* item;
	QList<QTreeWidgetItem*> items;

	m_thread->terminate();
	m_thread->wait();

	if ( m_progress )
	{
		m_progress->close();
		m_progress = 0;
	}

	if ( !data.found )
	{
		KMessageBox::sorry( this, i18n( "Airport not found" ) );
		return;
	}

	QListIterator<QStringList> itOthers( data.comOthers );

	while ( itOthers.hasNext() )
	{
		item = new QTreeWidgetItem( ui_widget.treeWidget_comOthers, itOthers.next() );
		//item->setIcon( 0, m_runwayPixmap );
		ui_widget.treeWidget_comOthers->addTopLevelItem( item );
	}

	QListIterator<QStringList> itATIS( data.comATIS );

	while ( itATIS.hasNext() )
	{
		item = new QTreeWidgetItem( ui_widget.treeWidget_comAtis, itATIS.next() );
		//item->setIcon( 0, m_runwayPixmap );
		ui_widget.treeWidget_comAtis->addTopLevelItem( item );
	}

	QListIterator<QStringList> itTower( data.comTower );

	while ( itTower.hasNext() )
	{
		item = new QTreeWidgetItem( ui_widget.treeWidget_comTower, itTower.next() );
		//item->setIcon( 0, m_runwayPixmap );
		ui_widget.treeWidget_comTower->addTopLevelItem( item );
	}

	QListIterator<QStringList> itNavaids( data.navaids );

	while ( itNavaids.hasNext() )
	{
		item = new QTreeWidgetItem( ui_widget.treeWidget_NAV, itNavaids.next() );
		//item->setIcon( 0, m_runwayPixmap );
		ui_widget.treeWidget_NAV->addTopLevelItem( item );
	}

	QMapIterator<QString, QString> itILS( data.runwayILS );;

	while ( itILS.hasNext() )
	{
		itILS.next();
		items = ui_widget.treeWidget_runway->findItems( itILS.key(), Qt::MatchExactly, 0 );
		QListIterator<QTreeWidgetItem*> itItem( items );

		if ( itItem.hasNext() )
		{
			itItem.next()->setText( 4, itILS.value() );
		}
	}

}

void KFFWin_Airports::setList( AirportDescList list )
{
	AirportDescription airport;
	QStringList params;
	QTreeWidgetItem* item;
	QTreeWidgetItem* child;
	bool inserted = false;

	QListIterator<AirportDescription> it( list );

	while ( it.hasNext() )
	{
		airport = it.next();
		params << airport.id << airport.name;
		item = new QTreeWidgetItem( ui_widget.treeWidget_Airport, params );
		item->setIcon( 0, m_towerPixmap );
		ui_widget.treeWidget_Airport->addTopLevelItem( item );

		if ( !inserted )
		{
			ui_widget.lineedit_AirportID->setText( airport.id );
			ui_widget.lineedit_AirportElevation->setText( airport.elevation );
			ui_widget.lineedit_AirportName->setText( airport.name );
			ui_widget.lineedit_Longitude->setText( airport.longitude );
			ui_widget.lineedit_Latitude->setText( airport.latitude );
			QListIterator<QStringList> itl( airport.runway );

			while ( itl.hasNext() )
			{
				child = new QTreeWidgetItem( ui_widget.treeWidget_runway, itl.next() );
				child->setIcon( 0, m_runwayPixmap );
				ui_widget.treeWidget_runway->addTopLevelItem( child );
			}

			inserted = true;

			if ( list.count() == 1 )
			{
				search( airport.id, airport.longitude, airport.latitude );
			}
		}

		airport.clear();

		params.clear();
	}
}

void KFFWin_Airports::favoriteRequest()
{
	QStringList list;

	if ( !ui_widget.lineedit_AirportID->text().isEmpty() )
	{
		list << ui_widget.lineedit_AirportID->text();
		list << ui_widget.lineedit_AirportName->text();
		emit( addFavorite( list ) );
	}
}

void KFFWin_Airports::setCoordinates( QString id )
{
	ui_widget.lineedit_Airport->setText( id );
	searchAirport();
}
void KFFWin_Airports::setNav1()
{
}

void KFFWin_Airports::setNav1stby()
{
}

void KFFWin_Airports::setNav1radial()
{
}

void KFFWin_Airports::setNav2()
{
}

void KFFWin_Airports::setNav2stby()
{
}

void KFFWin_Airports::setNav2radial()
{
}

void KFFWin_Airports::setDme()
{
}

void KFFWin_Airports::setAdf()
{
}

void KFFWin_Airports::setAdfstdby()
{
}

void KFFWin_Airports::setAdfrot()
{
}

void KFFWin_Airports::setCom1()
{
}

void KFFWin_Airports::setCom1stdby()
{
}

void KFFWin_Airports::setCom2()
{
}

void KFFWin_Airports::setCom2stdby()
{
}

/******************************************************************************
 *                                                                            *
 ******************************************************************************/
SearchThread::SearchThread()
{
}

SearchThread::~SearchThread()
{
}

void SearchThread::setAirport( QString id, double longitude, double latitude )
{
	m_id = id;
	m_longitude = longitude;
	m_latitude = latitude;
}

void SearchThread::run()
{
	QIODevice *file;
	QFile file2;
	QTextStream stream;
	QString line, buffer;
	int number = 0;
	QStringList list, tmp;
	AirportData data;
	double longitude = 0.0, latitude = 0.0;
	double distance = 0.0;
	bool found = false;

	buffer = Settings::fg_root() + "/Airports/apt.dat.gz";
	emit( fileChanged( "Airports/apt.dat.gz" ) );
	file = KFilterDev::deviceForFile( buffer );

	if ( !file -> open( QIODevice::ReadOnly ) )

	{
		qDebug() << i18n( "Cannot open airport file" ) << " " << buffer;
		emit( finished( data ) );
		return;
	}

	stream.setDevice( file );

	while ( !data.found && !stream.atEnd() )
	{
		line = stream.readLine();
		line = line.simplified();

		if (( line.left( 2 ) == "1 " ) || ( line.left( 2 ) == "17" ) )
		{
			buffer = line.section( ' ', 4, 4 ); //airport id

			if ( buffer == m_id )
			{
				data.found = true;
			}

			while ( !line.isEmpty() )
			{
				line = stream.readLine();

				if ( data.found && ( line.left( 1 ) == "5" ) ) // If it's a COM line
				{
					line = line.simplified();

					if ( !line.contains( "ATIS", Qt::CaseSensitive ) &&
					        ( !line.contains( "TWR", Qt::CaseSensitive ) ) )
					{
						buffer = line.section( ' ', 1, 1 ).left( 3 );
						buffer += "." + line.section( ' ', 1, 1 ).right( 2 );
						buffer += " " + line.section( ' ', 2 );
						list << buffer;
						data.comOthers << list;
						list.clear();
					}
				}
			}
		}

		number++;

		if ( number > 20 )
		{
			emit( progress() );
			// To let main window updating
			QCoreApplication::processEvents();

			msleep( 10 );
			number = 0;
		}
	}

	file->close();

	delete file;
	stream.reset();
	list.clear();


	//ATIS frequencies
	file2.setFileName( Settings::fg_root() + "/ATC/default.atis" );
	emit( fileChanged( "ATC/default.atis" ) );

	if ( !file2.open( QFile::ReadOnly ) )
	{
		qDebug() << i18n( "Cannot open atis file" ) << " " << buffer;
	}
	else
	{
		stream.setDevice( &file2 );

		while ( !stream.atEnd() )
		{
			buffer = stream.readLine();

			if ( buffer.contains( m_id, Qt::CaseSensitive ) )
			{
				list << buffer.simplified().section( ' ', 4, 4 );
				data.comATIS << list;
				list.clear();
			}
		}

		file2.close();

		stream.reset();
	}


	//Tower frequencies
	file2.setFileName( Settings::fg_root() + "/ATC/default.tower" );

	emit( fileChanged( "ATC/default.tower" ) );

	if ( !file2.open( QFile::ReadOnly ) )
	{
		qDebug() << i18n( "Cannot open tower file" ) << " " << buffer;
	}
	else
	{
		stream.setDevice( &file2 );

		while ( !stream.atEnd() )
		{
			buffer = stream.readLine();

			if ( buffer.contains( m_id, Qt::CaseSensitive ) )
			{
				list << buffer.simplified().section( ' ', 4, 4 );
				data.comTower << list;
				list.clear();
			}
		}

		file2.close();

		stream.reset();
	}


	buffer = Settings::fg_root() + "/Navaids/nav.dat.gz";

	emit( fileChanged( "Navaids/nav.dat.gz" ) );

	file = KFilterDev::deviceForFile( buffer );

	if ( !file -> open( QIODevice::ReadOnly ) )

	{
		qDebug() << i18n( "Cannot open airport file" ) << " " << buffer;
		emit( finished( data ) );
		return;
	}

	stream.setDevice( file );

	number = 0;

	while ( !stream.atEnd() )
	{
		line = stream.readLine();
		line = line.simplified();

		if (( line.left( 1 ) == "2" ) || ( line.left( 1 ) == "3" )
		        || ( line.left( 2 ) == "12" ) || ( line.left( 2 ) == "13" ) )
		{
			buffer = line;
			longitude = buffer.section( ' ', 2, 2 ).toDouble();
			latitude = buffer.section( ' ', 1, 1 ).toDouble();
			distance = calculateDistance( m_longitude, m_latitude, longitude, latitude );
			//qDebug() << distance;

			if ( buffer.left( 1 ) == "3" )
			{
				if (( distance <= 15.0 ) && ( !buffer.section( " ", -1, -1 ).contains( "ILS" ) ) )
				{
					list.clear();
					list << buffer.section( ' ', -1, -1 );
					list << buffer.section( ' ', 7, 7 );
					list << buffer.section( ' ', 4, 4 ).left( 3 ) + "." + buffer.section( ' ', 4, 4 ).right( 2 );
					list << "MHz";
					list << buffer.section( ' ', 8 ).remove( buffer.section( ' ', -1, -1 ) );
				}
			}

			if (( buffer.left( 2 ) == "12" ) || ( buffer.left( 2 ) == "13" ) )
			{
				if (( distance <= 15.0 ) && ( !buffer.section( " ", -1, -1 ).contains( "ILS" ) ) )
				{
					list.clear();
					list << buffer.section( ' ', -1, -1 );
					list << buffer.section( ' ', 7, 7 );
					list << buffer.section( ' ', 4, 4 ).left( 3 ) + "." + buffer.section( ' ', 4, 4 ).right( 2 );
					list << "MHz";
					list << buffer.section( ' ', 8 ).remove( buffer.section( ' ', -1, -1 ) );
				}
			}

			if ( buffer.left( 1 ) == "2" )
			{
				if ( distance <= 15.0 )
				{
					list.clear();
					list << buffer.section( ' ', -1, -1 );
					list << buffer.section( ' ', 7, 7 );
					list << buffer.section( ' ', 4, 4 );
					list << "kHz";
					list << buffer.section( ' ', 8 ).remove( buffer.section( ' ', -1, -1 ) );
				}
			}

			QListIterator<QStringList> itNavaids( data.navaids );

			while ( itNavaids.hasNext() )
			{
				if ( itNavaids.next() == list )
				{
					found = true;
				}
			}

			if ( !found && !list.isEmpty() )
			{
				data.navaids << list;
			}

			list.clear();

			found = false;
		}

		//ILS
		if (( line.left( 1 ) == "4" ) || ( line.left( 1 ) == "5" ) )
		{
			if ( line.section( ' ', 8, 8 ) == m_id )
			{
				buffer = line.section( ' ', 4, 4 );
				data.runwayILS[line.section( ' ', 9, 9 ).toUpper()] =
				    buffer.left( 3 ) + "." + buffer.right( 2 );
			}
		}

		number++;

		if ( number > 20 )
		{
			emit( progress() );
			// To let main window updating
			QCoreApplication::processEvents();

			msleep( 10 );
			number = 0;
		}
	}

	file -> close();

	delete file;

	emit( finished( data ) );
}

/******************************************************************************
 *                                                                            *
 ******************************************************************************/
AirportData::AirportData()
{
	found = false;
}

AirportData::~AirportData()
{
}

void AirportData::clear()
{
	found = false;
	comOthers.clear();
	comATIS.clear();
	comTower.clear();
	id.clear();
}

/******************************************************************************
 *                                                                            *
 ******************************************************************************/

AirportDescription::AirportDescription()
{
}

AirportDescription::~AirportDescription()
{
}

void AirportDescription::clear()
{
	id.clear();
	name.clear();
	elevation.clear();
	latitude.clear();
	longitude.clear();
	runway.clear();
}

