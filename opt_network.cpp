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

#include "opt_network.h"
#include "settings.h"

#include <QComboBox>
#include <QLineEdit>

KFFOpt_network::KFFOpt_network( QWidget *parent )
		: KFFOpt_skeleton( parent )
{
	//QString img = Settings::data_dir() + "/clouds.svg"; - pete@ffs nuked image

	ui_widget.setupUi ( this );
	wSetupHeader(ui_widget.wHeaderLabel);
	//ui_widget.widgetLogo->load ( img ); - pete@ffs nuked image

	m_grp = new QButtonGroup( this );
	m_grp->addButton( ui_widget.RB_multi_none, 0 );
	m_grp->addButton( ui_widget.rb_multi_internet, 1 );
	connect( m_grp, SIGNAL( buttonClicked( int ) ), SLOT( enableWidget( int ) ) );
	connect( ui_widget.btn_add, SIGNAL( clicked() ), SLOT( addServer() ) );
}


KFFOpt_network::~KFFOpt_network()
{
}

void KFFOpt_network::saveSettings()
{
	QStringList list;

	for ( int i = 0 ; i < ui_widget.combo_server->count() ; i++ )
	{
		list << ui_widget.combo_server->itemText( i );
	}

	Settings::setNetwork_server( list );

	Settings::setNetwork_myip( ui_widget.lineedit_ip->text() );
	Settings::setNetwork_callsign( ui_widget.lineedit_callsign->text() );
	Settings::setNetwork_refresh( ui_widget.spinbox_refresh->value() );
	Settings::setNetwork_port( ui_widget.spinbox_port->value() );
	Settings::setNetwork_selected( m_grp->checkedId() );
	Settings::self()->writeConfig();

}

void KFFOpt_network::loadSettings()
{
	ui_widget.lineedit_ip->setText( Settings::network_myip() );
	ui_widget.lineedit_callsign->setText( Settings::network_callsign() );
	ui_widget.spinbox_refresh->setValue( Settings::network_refresh() );
	ui_widget.spinbox_port->setValue( Settings::network_port() );
	ui_widget.combo_server->clear();
	ui_widget.combo_server->addItems( Settings::network_server() );
	m_grp->button( Settings::network_selected() )->setChecked( true );
	enableWidget( Settings::network_selected() );
}

bool KFFOpt_network::getOptions( QStringList & list )
{
	QString buffer;

	if ( m_multi )
	{
		buffer = ui_widget.spinbox_refresh->text();
		buffer.append( "," );
		buffer.append( ui_widget.lineedit_ip->text() );
		buffer.append( "," );
		buffer.append( ui_widget.spinbox_port->text() );
		list << "--multiplay=in," + buffer;

		buffer = ui_widget.spinbox_refresh->text();
		buffer.append( "," );
		buffer.append( ui_widget.combo_server->currentText() );
		buffer.append( "," );
		buffer.append( ui_widget.spinbox_port->text() );
		list << "--multiplay=out," + buffer;
	}
	list << "--callsign=" + ui_widget.lineedit_callsign->text();

	return true;
}

void KFFOpt_network::addServer()
{
	//ui_widget.combo_server->addItem(i18n("new server"));
	ui_widget.combo_server->setEditText(i18n("new server"));
}

void KFFOpt_network::enableWidget( int button )
{
	switch ( button )
	{

		case 0:
		{
			ui_widget.groupbox_multi->setEnabled( false );
			break;
		}

		case 1:
		{
			ui_widget.groupbox_multi->setEnabled( true );
			break;
		}
	}

	m_multi = button;
}

