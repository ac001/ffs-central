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
 *     (___)_)   File : kfreeflightview.cpp                 ||--|| *         *
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

#include "kfreeflightview.h"
#include "opt_airport.h"
#include "opt_property.h"
#include "opt_common.h"
#include "opt_rendering.h"
#include "opt_weather.h"
#include "opt_othersopt.h"
#include "opt_carrier.h"
#include "opt_aircraft.h"
#include "opt_scenery.h"
#include "opt_position.h"
#include "opt_datetime.h"
#include "opt_flightplan.h"
#include "opt_network.h"
#include "opt_radio.h"
#include "settings.h"

#include <klocale.h>
#include <kiconloader.h>
#include <kmessagebox.h>
#include <KDE/KLocale>

#include <QtCore/QStringList>
#include <QtGui/QWidget>
#include <QtGui/QStackedWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QTreeWidgetItem>

KFreeFlightView::KFreeFlightView( QWidget * parent )
	: QSplitter( parent )
{
}

void KFreeFlightView::init()
{
	int id = 0;
	KIconLoader loader;
	QPixmap pixmap;

	m_atlasWithFg = false;

	//***************************************************************************
	//*** Setup UI
	//***************************************************************************
	//** FFS - Create our own Stacked Widget in c++ - do away with UI
	//ui_kffbase.setupUi( this );
	//wSplitter = new QSplitter(this);
	setContentsMargins(0, 0, 0, 0);
	//setSpacing(0);
	
	//** Add stacket widget to left
	wStackedWidget = new QStackedWidget(this);
	wStackedWidget->setContentsMargins(0, 0, 0, 0);
	addWidget(wStackedWidget);
	
	//* Right Widget had vertical layout
	QWidget* rWidget = new QWidget(this);
	QVBoxLayout* vBox = new QVBoxLayout();
	vBox->setContentsMargins(0, 0, 0, 0);
	vBox->setSpacing(0);
	rWidget->setLayout(vBox);
	
	//* Page Selector widget is a tree
	pageSelector = new QTreeWidget(this);
	pageSelector->setRootIsDecorated(false);
	pageSelector->header()->hide();
	pageSelector->setUniformRowHeights(true);
	pageSelector->setAlternatingRowColors(true);
	pageSelector->setStyleSheet("font-size: 14pt;");
	pageSelector->header()->setStretchLastSection(true);
	vBox->addWidget(pageSelector, 50);
	
	wLaunchButton = new QPushButton(this);
	vBox->addWidget(wLaunchButton, 1);
	//***************************************************************************
	
	m_oldFG_ROOT = Settings::fg_root();

	m_output = new KFFWin_messages( 0 );
	m_calc = new KFFWin_Calculator( 0 );
	m_metarView = new KFFWin_metarView( 0 );
	m_metarCreate = new KFFWin_metarCreate( 0 );
	m_searchAirport = new KFFWin_Airports( 0 );
	m_flightplan = new KFFWin_Flightplan( 0 );
	m_worldview = new KFFWin_WorldView( 0 );
	m_fgfs = 0;
	m_atlas = 0;

	setAutoFillBackground( true );
	//pixmap = loader.loadIcon( "system-run", KIconLoader::Desktop );

	KFFOpt_common* common = new KFFOpt_common( 0 );
	wStackedWidget->insertWidget( id,  common );
	pageSelector->addTopLevelItem(  new QTreeWidgetItem(  QStringList(i18n( "Common" )) ) );
	m_sonWidgets.insert( "common", common );

	KFFOpt_rendering* rendering = new KFFOpt_rendering( 0 );
	wStackedWidget->insertWidget( id, rendering );
	pageSelector->addTopLevelItem(  new QTreeWidgetItem(  QStringList(i18n( "Rendering" )) ) );
	m_sonWidgets.insert( "rendering", rendering );

	KFFOpt_airport* airport = new KFFOpt_airport( 0 );
	wStackedWidget->insertWidget( id, airport );
	pageSelector->addTopLevelItem(  new QTreeWidgetItem(  QStringList(i18n( "Airport" )) ) );
	m_sonWidgets.insert( "airport", airport );

	KFFOpt_carrier* carrier = new KFFOpt_carrier( 0 );
	wStackedWidget->insertWidget( id, carrier );
	pageSelector->addTopLevelItem(  new QTreeWidgetItem(  QStringList(i18n( "Carrier" )) ) );
	m_sonWidgets.insert( "carrier", carrier );

	KFFOpt_aircraft* aircraft = new KFFOpt_aircraft( 0 );
	wStackedWidget->insertWidget( id, aircraft );
	pageSelector->addTopLevelItem(  new QTreeWidgetItem(  QStringList(i18n( "Aircraft" )) ) );
	m_sonWidgets.insert( "aircraft", aircraft );

	KFFOpt_position* position = new KFFOpt_position( 0 );
	wStackedWidget->insertWidget( id, position );
	pageSelector->addTopLevelItem(  new QTreeWidgetItem(  QStringList(i18n( "Position" )) ) );
	m_sonWidgets.insert( "position", position );

	KFFOpt_datetime* datetime = new KFFOpt_datetime( 0 );
	wStackedWidget->insertWidget( id, datetime );
	pageSelector->addTopLevelItem(  new QTreeWidgetItem(  QStringList(i18n( "Date Time" )) ) );
	m_sonWidgets.insert( "datetime", datetime );

	KFFOpt_weather* weather = new KFFOpt_weather( 0 );
	wStackedWidget->insertWidget( id, weather );
	pageSelector->addTopLevelItem(  new QTreeWidgetItem(  QStringList(i18n( "Weather" )) ) );
	m_sonWidgets.insert( "weather", weather );

	KFFOpt_flightplan* flightplan = new KFFOpt_flightplan( 0 );
	wStackedWidget->insertWidget( id, flightplan );
	pageSelector->addTopLevelItem(  new QTreeWidgetItem(  QStringList(i18n( "Flight Plan" )) ) );
	m_sonWidgets.insert( "flightplan", flightplan );

	KFFOpt_network* network = new KFFOpt_network( 0 );
	wStackedWidget->insertWidget( id, network );
	pageSelector->addTopLevelItem(  new QTreeWidgetItem(  QStringList(i18n( "Network" )) ) );
	m_sonWidgets.insert( "network", network );

	KFFOpt_radio* radio = new KFFOpt_radio( 0 );
	wStackedWidget->insertWidget( id, radio );
	pageSelector->addTopLevelItem(  new QTreeWidgetItem(  QStringList(i18n( "NAV and COM")) ) );
	m_sonWidgets.insert( "radio", radio );

	KFFOpt_scenery* scenery = new KFFOpt_scenery( 0 );
	wStackedWidget->insertWidget( id, scenery );
	pageSelector->addTopLevelItem(  new QTreeWidgetItem(  QStringList(i18n( "Scenarii")) ) );
	m_sonWidgets.insert( "scenery", scenery );

	KFFOpt_property* property = new KFFOpt_property( 0 );
	wStackedWidget->insertWidget( id, property );
	pageSelector->addTopLevelItem(  new QTreeWidgetItem(  QStringList(i18n( "Property" )) ) );
	m_sonWidgets.insert( "property", property );

	KFFOpt_othersopt* othersopt = new KFFOpt_othersopt( 0 );
	wStackedWidget->insertWidget( id, othersopt );
	pageSelector->addTopLevelItem(  new QTreeWidgetItem(  QStringList(i18n( "Personnal" )) ) );
	m_sonWidgets.insert( "othersopt", othersopt );

	wStackedWidget->setCurrentIndex( 0 );

	airport->setSearchAirport( m_searchAirport );
	airport->setMetarView( m_metarView );
	weather->setMetarView( m_metarView );
	weather->setMetarCreate( m_metarCreate );

	connect( m_searchAirport,
	         SIGNAL( frequencySelected( int, QString ) ),
	         radio,
	         SLOT( setRadioFrequency( int, QString ) )
	       );
	connect( common,
	         SIGNAL( queryCloseTerrasync() ),
	         SLOT( closeTerrasync() )
	       );
	connect( common,
	         SIGNAL( queryLaunchAtlas() ),
	         SIGNAL( needAirport() )
	       );

	connect( airport,
	         SIGNAL( finished() ),
	         SIGNAL( finished() )
	       );

	//m_worldview->centerOn( -122.0, 43.0, true );
	connect( airport,
	         SIGNAL( showPlace( qreal, qreal, bool ) ),
	         m_worldview,
	         SLOT( center( qreal, qreal, bool ) )
	       );

	connect( pageSelector,
	         SIGNAL( itemClicked( QTreeWidgetItem*,  int ) ),
	         SLOT( wSetStack( QTreeWidgetItem*,  int ) )
	       );

	connect( wLaunchButton,
	         SIGNAL( clicked() ),
	         position,
	         SLOT( getStartPlace() )
	       );

	connect( position,
	         SIGNAL( startPlace( int ) ),
	         SLOT( launchFlightGear( int ) )
	       );

	connect( flightplan,
	         SIGNAL( queryAtlas() ),
	         airport,
	         SLOT( getAirport() )
	       );

	connect( this,
	         SIGNAL( needAirport() ),
	         airport,
	         SLOT( getAirport() )
	       );

	connect( airport,
	         SIGNAL( selected( QString ) ),
	         SLOT( launchAtlas( QString ) )
	       );

	connect( flightplan,
	         SIGNAL( queryFlightPlanWin() ),
	         m_flightplan,
	         SLOT( show() )
		   );
}

KFreeFlightView::~KFreeFlightView()
{
	save();
}

void KFreeFlightView::wSetStack(QTreeWidgetItem* item,  int)
{
	wStackedWidget->setCurrentIndex( pageSelector->invisibleRootItem()->childCount() - pageSelector->indexOfTopLevelItem( item )  - 1);
}

void KFreeFlightView::load( bool loadAirport, bool firstTime )
{
	QMapIterator<QString, KFFOpt_skeleton*> it( m_sonWidgets );

	while ( it.hasNext() )
	{
		it.next();

		if ( firstTime )
		{
			it.value()->setOutput( m_output );
		}

		if (( it.key() == "airport" ) && ((( m_flag & DISABLE_AIRPORT ) == DISABLE_AIRPORT ) || !loadAirport))
		{
			continue;
		}

		if (( it.key() == "carrier" ) && (( m_flag & DISABLE_CARIER ) == DISABLE_CARIER ) )
		{
			continue;
		}

		it.value()->loadSettings();
	}

	m_flightplan->loadSettings();

	m_worldview->loadSettings();
}

void KFreeFlightView::save()
{
	QMapIterator<QString, KFFOpt_skeleton*> it( m_sonWidgets );

	while ( it.hasNext() )
	{
		it.next();
		it.value()->saveSettings();
	}

	m_flightplan->saveSettings();

	Settings::self()->writeConfig();
}

void KFreeFlightView::setFG_ROOT( QString path )
{
	m_oldFG_ROOT = path;
}

void KFreeFlightView::settingsChanged()
{
	bool fgrootChanged = false;

	if ( Settings::fg_root() != m_oldFG_ROOT )
	{
		// reload page depending of FG_ROOT
		KMessageBox::information( this, i18n( "You have change the FG_ROOT, the reload can take some time" ) );
		fgrootChanged = true;
	}

	load( fgrootChanged, false );

	emit signalChangeStatusbar( i18n( "Settings changed" ) );
}

void KFreeFlightView::showOutput()
{
	m_output->show();
}

void KFreeFlightView::showCalc()
{
	m_calc->show();
}

void KFreeFlightView::closeTerrasync()
{
	KMessageBox::information( this, "Close Terrasync" );
}

void KFreeFlightView::launchFlightGear( int startingPlace )
{
	QMapIterator<QString, KFFOpt_skeleton*> it( m_sonWidgets );
	QStringList list;
	QStringList::Iterator its;
	QString output;
	QString buffer;
	bool ignoreCarrier = false;
	bool ignoreAirport = false;
	bool noError = true;



	m_atlasWithFg = true;

	if ( !m_fgfs )
	{
		m_fgfs = new KProcess;
		m_fgfs->setOutputChannelMode( KProcess::SeparateChannels );
		connect( m_fgfs, SIGNAL( readyReadStandardOutput() ), SLOT( fgfsReadData() ) );
		connect( m_fgfs, SIGNAL( readyReadStandardError() ), SLOT( fgfsReadError() ) );
		connect( m_fgfs,
		         SIGNAL( finished( int, QProcess::ExitStatus ) ),
		         SLOT( fgfsCloseProcess( int, QProcess::ExitStatus ) )
		       );
	}

	switch ( startingPlace )
	{

		case KFFOpt_skeleton::START_ON_AIRPORT:
		{
			ignoreCarrier = true;
			ignoreAirport = false;
			break;
		}

		case KFFOpt_skeleton::START_ON_CARRIER:
		{
			ignoreCarrier = false;
			ignoreAirport = true;
			break;
		}

		case KFFOpt_skeleton::START_ON_TOP:
		{
			ignoreCarrier = true;
			ignoreAirport = false;
			break;
		}

		case KFFOpt_skeleton::START_ANYWHERE:
		{
			ignoreCarrier = true;
			ignoreAirport = true;
			break;
		}
	}

	m_fgfs->clearProgram();

	m_fgfs->setProgram( *Settings::fg_exe().begin() );

	*m_fgfs << "--fg-root=" + Settings::fg_root();
	*m_fgfs << "--fg-scenery=" + Settings::fg_addon_sceneries().join( ":" );

	while ( it.hasNext() )
	{
		it.next();

		if ( it.key() == "carrier" && ignoreCarrier ) continue;

		if ( it.key() == "airport" && ignoreAirport ) continue;

		noError = it.value()->getOptions( list );

		if ( !noError )
		{
			return;
		}

	}

	for ( its = list.begin() ; its != list.end() ; its++ )
	{
		output.append( *its + "<br>" );
		*m_fgfs << *its;
	}

	if (( m_flag & DEBUG_ONLY ) != DEBUG_ONLY )
	{
		m_fgfs->start();
	}

	m_output->insertTitle( i18n( "Launch FlighGear" ) );

	m_output->insertText( output );

}

void KFreeFlightView::fgfsReadData()
{
	m_fgfsout.append( m_fgfs->readAllStandardOutput() );
}

void KFreeFlightView::fgfsReadError()
{
	m_fgfserr.append( m_fgfs->readAllStandardOutput() );
}

void KFreeFlightView::fgfsCloseProcess( int code, QProcess::ExitStatus status )
{
	QString buffer;

	m_atlasWithFg = false;
	buffer.setNum( code );
	m_output->insertText( "FlightGear process finished with code " + buffer );

	if ( status != QProcess::NormalExit )
	{
		m_output->insertError( "process crashed" );
	}

	m_fgfserr = m_fgfserr.simplified();

	m_fgfsout = m_fgfsout.simplified();

	if ( !m_fgfserr.isEmpty() )
	{
		m_output->insertError( m_fgfserr );
		m_fgfserr.clear();
	}

	if ( !m_fgfsout.isEmpty() )
	{
		m_output->insertError( m_fgfsout );
		m_fgfsout.clear();
	}
}

void KFreeFlightView::queryAtlas()
{
	emit( needAirport() );
}

void KFreeFlightView::launchAtlas( QString airport )
{
	QString buffer;
	QStringList args;

	if ( !m_atlas )
	{
		m_atlas = new KProcess;
		m_atlas->setOutputChannelMode( KProcess::SeparateChannels );
		connect( m_atlas, SIGNAL( readyReadStandardOutput() ), SLOT( atlasReadData() ) );
		connect( m_atlas, SIGNAL( readyReadStandardError() ), SLOT( atlasReadError() ) );
		connect( m_atlas,
		         SIGNAL( finished( int, QProcess::ExitStatus ) ),
		         SLOT( atlasCloseProcess( int, QProcess::ExitStatus ) )
		       );
	}

	m_atlas->clearProgram();

	buffer = Settings::atlas_exe();

	if ( buffer.isEmpty() )
	{
		KMessageBox::sorry( this, i18n( "No Atlas executable found" ) );
		return;
	}

	m_atlas->setProgram( buffer );

	*m_atlas << "--fg-root=" + Settings::fg_root();
	*m_atlas << "--airport=" + airport;
	
	if ( Settings::atlas_version() )
	{
		*m_atlas << "--atlas=" + Settings::img_dir();
	}
	else
	{
		*m_atlas << "--path=" + Settings::img_dir();
	}

	if ( Settings::glut_font() )
	{
		*m_atlas << "--glutfonts";
	}

	if ( m_atlasWithFg )
	{
		buffer.setNum( Settings::http_port() );

		*m_atlas << "--udp=" + buffer;
	}

	m_atlas->start();

	m_output->insertTitle( i18n( "Launch Atlas" ) );
	m_output->insertText( m_atlas->program().join( " " ) );
}

void KFreeFlightView::atlasReadData()
{
	m_atlasout.append( m_atlas->readAllStandardOutput() );
}

void KFreeFlightView::atlasReadError()
{
	m_atlaserr.append( m_atlas->readAllStandardOutput() );
}

void KFreeFlightView::atlasCloseProcess( int code, QProcess::ExitStatus status )
{
	QString buffer;

	buffer.setNum( code );
	m_output->insertText( "Atlas process finished with code " + buffer );
	m_atlaserr = m_fgfserr.simplified();
	m_atlasout = m_fgfsout.simplified();

	if ( status != QProcess::NormalExit )
	{
		m_output->insertError( "process crashed" );
	}

	if ( !m_atlaserr.isEmpty() )
	{
		m_output->insertError( m_atlaserr );
		m_atlaserr.clear();
	}

	if ( !m_atlasout.isEmpty() )
	{
		m_output->insertError( m_atlasout );
		m_atlasout.clear();
	}
}

void KFreeFlightView::setFlag( int & fl )
{
	m_flag = fl ;
	qDebug() << "flag = " << m_flag;
}

void KFreeFlightView::setProfile( QString profile )
{
	m_profile = profile;
	qDebug() << "profile = " << m_profile;
}

#include "kfreeflightview.moc"
