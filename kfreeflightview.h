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
 *     (___)_)   File : kfreeflightview.h                   ||--|| *         *
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

#ifndef KFREEFLIGHTVIEW_H
#define KFREEFLIGHTVIEW_H

#include <QtGui/QWidget>
#include <QSplitter>

#include <KProcess>

#include "ui_kfreeflightview_base.h"
#include "opt_skeleton.h"
#include "win_messages.h"
#include "win_calculator.h"
#include "win_metarview.h"
#include "win_metarcreate.h"
#include "win_airports.h"
#include "win_flightplan.h"
#include "win_worldview.h"

class QPainter;

class KUrl;

/**
 * This is the main view class for kfreeflight.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 * @short Main view
 * @author Didier Fabert <didier.fabert@gmail.com>
 * @version 1.0
 */

class KFreeFlightView : public QSplitter, public Ui::KFreeFlightview_base
{
	Q_OBJECT

public:
	/**
	 * Default constructor
	 */
	KFreeFlightView( QWidget *parent );

	/**
	 * Destructor
	 */
	virtual ~KFreeFlightView();

	enum KFFflags
	{
		DEFAULT         = 0x00,
		DISABLE_AIRPORT = 0x01,
		DISABLE_CARIER  = 0x02,
		DISABLE_3D      = 0x04,
		DEBUG_ONLY      = 0x08,

	};

	void setFlag( int & fl );
	void setProfile( QString profile );

public slots:
	virtual void init();
	virtual void setFG_ROOT( QString path );
	virtual void showOutput();
	virtual void showCalc();
	virtual void save();
	virtual void load( bool loadAirport = true, bool firstTime = false );

private:
	Ui::KFreeFlightview_base ui_kffbase;
	KFFWin_messages* m_output;
	KFFWin_Calculator* m_calc;
	KFFWin_metarView* m_metarView;
	KFFWin_metarCreate* m_metarCreate;
	KFFWin_Airports* m_searchAirport;
	KFFWin_Flightplan* m_flightplan;
	KFFWin_WorldView* m_worldview;
	QMap<QString, KFFOpt_skeleton*> m_sonWidgets;
	QString m_oldFG_ROOT;
	KProcess* m_fgfs;
	KProcess* m_atlas;
	QString m_fgfsout;
	QString m_fgfserr;
	QString m_atlasout;
	QString m_atlaserr;
	bool m_atlasWithFg;
	int m_flag;
	QString m_profile;

signals:
	/**
	 * Use this signal to change the content of the statusbar
	 */
	void signalChangeStatusbar( const QString& text );

	/**
	 * Use this signal to change the content of the caption
	 */
	void signalChangeCaption( const QString& text );

	void finished();
	void needAirport();

private slots:
	void settingsChanged();
	void closeTerrasync();
	void launchFlightGear( int );
	void queryAtlas();
	void launchAtlas( QString );
	void fgfsReadData();
	void fgfsReadError();
	void fgfsCloseProcess( int, QProcess::ExitStatus );
	void atlasReadData();
	void atlasReadError();
	void atlasCloseProcess( int, QProcess::ExitStatus );
};

#endif // KFREEFLIGHTVIEW_H
