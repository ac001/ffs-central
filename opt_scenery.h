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

#ifndef OPT_SCENERY_H
#define OPT_SCENERY_H

#include "ui_option_scenery_base.h"
#include <opt_skeleton.h>

#include <QWidget>
#include <QFile>

/**
 * @author Didier Fabert <didier.fabert@gmail.com>
 */

class KFFScenarioData
{

public:
	KFFScenarioData() {};

	~KFFScenarioData() {};

	QString description;
	QString type;
};

class KFFOpt_scenery : public KFFOpt_skeleton
{
	Q_OBJECT

public:
	KFFOpt_scenery( QWidget *parent = 0 );

	~KFFOpt_scenery();

	void reloadScenarii(bool showMessage = true);
	
public slots:
	virtual void saveSettings();
	virtual void loadSettings();
	virtual bool getOptions(QStringList &);

private:
	Ui::opt_scenery ui_widget;
	QMap<QString, KFFScenarioData> m_scenarii;
	QPixmap m_aircraftIcon;
	QPixmap m_weatherIcon;
	QPixmap m_shipIcon;
	QPixmap m_trainIcon;
	QPixmap m_unknowIcon;

private slots:
	void reload();
	void getScenarii();
	void searchData( QFile* file );
};

#endif // OPT_SCENERY_H
