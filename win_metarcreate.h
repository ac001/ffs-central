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

#ifndef WIN_METARCREATE_H
#define WIN_METARCREATE_H

#include "ui_win_metarcreate_base.h"
#include "metar.h"

#include <QWidget>

class KFF_Metar;

/**
 * @author
 */
class KFFWin_metarCreate : public QWidget
{
	Q_OBJECT
public:
	KFFWin_metarCreate ( QWidget *parent = 0 );

	~KFFWin_metarCreate();

	void init();

private:
	Ui::win_metarcreate ui_widget;
	KFFMetar m_metar;
	QButtonGroup* m_unitGrp;

public slots:
	void setAirport( QString airport );
	
private slots:
	void setFavorite( const QString & );
	void enableWindDirectionGroup ( int );
	void enableWindMaxSpeed ( int );
	void enableCloudLayer1 ( int );
	void enableCloudLayer2 ( int );
	void enableCloudLayer3 ( int );
	void enableVerticalVisibility ( int );
	void enableAuto ( int );
	void enablePoorVisibility();
	void disablePoorVisibility( int );
	void changePresureUnit( int );
	void changeVisibilityUnit( int );
	void changeVerticalVisibilityUnit ( int );
	void getHumidity();
	void generate();
	void addPrecipitations();
	void showContextMenu( const QPoint& );
	void removePhenomena();
	void moveUpPhenomena();
	void moveDownPhenomena();

};

QString getCloud ( int );

#endif // WIN_METARCREATE_H
