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
 *     (___)_)   File : win_metarview.h                     ||--|| *         *
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

#ifndef WIN_METARVIEW_H
#define WIN_METARVIEW_H

#include "ui_win_metarview_base.h"
#include "metar.h"

#include <kprogressdialog.h>

#include <QWidget>
#include <QFtp>
#include <QThread>
#include <QFile>

class DownloadThread;

class KFF_Metar;

class DownloadThread : public QThread
{
	Q_OBJECT

public:
	/**
	 * Constructor
	 */
	DownloadThread();
	/**
	 * Destructor
	 */
	~DownloadThread();

public slots:
	virtual void abort();
	virtual void setAirportID ( QString id );

protected:
	/**
	 * The code to execute when thread is active
	 */
	void run();

private:
	QString m_id;
	QString m_state;
	QFtp m_ftp;
	bool totalSetted;
	QFile m_file;

private slots:
	void setProgress ( qint64, qint64 );
	void cmdFinished ( int, bool );
	void cmdStarted ( int );

signals:
	void state ( QString& );
	void progress ( qint64 );
	void totalProgress ( qint64 );
	void finished ( int );
};

/******************************************************************************/
/**
 * @author
 */

class KFFWin_metarView : public QWidget
{
	Q_OBJECT

public:
	KFFWin_metarView ( QWidget *parent = 0 );

	~KFFWin_metarView();

public slots:
	void setAirport ( QString );
	void download();

private:
	Ui::win_metarview ui_widget;
	DownloadThread m_thread;
	KProgressDialog* m_progress;
	KFFMetar m_metar;

private slots:
	void setFavorite ( const QString & );
	void setProgress ( qint64 );
	void setTotalProgress ( qint64 );
	void setProgressText ( QString& );
	void display ( int );
};



#endif // WIN_METARVIEW_H
