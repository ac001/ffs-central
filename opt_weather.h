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

#ifndef OPT_WEATHER_H
#define OPT_WEATHER_H

#include "ui_option_weather_base.h"
#include "opt_skeleton.h"
#include "win_metarview.h"
#include "win_metarcreate.h"

#include <QWidget>
#include <QButtonGroup>

class KFFWin_metarView;

/**
 * @author Didier Fabert <didier.fabert@gmail.com>
 */
class KFFOpt_weather : public KFFOpt_skeleton
{
		Q_OBJECT

	public:
		KFFOpt_weather ( QWidget *parent = 0 );

		~KFFOpt_weather();

	public slots:
		virtual void setMetarView ( KFFWin_metarView* );
		virtual void setMetarCreate ( KFFWin_metarCreate* );
		virtual void saveSettings();
		virtual void loadSettings();
		virtual bool getOptions ( QStringList & );

	private:
		Ui::opt_weather ui_widget;
		QButtonGroup* m_grp;
		KFFWin_metarView* m_metarView;
		KFFWin_metarCreate* m_metarCreate;
		bool m_update;

	private slots:
		void showViewer();
		void showCreator();
		void addCeilingSlot();
		void delCeilingSlot();
		void enableWindWidget ( int );
		void enableWidget ( int );
		void showContextMenu ( const QPoint& );
		void updateItem ( QTreeWidgetItem *, int );
};

#endif // OPT_WEATHER_H
