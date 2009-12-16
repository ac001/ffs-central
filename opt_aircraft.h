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

#ifndef OPT_AIRCRAFT_H
#define OPT_AIRCRAFT_H

#include "ui_option_aircraft_base.h"
#include "opt_skeleton.h"
#include "widget_render.h"

#include "widget_render.h"

#include <QWidget>

#include <KProcess>

/**
 * @author Didier Fabert <didier.fabert@gmail.com>
 */

class KFFAircraftData
{
public:
	KFFAircraftData() {};
	~KFFAircraftData() {};
	QString description;
	QString model;
	QString texture;
};

class KFFOpt_aircraft : public KFFOpt_skeleton
{
	Q_OBJECT

public:
	KFFOpt_aircraft( QWidget *parent = 0 );

	~KFFOpt_aircraft();

public slots:
	virtual void saveSettings();
	virtual void loadSettings();
	virtual bool getOptions(QStringList &);

protected:
	virtual void resizeEvent( QResizeEvent * event );
	
private:
	Ui::opt_aircraft ui_widget;
	KProcess* m_process;
	KFFWidget_Render *m_render;
	QString m_input;
	QString m_error;
	KUrl m_url;
	QMap< QString, KFFAircraftData> modelfile;

	void reloadList( bool showMessage = false );
	bool searchData( QString file, KFFAircraftData & data );

private slots:
	void reload();
	void getAircraft();
	void setAircraft( QString );
	void loadModel();

	void readData();
	void readError();
	void closeProcess(int, QProcess::ExitStatus);

signals:
	void settingsChanged();
};

#endif // OPT_AIRCRAFT_H
