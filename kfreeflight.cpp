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
 *     (___)_)   File : kfreeflight.cpp                     ||--|| *         *
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


#include "kfreeflight.h"
#include "kfreeflightview.h"
#include "settings.h"

#include <QtGui/QDropEvent>
#include <QtGui/QPainter>

#include <kconfigdialog.h>
#include <kstatusbar.h>

#include <kaction.h>
#include <kactioncollection.h>
#include <kstandardaction.h>
#include <kstandarddirs.h>

#include <KDE/KLocale>

KFreeFlight::KFreeFlight()
		: KXmlGuiWindow(),
		m_view( new KFreeFlightView( this ) ),
		m_printer( 0 )
{
	KStandardDirs stdDir;
	QPixmap pixmap;
	QString buffer;

	buffer = stdDir.findResource( "data", "kfreeflight/splash.jpeg" );

	pixmap.load( buffer, "JPEG" );
	m_splash = new KSplashScreen( pixmap, Qt::WindowStaysOnTopHint );
	m_splash->show();

	buffer = buffer.remove( buffer.section("/", -1, -1) );
	Settings::setData_dir( buffer );
	Settings::self()->writeConfig();

	m_view->init();
	
	// accept dnd
	setAcceptDrops( true );

	// tell the KXmlGuiWindow that this is indeed the main widget
	setCentralWidget( m_view );

	// then, setup our actions
	setupActions();

	// add a status bar
	statusBar()->show();

	// a call to KXmlGuiWindow::setupGUI() populates the GUI
	// with actions, using KXMLGUI.
	// It also applies the saved mainwindow settings, if any, and ask the
	// mainwindow to automatically save settings if changed: window size,
	// toolbar position, icon size, etc.
	setupGUI();

	// allow the main window to change the statusbar and caption
	connect ( m_view,
	          SIGNAL ( signalChangeStatusbar ( const QString& ) ),
	          SLOT ( changeStatusbar ( const QString& ) ) );
	connect ( m_view,
	          SIGNAL ( signalChangeCaption ( const QString& ) ),
	          SLOT ( changeCaption ( const QString& ) ) );
	connect ( m_view,
	          SIGNAL ( finished () ),
	          SLOT ( showApp() )
	        );
}

KFreeFlight::~KFreeFlight()
{
}

void KFreeFlight::showApp()
{
	show();
	m_splash->finish( this );

}

void KFreeFlight::setupActions()
{
	KStandardAction::openNew( this, SLOT( fileNew() ), actionCollection() );
	KStandardAction::quit( qApp, SLOT( quit() ), actionCollection() );
	KStandardAction::save( m_view, SLOT( save() ), actionCollection() );
	KStandardAction::revert( m_view, SLOT( load() ), actionCollection() );

	KStandardAction::preferences( this, SLOT( optionsPreferences() ), actionCollection() );

	// custom menu and menu item - the slot is in the class KFreeFlightView
	KAction *output = new KAction( KIcon( "utilities-terminal" ), i18n( "Output" ), this );
	actionCollection()->addAction( QLatin1String( "output" ), output );
	connect( output, SIGNAL( triggered( bool ) ), m_view, SLOT( showOutput() ) );

	KAction *calc = new KAction( KIcon( "accessories-calculator" ), i18n( "Calculator" ), this );
	actionCollection()->addAction( QLatin1String( "calc" ), calc );
	connect( calc, SIGNAL( triggered( bool ) ), m_view, SLOT( showCalc() ) );
}

void KFreeFlight::changeStatusbar ( const QString& text )
{
	// display the text on the statusbar
	statusBar()->showMessage ( text, 2000 );
}

void KFreeFlight::changeCaption ( const QString& text )
{
	// display the text on the caption
	setCaption ( text );
}

void KFreeFlight::fileNew()
{
	// this slot is called whenever the File->New menu is selected,
	// the New shortcut is pressed (usually CTRL+N) or the New toolbar
	// button is clicked

	// create a new window
	( new KFreeFlight )->show();
}

void KFreeFlight::optionsPreferences()
{
	// The preference dialog is derived from prefs_base.ui
	//
	// compare the names of the widgets in the .ui file
	// to the names of the variables in the .kcfg file
	//avoid to have 2 dialogs shown
	if ( KConfigDialog::showDialog( "settings" ) )
	{
		return;
	}

	m_view->setFG_ROOT( Settings::fg_root() );

	KConfigDialog *dialog = new KConfigDialog( this, "settings", Settings::self() );

	dialog->setAttribute( Qt::WA_DeleteOnClose );

	// Page 1
	KFFPref_page1 *page1 = new KFFPref_page1( this );
	dialog->addPage( page1, i18n( "KFreeFlight Options" ), "configure" );

	// Page 2
	KFFPref_page2 *page2 = new KFFPref_page2( this );
	dialog->addPage( page2, i18n( "FlightGear Paths" ), "system-run" );

	// Page 3
	KFFPref_page3 *page3 = new KFFPref_page3( this );
	dialog->addPage( page3, i18n( "FlightGear Options" ), "system-run" );

	// Page 4
	KFFPref_page4 *page4 = new KFFPref_page4( this );
	dialog->addPage( page4, i18n( "Atlas Options" ), "system-run" );

	// Page 5
	KFFPref_page5 *page5 = new KFFPref_page5( this );
	dialog->addPage( page5, i18n( "Advanced" ), "tools-wizard" );

	connect( dialog,
	         SIGNAL( settingsChanged( QString ) ),
	         m_view,
	         SLOT( settingsChanged() ) );

	dialog->show();
}

void KFreeFlight::setFlag( int & fl )
{
	m_view->setFlag( fl );
}

void KFreeFlight::setProfile( QString profile )
{
	m_view->setProfile( profile );
}

void KFreeFlight::loadSettings()
{
	m_view->load( true, true );
}

#include "kfreeflight.moc"
