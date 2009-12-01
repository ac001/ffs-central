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

#include "win_flightplan.h"
#include "settings.h"
#include "shared.h"

#include <kmessagebox.h>
#include <kfilterdev.h>
#include <kmenu.h>
#include <kiconloader.h>
#include <klineedit.h>
#include <kstandarddirs.h>

#include <QIODevice>
#include <QFile>
#include <QTextStream>
#include <QTreeWidget>
#include <QPainter>
#include <QListView>
#include <QDir>
#include <QFile>
#include <QIcon>
#include <QDesktopWidget>

KFFWin_Flightplan::KFFWin_Flightplan( QWidget *parent )
		: QWidget( parent )
{
	KIconLoader loader;
	QPixmap pixmap;
	QIcon icon;
	QRect rect;

	rect = QApplication::desktop()->screenGeometry();
	if ( rect.width() >= 1280 )
	{
		setMinimumWidth( 1280 );
	}

	ui_widget.setupUi( this );
	qRegisterMetaType<NavDataList>();
	m_editing = false;

	pixmap = loader.loadIcon( "arrow-left", KIconLoader::Toolbar );
	icon.addPixmap( pixmap );
	ui_widget.kpushbutton_next->setIcon( icon );
	pixmap = loader.loadIcon( "arrow-right", KIconLoader::Toolbar );
	icon.addPixmap( pixmap );
	ui_widget.kpushbutton_previous->setIcon( icon );

	m_progress = 0;
	m_thread = new NavThread();

	ui_widget.kpushbutton_previous->setEnabled( false );
	ui_widget.kpushbutton_next->setEnabled( false );

	connect( m_thread,
	         SIGNAL( finished( NavDataList ) ),
	         SLOT( loadFinished( NavDataList ) )
	       );

	connect( m_thread,
	         SIGNAL( progress() ),
	         SLOT( incrementProgress() )
	       );

	connect( ui_widget.pushbutton_search,
	         SIGNAL( clicked() ),
	         SLOT( search() )
	       );

	connect( ui_widget.lineEdit_search,
	         SIGNAL( returnPressed() ),
	         SLOT( search() )
	       );

	connect( ui_widget.pushbutton_add,
	         SIGNAL( clicked() ),
	         SLOT( add() )
	       );

	connect( ui_widget.kpushbutton_next,
	         SIGNAL( clicked() ),
	         SLOT( next() )
	       );

	connect( ui_widget.kpushbutton_previous,
	         SIGNAL( clicked() ),
	         SLOT( previous() )
	       );

	connect( ui_widget.pushbutton_open,
	         SIGNAL( clicked() ),
	         SLOT( open() )
	       );

	connect( ui_widget.pushbutton_save,
	         SIGNAL( clicked() ),
	         SLOT( save() )
	       );

	ui_widget.treewidget_navaids->setContextMenuPolicy( Qt::CustomContextMenu );
	connect( ui_widget.treewidget_navaids,
	         SIGNAL( customContextMenuRequested( const QPoint & ) ),
	         this,
	         SLOT( showFavoriteContextMenu( const QPoint & ) )
	       );

	connect( ui_widget.treewidget_navaids,
	         SIGNAL( itemActivated( QTreeWidgetItem*, int ) ),
	         this,
	         SLOT( itemActivated( QTreeWidgetItem*, int ) )
	       );

	connect( ui_widget.toolButton_up,
	         SIGNAL( clicked() ),
	         SLOT( moveItemUp() )
	       );

	connect( ui_widget.toolButton_down,
	         SIGNAL( clicked() ),
	         SLOT( moveItemDown() )
	       );

	connect( ui_widget.treewidget_navaids,
	         SIGNAL( currentItemChanged( QTreeWidgetItem *, QTreeWidgetItem * ) ),
	         this,
	         SLOT( saveSettings() )
	       );
}

KFFWin_Flightplan::~KFFWin_Flightplan()
{
}

void KFFWin_Flightplan::search()
{
	if ( !m_progress )
	{
		m_progress = new KProgressDialog( this,
		                                  i18n( "Navaids informations" ),
		                                  i18n( "Search navaids informations" )
		                                );
	}

	m_progress->setAttribute( Qt::WA_DeleteOnClose );

	m_progress->setAutoClose( false );
	m_progress->setAutoReset( false );
	m_progress->setAllowCancel( false );
	m_progress->progressBar()->setRange( 0, NB_LINE / NB_LINE_BEFORE_UPDATE );
	m_progress->setMinimumDuration( 1000 );

	m_progress->show();

	m_thread->setText( ui_widget.lineEdit_search->text() );
	m_thread->start();
	m_thread->setPriority( QThread::NormalPriority );
}

void KFFWin_Flightplan::incrementProgress()
{
	m_progress->progressBar()->setValue( m_progress->progressBar()->value() + 1 );
}

void KFFWin_Flightplan::loadFinished( NavDataList datalist )
{
	m_thread->terminate();
	m_thread->wait();

	if ( m_progress )
	{
		m_progress->close();
		m_progress = 0;
	}

	m_datalist = datalist;

	m_it = m_datalist.begin();

	if ( m_it == m_datalist.end() || m_it->id.isEmpty() )
	{
		KMessageBox::sorry( this, i18n( "Navaids not found" ) );
		return;
	}

	m_editing = false;

	setNavaids( *m_it );

	ui_widget.kpushbutton_previous->setEnabled( false );
	ui_widget.kpushbutton_next->setEnabled( true );
}

void KFFWin_Flightplan::setNavaids( NavaidsData & data )
{
	QTableWidgetItem* item = 0;
	QString buffer;
	QBrush black( QColor( 0, 0, 0, 255 ) );
	QBrush grey( QColor( 200, 200, 200, 255 ) );
	QBrush *brush;


	if ( m_editing )
	{
		//ui_widget.tableWidget_data->setEnabled( false );
		brush = &grey;
		ui_widget.kpushbutton_previous->setEnabled( false );
		ui_widget.kpushbutton_next->setEnabled( false );
		ui_widget.spinbox_altitude->setValue( data.altitude );
		ui_widget.pushbutton_add->setText( i18n( "Update" ) );
	}
	else
	{
		//ui_widget.tableWidget_data->setEnabled( true );
		brush = &black;
		ui_widget.pushbutton_add->setText( i18n( "Add" ) );
	}

	brush->setStyle( Qt::NoBrush );

	item = ui_widget.tableWidget_data->item( 0, 0 );

	if ( !item )
	{
		qDebug() << "No item";
		return;
	}

	item->setForeground( *brush );

	item->setText( data.id );

	item = ui_widget.tableWidget_data->item( 1, 0 );

	if ( !item )
	{
		qDebug() << "No name item";
		return;
	}

	item->setForeground( *brush );

	item->setText( data.name );

	item = ui_widget.tableWidget_data->item( 3, 0 );
	item->setForeground( *brush );
	item->setText( data.type );

	if ( data.type.contains( "ndb", Qt::CaseInsensitive ) )
	{
		buffer.setNum( data.frequency, 'f', 0 );
		buffer.append( " kHz" );
	}
	else
	{
		buffer.setNum( data.frequency, 'f', 2 );
		buffer.append( " MHz" );
	}

	item = ui_widget.tableWidget_data->item( 2, 0 );

	item->setForeground( *brush );
	item->setText( buffer );

	buffer.clear();
	buffer.setNum( data.longitude, 'f', 6 );
	item = ui_widget.tableWidget_data->item( 4, 0 );
	item->setForeground( *brush );
	item->setText( buffer );

	buffer.clear();
	buffer.setNum( data.latitude, 'f', 6 );
	item = ui_widget.tableWidget_data->item( 5, 0 );
	item->setForeground( *brush );
	item->setText( buffer );
}

void KFFWin_Flightplan::previous()
{
	if (( m_datalist.count() == 0 ) || ( m_it == m_datalist.begin() ) )
	{
		ui_widget.kpushbutton_previous->setEnabled( false );
		return;
	}

	m_it--;

	if ( m_it == m_datalist.begin() )
	{
		ui_widget.kpushbutton_previous->setEnabled( false );
	}

	ui_widget.kpushbutton_next->setEnabled( true );

	setNavaids( *m_it );
}

void KFFWin_Flightplan::next()
{
	if ( m_datalist.count() == 0 )
	{
		ui_widget.kpushbutton_next->setEnabled( false );
		return;
	}

	m_it++;

	ui_widget.kpushbutton_previous->setEnabled( true );

	if (( m_it + 1 ) == m_datalist.end() )
	{
		ui_widget.kpushbutton_next->setEnabled( false );
	}

	setNavaids( *m_it );
}

void KFFWin_Flightplan::add()
{
	QTableWidgetItem* titem = 0;
	QTreeWidgetItem* item = 0;
	QString buffer;
	uint nb = ui_widget.treewidget_navaids->topLevelItemCount();
	int i;

	if ( m_editing )
	{
		item = ui_widget.treewidget_navaids->currentItem();

		if ( item )
		{
			item->setText( 4, ui_widget.spinbox_altitude->text() );
		}

		for ( i = 0 ; i <= 5 ; ++i )
		{
			switch ( i )
			{

				case 0:
				{
					buffer = i18n( "ID" );
					break;
				}

				case 1:
				{
					buffer = i18n( "name" );
					break;
				}

				case 2:
				{
					buffer = i18n( "frequency" );
					break;
				}

				case 3:
				{
					buffer = i18n( "type" );
					break;
				}

				case 4:
				{
					buffer = i18n( "longitude" );
					break;
				}

				case 5:
				{
					buffer = i18n( "latitude" );
					break;
				}
			}

			titem = ui_widget.tableWidget_data->item( i, 0 );

			if ( !titem )
			{
				qDebug() << "No item";
				return;
			}

			titem->setText( buffer );

			ui_widget.pushbutton_add->setText( i18n( "Add" ) );
		}

		return;
	}

	nb++;

	item = new QTreeWidgetItem( ui_widget.treewidget_navaids );
	item->setText( 0, m_it->id );
	item->setText( 1, m_it->name );
	buffer.clear();

	if ( m_it->type.contains( "ndb", Qt::CaseInsensitive ) )
	{
		buffer.setNum( m_it->frequency, 'f', 0 );
		buffer.append( " kHz" );
	}
	else
	{
		buffer.setNum( m_it->frequency, 'f', 2 );
		buffer.append( " MHz" );
	}

	item->setText( 2, buffer );

	item->setText( 3, m_it->type );

	item->setText( 4, ui_widget.spinbox_altitude->text() );
	buffer.clear();
	buffer.setNum( m_it->longitude, 'f', 6 );
	item->setText( 5, buffer );
	buffer.clear();
	buffer.setNum( m_it->latitude, 'f', 6 );
	item->setText( 6, buffer );
	ui_widget.treewidget_navaids->insertTopLevelItem( nb, item );
	recalculateDistance();
}

void KFFWin_Flightplan::recalculateDistance()
{

	QTreeWidgetItem* item = 0;
	QString buffer;
	double distance = 0.0, distTot = 0.0;
	double longitude = 0.0, latitude = 0.0;
	int i, dist;
	QMap<int, int> waypoint;

	for ( i = 0 ; i < ui_widget.treewidget_navaids->topLevelItemCount() ; i++ )
	{
		item = 0;
		item = ui_widget.treewidget_navaids->topLevelItem( i );

		if ( item )
		{
			if ( i )
			{
				distance = calculateDistance( item->text( 5 ).toDouble(),
				                              item->text( 6 ).toDouble(),
				                              longitude,
				                              latitude
				                            );
				distTot += distance;
			}
			else
			{
				distTot += 0.0;
			}

			dist = ( int ) distTot;

			waypoint[dist] = item->text( 3 ).toInt();

			buffer.clear();

			buffer.setNum( distance );
			item->setText( 7, buffer );
			buffer.clear();
			buffer.setNum( distTot );
			item->setText( 8, buffer );
			longitude = item->text( 5 ).toDouble();
			latitude = item->text( 6 ).toDouble();
		}
	}
}

void KFFWin_Flightplan::loadSettings()
{
	QStringList list;

	list = Settings::flightplan_list();
	setCurrentList( list );

	recalculateDistance();
}

void KFFWin_Flightplan::saveSettings()
{
	QStringList list;

	getCurrentList( list );
	Settings::setFlightplan_list( list );

	Settings::self()->writeConfig();
}

void KFFWin_Flightplan::getCurrentList( QStringList & list )
{
	QTreeWidgetItem* item = 0;
	QString buffer;
	int i, j;

	for ( i = 0 ; i < ui_widget.treewidget_navaids->topLevelItemCount() ; i++ )
	{
		item = 0;
		buffer.clear();
		item = ui_widget.treewidget_navaids->topLevelItem( i );

		if ( item )
		{
			for ( j = 0 ; j < ui_widget.treewidget_navaids->columnCount() ; j++ )
			{
				buffer.append( item->text( j ) + "|" );
			}

			list << buffer;
		}
	}
}

void KFFWin_Flightplan::setCurrentList( QStringList & list )
{
	QTreeWidgetItem* item = 0;
	QStringList::Iterator it;
	int i = 0, j;

	ui_widget.treewidget_navaids->clear();

	for ( it = list.begin() ; it != list.end() ; ( it++, i++ ) )
	{
		item = new QTreeWidgetItem( ui_widget.treewidget_navaids );

		for ( j = 0 ; j < ui_widget.treewidget_navaids->columnCount() ; j++ )
		{
			item->setText( j, it->section( "|", j, j ) );
		}

		ui_widget.treewidget_navaids->insertTopLevelItem( i, item );
	}
}

void KFFWin_Flightplan::showFavoriteContextMenu( const QPoint &pos )
{
	KIconLoader loader;
	QPixmap pixmap;
	QIcon icon;
	QAction* remove;
	QAction* clear;
	QAction* edit;
	QAction* moveup;
	QAction* movedown;
	QAction* calc;
	KMenu menu( this );

	pixmap = loader.loadIcon( "edit-delete", KIconLoader::Small );
	icon.addPixmap( pixmap );
	remove = new QAction( icon, i18n( "&Remove waypoint" ), this );
	remove->setStatusTip( i18n( "Remove this waypoint" ) );
	connect( remove, SIGNAL( triggered() ), this, SLOT( removeNavaids() ) );

	pixmap = loader.loadIcon( "edit-clear-list", KIconLoader::Small );
	icon.addPixmap( pixmap );
	clear = new QAction( icon, i18n( "&Clear all waypoints" ), this );
	clear->setStatusTip( i18n( "Clear waypoint list" ) );
	connect( clear, SIGNAL( triggered() ), ui_widget.treewidget_navaids, SLOT( clear() ) );

	pixmap = loader.loadIcon( "edit-rename", KIconLoader::Small );
	icon.addPixmap( pixmap );
	edit = new QAction( icon, i18n( "&Edit waypoint altitude" ), this );
	edit->setStatusTip( i18n( "Edit this waypoint" ) );
	connect( edit, SIGNAL( triggered() ), this, SLOT( edit() ) );

	pixmap = loader.loadIcon( "arrow-up", KIconLoader::Small );
	icon.addPixmap( pixmap );
	moveup = new QAction( icon, i18n( "&Move waypoint up" ), this );
	moveup->setStatusTip( i18n( "Move this waypoint up" ) );
	connect( moveup, SIGNAL( triggered() ), this, SLOT( moveItemUp() ) );

	pixmap = loader.loadIcon( "arrow-down", KIconLoader::Small );
	icon.addPixmap( pixmap );
	movedown = new QAction( icon, i18n( "&Move waypoint down" ), this );
	movedown->setStatusTip( i18n( "Move this waypoint down" ) );
	connect( movedown, SIGNAL( triggered() ), this, SLOT( moveItemDown() ) );

	pixmap = loader.loadIcon( "view-refresh", KIconLoader::Small );
	icon.addPixmap( pixmap );
	calc = new QAction( icon, i18n( "&Recalculate Distance" ), this );
	calc->setStatusTip( i18n( "Force recalculate distance between all waypoints" ) );
	connect( calc, SIGNAL( triggered() ), this, SLOT( recalculate() ) );
	
	menu.addAction( remove );
	menu.addAction( edit );
	menu.addSeparator();
	menu.addAction( clear );
	menu.addSeparator();
	menu.addAction( moveup );
	menu.addAction( movedown );
	menu.addSeparator();
	menu.addAction( calc );
	menu.exec( mapToGlobal( pos + ui_widget.treewidget_navaids->pos() ) );
}

void KFFWin_Flightplan::itemActivated( QTreeWidgetItem * item, int column )
{
	//QTreeWidgetItem* item = ui_widget.treewidget_navaids->currentItem();

	m_data.id = item->text( 0 );
	m_data.name = item->text( 1 );
	m_data.type = item->text( 3 );
	m_data.altitude = item->text( 4 ).toLong();
	m_data.longitude = item->text( 5 ).toDouble();
	m_data.latitude = item->text( 6 ).toDouble();
	m_data.frequency = item->text( 2 ).section( " ", 0, 0 ).toDouble();
	m_editing = true;
	setNavaids( m_data );
}

void KFFWin_Flightplan::removeNavaids()
{
	QTreeWidgetItem* item;

	item = ui_widget.treewidget_navaids->currentItem();
	ui_widget.treewidget_navaids->takeTopLevelItem( ui_widget.treewidget_navaids->indexOfTopLevelItem( item ) );
}

void KFFWin_Flightplan::edit()
{
	QTreeWidgetItem* item = ui_widget.treewidget_navaids->currentItem();
	itemActivated( item, 0 );
}

void KFFWin_Flightplan::getFlightplanList( QStringList & list )
{
	KStandardDirs stddirs;
	QString dirname;
	QDir dir;

	dirname = stddirs.saveLocation( "data" );
	dir.cd( dirname );

	if ( !dir.exists( "kfreeflight" ) )
	{
		dir.mkdir( "kfreeflight" );
	}

	dir.cd( "kfreeflight" );

	if ( !dir.exists( "flightplans" ) )
	{
		dir.mkdir( "flightplans" );
	}

	dir.cd( "flightplans" );

	list = dir.entryList( QDir::Files, QDir::Name );

}

void KFFWin_Flightplan::createRestoreWidget( QString what )
{
	QPoint pos;
	QSize size, parentsize;
	QIcon icon;
	KIconLoader loader;
	QPixmap pixmap;
	int width = 500, height = 300;

	m_chooser = new KFFWin_Chooser( 0 );

	if ( what == "save" )
	{
		pixmap = loader.loadIcon( "document-save", KIconLoader::Small );
		icon.addPixmap( pixmap );
		m_chooser->setTitle( i18n( "Choose a name for this flight plan" ) );
		m_chooser->setButtonText( i18n( "Save" ) );
		m_chooser->setWindowTitle( i18n( "Save Flightplan" ) );
		m_chooser->setType( KFFWin_Chooser::KFFDLG_SAVE );
		connect( m_chooser,
		         SIGNAL( selected( const QString & ) ),
		         this,
		         SLOT( saveFlightplan( const QString & ) ) );
	}
	else
	{
		pixmap = loader.loadIcon( "document-open", KIconLoader::Small );
		icon.addPixmap( pixmap );
		m_chooser->setTitle( i18n( "Choose the flight plan to open" ) );
		m_chooser->setWindowTitle( i18n( "Open Flightplan" ) );
		m_chooser->setButtonText( i18n( "Open" ) );
		m_chooser->setType( KFFWin_Chooser::KFFDLG_OPEN );
		connect( m_chooser,
		         SIGNAL( selected( const QString & ) ),
		         this,
		         SLOT( openFlightplan( const QString & ) ) );
	}

	connect( m_chooser,

	         SIGNAL( haveDirtyList() ),
	         this,
	         SLOT( setList() ) );

	m_chooser->setButtonIcon( icon );
	setList();
	m_chooser->setAttribute( Qt::WA_DeleteOnClose );
	m_chooser->setFixedSize( width, height );

	pos = this->pos();
	parentsize = this->size();
	pos.rx() += (( parentsize.width() - width ) / 2 );
	pos.ry() += (( parentsize.height() - height ) / 2 );
	m_chooser->move( pos );
	m_chooser->show();
}

void KFFWin_Flightplan::setList()
{
	QStringList list;

	getFlightplanList( list );
	m_chooser->insertStringList( list );
}

void KFFWin_Flightplan::save()
{
	QTreeWidgetItem* item = 0;
	QString buffer;
	int nb;

	// propose flightplan name ( first_navaid-last_navaid)
	item = ui_widget.treewidget_navaids->topLevelItem( 0 );

	if ( item )
	{
		buffer = item->text( 0 );
		buffer.append( "-" );
	}

	nb = ui_widget.treewidget_navaids->topLevelItemCount();

	item = ui_widget.treewidget_navaids->topLevelItem( --nb );

	if ( item )
	{
		buffer.append( item->text( 0 ) );
	}

	createRestoreWidget( "save" );

	m_chooser->setDefaultText( buffer );
}

void KFFWin_Flightplan::open()
{
	createRestoreWidget( "open" );
}

void KFFWin_Flightplan::saveFlightplan( const QString &name )
{
	QStringList list;
	QStringList::iterator it;
	KStandardDirs stddirs;
	QFile file;
	QTextStream stream;

	qDebug() << "save : " << name;
	getCurrentList( list );
	file.setFileName( stddirs.saveLocation( "data" ) +
	                  "kfreeflight/flightplans/" + name );

	if ( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
	{
		qDebug() << "Cannot open file " << stddirs.saveLocation( "data" )
		<< "kfreeflight/flightplans/" << name;
		return;
	}

	stream.setDevice( &file );

	for ( it = list.begin() ; it != list.end() ; ++it )
	{
		stream << *it << "\n";
	}

	file.close();

	disconnect( m_chooser, SIGNAL( selected( const QString & ) ) );
	m_chooser->close();
}

void KFFWin_Flightplan::openFlightplan( const QString & name )
{
	QStringList list;
	KStandardDirs stddirs;
	QFile file;
	QTextStream stream;

	qDebug() << "open : " << name;
	file.setFileName( stddirs.saveLocation( "data" ) +
	                  "kfreeflight/flightplans/" + name );

	if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
	{
		qDebug() << "Cannot open file " << stddirs.saveLocation( "data" )
		<< "kfreeflight/flightplans/" << name;
		return;
	}

	stream.setDevice( &file );

	while ( !stream.atEnd() )
	{
		list << stream.readLine();
	}

	setCurrentList( list );

	file.close();

	disconnect( m_chooser, SIGNAL( selected( const QString & ) ) );
	m_chooser->close();
}

void KFFWin_Flightplan::moveItemUp()
{
	moveItem( 1 );
}

void KFFWin_Flightplan::moveItemDown()
{
	moveItem( -1 );
}

void KFFWin_Flightplan::moveItem( int direction )
{
	QTreeWidgetItem* item = 0;
	QList<QTreeWidgetItem*> itemList;
	int id;

	item = ui_widget.treewidget_navaids->currentItem();

	if ( !item )
	{
		return;
	}

	id = ui_widget.treewidget_navaids->indexOfTopLevelItem( item );

	ui_widget.treewidget_navaids->takeTopLevelItem( id );

	if ( direction > 0 )
	{
		--id;
		ui_widget.treewidget_navaids->insertTopLevelItem( id, item );
	}
	else
	{
		++id;

		if ( id < ui_widget.treewidget_navaids->topLevelItemCount() )
		{
			ui_widget.treewidget_navaids->insertTopLevelItem( id, item );
		}
		else
		{
			ui_widget.treewidget_navaids->addTopLevelItem( item );
		}
	}

	ui_widget.treewidget_navaids->setCurrentItem( item );

	recalculateDistance();
}

/******************************************************************************
 *                                                                            *
 ******************************************************************************/
NavThread::NavThread()
{
}

NavThread::~NavThread()
{
}

void NavThread::setText( QString text )
{
	m_rabbit = text;
}

void NavThread::run()
{
	QIODevice *file;
	QTextStream stream;
	QString line, buffer;
	int number = 0;
	QStringList list, tmp;
	NavaidsData data;
	double freq = 0.0;

	m_datalist.clear();

	buffer = Settings::fg_root() + "/Navaids/nav.dat.gz";

	file = KFilterDev::deviceForFile( buffer );

	if ( !file -> open( QIODevice::ReadOnly ) )
	{
		qDebug() << i18n( "Cannot open navaids file" ) << " " << buffer;
		emit( finished( m_datalist ) );
		return;
	}

	stream.setDevice( file );

	number = 0;

	while ( !stream.atEnd() )
	{
		line = stream.readLine();

		if ( line.contains( m_rabbit, Qt::CaseInsensitive ) )
		{
			line = line.simplified();
			data.id = line.section( " ", 7, 7 );
			buffer = line.section( " ", 8 );
			data.type = buffer.section( " ", -1, -1 );
			data.name = buffer.remove( " " + data.type );
			data.longitude = line.section( " ", 2, 2 ).toDouble();
			data.latitude = line.section( " ", 1, 1 ).toDouble();
			freq = line.section( " ", 4, 4 ).toDouble();

			if ( freq )
			{
				if ( !data.type.contains( "ndb", Qt::CaseInsensitive ) )
				{
					data.frequency = ( freq / 100.0 );
				}
				else
				{
					data.frequency = freq;
				}

				m_datalist.push_back( data );
			}

		}

		number++;

		if ( number > NB_LINE_BEFORE_UPDATE )
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

	emit( finished( m_datalist ) );
}

/******************************************************************************
 *                                                                            *
 ******************************************************************************/
NavaidsData::NavaidsData()
{
}

NavaidsData::~NavaidsData()
{
}

void NavaidsData::clear()
{
	id.clear();
	name.clear();
	type.clear();
	longitude = 0.0;
	latitude = 0.0;
	frequency = 0.0;
}
