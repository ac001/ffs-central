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

#ifndef OPT_SKELETON_H
#define OPT_SKELETON_H

#include <QtGui/QLabel>
#include <QtCore/QString>

/**
 * @author Didier Fabert <didier.fabert@gmail.com>
 */

class KFFWin_messages;

class KFFOpt_skeleton : public QWidget
{
	Q_OBJECT

protected:
	KFFOpt_skeleton( QWidget *parent = 0 );

	~KFFOpt_skeleton();

	KFFWin_messages* m_output;
	
	//static const QString HEADER_STYLE;
	void wSetupHeader(QLabel *);

public slots:
	virtual void saveSettings();
	virtual void loadSettings();
	virtual bool getOptions( QStringList & );
	virtual void setOutput( KFFWin_messages* );

public:

	enum StartPlace
	{
		START_ON_AIRPORT,
		START_ON_CARRIER,
		START_ON_TOP,
		START_ANYWHERE,
	};

	enum Navaids
	{
		NAV1_CURRENT,
		NAV1_STANDBY,
		NAV1_RADIAL,
		NAV2_CURRENT,
		NAV2_STANDBY,
		NAV2_RADIAL,
		ADF_CURRENT,
		ADF_STANDBY,
		ADF_ROTATION,
		DME_CURRENT,
		COM1_CURRENT,
		COM1_STANDBY,
		COM2_CURRENT,
		COM2_STANDBY,
	};
};

#endif // OPT_SKELETON_H
