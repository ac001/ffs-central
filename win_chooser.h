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

#ifndef WIN_CHOOSER_H
#define WIN_CHOOSER_H

#include <QWidget>
#include<QListWidget>

#include "ui_win_chooser_base.h"

/**
	@author Didier Fabert <didier.fabert@gmail.com>
*/

class KFFWin_Chooser : public QWidget
{
	Q_OBJECT

public:
	KFFWin_Chooser( QWidget *parent = 0 );

	virtual ~KFFWin_Chooser();

	enum
	{
		KFFDLG_SAVE,
		KFFDLG_OPEN,
	} WidgetType;

public slots:
	virtual void setTitle( const QString & );
	virtual void setButtonText( const QString & );
	virtual void setButtonIcon( const QIcon & );
	virtual void insertStringList( const QStringList & );
	virtual void setDefaultText( const QString & );
	virtual void setType( int );

private:
	Ui::win_chooser ui_widget;
	int m_type;

private slots:
	void sendSignal();
	void setCurrentText( QListWidgetItem * );
	void showContextMenu( const QPoint & );
	void remove();

signals:
	void selected( const QString & );
	void haveDirtyList();
};

#endif // WIN_CHOOSER_H
