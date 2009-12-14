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
#include <QFile>

class KFF_Metar;

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
	QFtp m_ftp;
	QFile m_file;
	KProgressDialog* m_progress;
	KFFMetar m_metar;
	int m_id;
	int m_currentID;

private slots:
	void setFavorite ( const QString & );
	void setProgress ( qint64, qint64 );
	void display ( bool );
	void cmdFinished ( int, bool );
	void cmdStarted ( int );
};



#endif // WIN_METARVIEW_H
