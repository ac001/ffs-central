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
 *     (___)_)   File : kfreeflight.h                       ||--|| *         *
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
 
#ifndef KFREEFLIGHT_H
#define KFREEFLIGHT_H


#include <kxmlguiwindow.h>
#include <ksplashscreen.h>

#include "pref_page1.h"
#include "pref_page2.h"
#include "pref_page3.h"
#include "pref_page4.h"
#include "pref_page5.h"

#include <QtGui/QTabWidget>
#include <QtWebKit/QWebView>

class KFreeFlightView;
class KPrinter;
class KToggleAction;
class KUrl;

/**
 * This class serves as the main window for KFreeFlight.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author Andreas Pakulat <apaku@gmx.de>
 * @version 0.1
 */
class KFreeFlight : public KXmlGuiWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    KFreeFlight();

    /**
     * Default Destructor
     */
    virtual ~KFreeFlight();

	void setFlag( int & fl );
	void setProfile( QString profile );
	void loadSettings();

private slots:
    void fileNew();
	void optionsPreferences();
	void changeStatusbar ( const QString& text );
	void changeCaption ( const QString& text );
	void showApp();

private:
    void setupActions();

private:
	
	KFFPref_page1* prefPage1;
	KFFPref_page2* prefPage2;
	KFFPref_page3* prefPage3;
	KFFPref_page4* prefPage4;
	KFFPref_page5* prefPage5;
    KFreeFlightView* m_view;

    KPrinter*   m_printer;
    KToggleAction* m_toolbarAction;
	KToggleAction* m_statusbarAction;
	KSplashScreen* m_splash;
	
	QTabWidget* centralTabsWidget;
	QWebView* webBrowser;
};

#endif // _KFREEFLIGHT_H_
