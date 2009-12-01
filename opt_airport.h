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
 *     (___)_)   File : opt_airport.h                       ||--|| *         *
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

#ifndef OPT_AIRPORT_H
#define OPT_AIRPORT_H

#include "ui_option_airport_base.h"
#include "opt_skeleton.h"
#include "win_airports.h"
#include "win_metarview.h"

#include <QWidget>
#include <QThread>
#include <QTreeWidget>

#include <kprogressdialog.h>

class ReadingThread;
class AirportItem;

/**
 * @author Didier Fabert <didier.fabert@gmail.com>
 */

class KFFOpt_airport : public KFFOpt_skeleton
{
	Q_OBJECT

public:
	KFFOpt_airport( QWidget *parent = 0 );

	~KFFOpt_airport();

public slots:
	virtual void saveSettings();
	virtual void loadSettings();
	virtual bool getOptions(QStringList &);
	virtual void getAirport();
	virtual void setMetarView(KFFWin_metarView*);
	virtual void setSearchAirport(KFFWin_Airports*);

private slots:
	void loadAirport();
	void insertItem( AirportItem item );
	void loadFinished();
	void whereIsIt();
	void webInfo();
	void selectAirport();
	void setAirport( QTreeWidgetItem * , int );
	void showContextMenu( const QPoint& );
	void showFavoriteContextMenu( const QPoint& );
	void addToFavorite();
	void addToFavorite(QStringList);
	void removeFavorite();
	void showFavorite( QTreeWidgetItem* selected );
	void getWeather();
	void search();
	QString getParentCurrentText(int);
	void getAirportList( QString id);
	void find ( const QString & );

private:
	Ui::opt_airport ui_widget;
	KFFWin_Airports* m_searchAirport;
	KFFWin_metarView* m_metarView;
	ReadingThread* m_thread;
	KProgressDialog* m_progress;
	QPixmap m_towerIcon;
	QPixmap m_runwayIcon;
	QString m_airport;
	QString m_runway;
	
private:
	void loadAirport( bool showDialog );

signals:
	void searchAirport(AirportDescription);
	void foundAirports( AirportDescList );
	void finished();
	void selected( QString );
	void showPlace( qreal, qreal, bool );
};

/******************************************************************************/

class ReadingThread : public QThread
{
	Q_OBJECT

public:
	/**
	 * Constructor
	 */
	ReadingThread();
	/**
	 * Destructor
	 */
	~ReadingThread();

protected:
	/**
	 * The code to execute when thread is active
	 */
	void run();

signals:
	void insertItem( AirportItem );
	void finished();
};

class AirportItem
{

public:
	AirportItem();
	~AirportItem();

	void clear();

	QStringList parent;
	QList<QStringList> childs;
	QString coordinates;
};

Q_DECLARE_METATYPE( AirportItem );

#endif // OPT_AIRPORT_H
