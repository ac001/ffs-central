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
 *     (___)_)   File : win_airports.h                      ||--|| *         *
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

#ifndef WIN_AIRPORTS_H
#define WIN_AIRPORTS_H

#include "ui_win_airport_base.h"
#include "win_coordinates.h"

#include <QWidget>
#include <QThread>

#include <kprogressdialog.h>

#define NB_AIRPORT 25268

class SearchThread;

class AirportData;

class AirportDescription;

typedef QList<AirportDescription> AirportDescList;


/******************************************************************************/

class AirportDescription
{

public:
	AirportDescription();
	~AirportDescription();

	QString id;
	QString name;
	QString elevation;
	QString latitude;
	QString longitude;
	QList<QStringList> runway;

	void clear();
};

/******************************************************************************/

class AirportData
{

public:
	AirportData();
	~AirportData();

	void clear();

	bool found;
	QString id;
	QList<QStringList> comOthers;
	QList<QStringList> comTower;
	QList<QStringList> comATIS;
	QList<QStringList> navaids;
	QMap<QString, QString> runwayILS;
};

/******************************************************************************/
/**
 * @author Didier Fabert <didier.fabert@gmail.com>
 */

class KFFWin_Airports : public QWidget
{
	Q_OBJECT

public:
	KFFWin_Airports( QWidget *parent = 0 );

	~KFFWin_Airports();

public slots:
	virtual void searchAirport( AirportDescription desc = AirportDescription() );
	virtual void setList( AirportDescList list );
	virtual void setPixmap( QPixmap& tower, QPixmap& runway );

private:
	Ui::win_airport ui_widget;
	KProgressDialog* m_progress;
	KFFWin_Coordinates* m_coordinates;
	SearchThread* m_thread;
	QPixmap m_towerPixmap;
	QPixmap m_runwayPixmap;

private slots:
	void search( QString id, QString longitude, QString latitude );
	void loadFinished( AirportData );
	void searchMyAirport();
	void incrementProgress();
	void changeProgress( QString );
	void setAirport(QTreeWidgetItem*);
	void favoriteRequest();
	void setCoordinates( QString );
	void setNav1();
	void setNav1stby();
	void setNav1radial();
	void setNav2();
	void setNav2stby();
	void setNav2radial();
	void setDme();
	void setAdf();
	void setAdfstdby();
	void setAdfrot();
	void setCom1();
	void setCom1stdby();
	void setCom2();
	void setCom2stdby();
	void showContextMenu( const QPoint &pos );

signals:
	void needList( QString );
	void addFavorite (QStringList favorite);
	void frequencySelected(int, QString);
};

/******************************************************************************/

class SearchThread : public QThread
{
	Q_OBJECT

public:
	/**
	 * Constructor
	 */
	SearchThread();
	/**
	 * Destructor
	 */
	~SearchThread();

public slots:
	virtual void setAirport( QString id, double longitude, double latitude );

protected:
	/**
	 * The code to execute when thread is active
	 */
	void run();

private:
	QString m_id;
	double m_longitude;
	double m_latitude;
	QStringList m_runways;

signals:
	void finished( AirportData );
	void progress();
	void fileChanged( QString );
};

Q_DECLARE_METATYPE( AirportData );
Q_DECLARE_METATYPE( AirportDescription );
Q_DECLARE_METATYPE( AirportDescList );

#endif // WIN_AIRPORTS_H
