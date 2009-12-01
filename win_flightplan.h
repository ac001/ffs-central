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

#ifndef WIN_FLIGHTPLAN_H
#define WIN_FLIGHTPLAN_H

#include "ui_win_flightplan_base.h"
#include "win_chooser.h"

#include <QWidget>
#include <QThread>
#include <QTableWidget>

#include <kprogressdialog.h>
#include <keditlistbox.h>

#define NB_LINE 25862
#define NB_LINE_BEFORE_UPDATE 20

/**
	@author
*/

class NavThread;

/******************************************************************************/

class NavaidsData
{

public:
	NavaidsData();
	~NavaidsData();

	void clear();

	QString id;
	QString name;
	QString type;
	long int altitude;
	double longitude;
	double latitude;
	double frequency;
};

typedef QList<NavaidsData> NavDataList;

/******************************************************************************/

class KFFWin_Flightplan : public QWidget
{
	Q_OBJECT

public:
	KFFWin_Flightplan( QWidget *parent = 0 );

	~KFFWin_Flightplan();

public slots:
	virtual void loadSettings();
	virtual void saveSettings();
	
private:
	Ui::win_flightplan ui_widget;
	KProgressDialog* m_progress;
	NavThread* m_thread;
	NavDataList m_datalist;
	QList<NavaidsData>::Iterator m_it;
	NavaidsData m_data;
	bool m_editing;
	KFFWin_Chooser * m_chooser;

	void getFlightplanList( QStringList & );
	void getCurrentList( QStringList & );
	void setCurrentList( QStringList & );
	
private slots:
	void setNavaids( NavaidsData& );
	void add();
	void edit();
	void previous();
	void next();
	void moveItemUp();
	void moveItemDown();
	void moveItem( int direction );
	void recalculateDistance();
	void search();
	void incrementProgress();
	void loadFinished( NavDataList );
	void showFavoriteContextMenu( const QPoint & );
	void removeNavaids();
	void itemActivated( QTreeWidgetItem*, int );
	void setList();
	void save();
	void open();
	void createRestoreWidget( QString );
	void saveFlightplan( const QString & );
	void openFlightplan( const QString & );

};

/******************************************************************************/

class NavThread : public QThread
{
	Q_OBJECT

public:
	/**
	 * Constructor
	 */
	NavThread();
	/**
		 * Destructor
	 */
	~NavThread();

public slots:
	virtual void setText( QString text );

protected:
	/**
	 * The code to execute when thread is active
	 */
	void run();

private:
	QString m_rabbit;
	NavDataList m_datalist;

signals:
	void finished( NavDataList );
	void progress();
};

Q_DECLARE_METATYPE( NavDataList );

#endif // WIN_FLIGHTPLAN_H
