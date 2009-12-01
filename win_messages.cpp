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
 *     (___)_)   File : win_messages.cpp                    ||--|| *         *
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

#include "win_messages.h"

#include <kmessagebox.h>

KFFWin_messages::KFFWin_messages( QWidget *parent )
		: QWidget( parent )
{
	ui_widget.setupUi ( this );
	connect ( ui_widget.btn_clear,
	          SIGNAL( clicked() ),
	          ui_widget.textEdit,
	          SLOT( clear() )
	        );
}


KFFWin_messages::~KFFWin_messages()
{
}

void KFFWin_messages::save()
{
	KMessageBox::information( this, "Not implemented yet !" );
}

void KFFWin_messages::insertTitle( const QString& title )
{
	ui_widget.textEdit->append( "<h3>" + title + "</h3>" );
}

void KFFWin_messages::insertText( const QString& text )
{
	ui_widget.textEdit->append( text );
}

void KFFWin_messages::insertError(const QString& text)
{
	ui_widget.textEdit->append( "<span style=\" color:#ff5500;\">" + text + "</span>" );
}

