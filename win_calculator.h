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
 *     (___)_)   File : win_calculator.h                    ||--|| *         *
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

#ifndef WIN_CALCULATOR_H
#define WIN_CALCULATOR_H

#include "ui_win_calculator_base.h"

#include <QWidget>

/**
	@author
*/

class KFFWin_Calculator : public QWidget
{
	Q_OBJECT

public:
	KFFWin_Calculator( QWidget *parent = 0 );

	~KFFWin_Calculator();

private:
	Ui::win_calculator ui_widget;
	enum { KILOMETER, US_MILE, NAUTIC_MILE, METER, FEET };
	
private slots:
	void calculate();
	void convertCalc( int );
	void convertWUnit();
	void convertUnit1( int );
	void convertUnit2( int );
	void convert( int, int );
};

#endif // WIN_CALCULATOR_H
