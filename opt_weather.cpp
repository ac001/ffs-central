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

#include "opt_weather.h"
#include "settings.h"

#include <kiconloader.h>
#include <kmessagebox.h>
#include <kmenu.h>

KFFOpt_weather::KFFOpt_weather ( QWidget *parent )
		: KFFOpt_skeleton ( parent )
{
	QString img = Settings::data_dir() + "/clouds.svg";
	ui_widget.setupUi ( this );
	ui_widget.widgetLogo->load ( img );
	m_metarView = 0;
	m_update = false;

	m_grp = new QButtonGroup ( this );
	m_grp->addButton ( ui_widget.radioButton_realWeather, 0 );
	m_grp->addButton ( ui_widget.radioButton_metar, 1 );
	m_grp->addButton ( ui_widget.radioButton_edited, 2 );

	connect ( ui_widget.btn_getWeather,
	          SIGNAL ( clicked() ),
	          SLOT ( showViewer() )
	        );

	connect ( ui_widget.btn_metarEditor,
	          SIGNAL ( clicked() ),
	          SLOT ( showCreator() )
	        );

	connect ( ui_widget.BTN_Clouds_Add,
	          SIGNAL ( clicked() ),
	          SLOT ( addCeilingSlot() )
	        );

	connect ( ui_widget.CB_RandomWind,
	          SIGNAL ( stateChanged ( int ) ),
	          SLOT ( enableWindWidget ( int ) )
	        );

	ui_widget.treeWidget_clouds->setContextMenuPolicy ( Qt::CustomContextMenu );
	connect ( ui_widget.treeWidget_clouds,
	          SIGNAL ( customContextMenuRequested ( const QPoint & ) ),
	          this,
	          SLOT ( showContextMenu ( const QPoint & ) )
	        );
	connect ( ui_widget.treeWidget_clouds,
	          SIGNAL ( itemActivated ( QTreeWidgetItem *, int ) ),
	          this,
	          SLOT ( updateItem ( QTreeWidgetItem *, int ) )
	        );

	connect ( m_grp, SIGNAL ( buttonClicked ( int ) ), SLOT ( enableWidget ( int ) ) );
}


KFFOpt_weather::~KFFOpt_weather()
{
}

void KFFOpt_weather::showViewer()
{
	if ( m_metarView )
	{
		m_metarView->show();
	}
}

void KFFOpt_weather::showCreator()
{
	if ( m_metarCreate )
	{
		m_metarCreate->show();
	}
}

void KFFOpt_weather::setMetarView ( KFFWin_metarView* widget )
{
	m_metarView = widget;
}

void KFFOpt_weather::setMetarCreate ( KFFWin_metarCreate* widget )
{
	m_metarCreate = widget;
}

bool KFFOpt_weather::getOptions ( QStringList & list )
{
	QTreeWidgetItem* item;
	float turbulence;
	QString buffer, buffer2;
	uint i = 0;

	if ( ui_widget.radioButton_edited->isChecked() )
	{
		list << "--disable-real-weather-fetch";

		if ( ui_widget.CB_RandomWind->isChecked() )
		{
			list << "--random-wind";
		}
		else
		{
			list << "--wind=" + ui_widget.SpinBox_DirectionWind->text()
			+ "@" + ui_widget.SpinBox_SpeedWind->text();
		}

		list << "--visibility=" + ui_widget.SpinBox_Visibility->text();

		buffer = buffer.setNum ( ui_widget.Slider_Turbulence->value(), 10 );

		turbulence = buffer.toFloat() / 10;

		buffer = buffer.number ( turbulence, 'f', 1 );

		list << "--turbulence=" + buffer;

		item = ui_widget.treeWidget_clouds->topLevelItem ( 0 );

		i = 0;

		while ( item )
		{
			buffer2.setNum ( i, 10 );
			list << "--prop:environment/clouds/layer[" + buffer2 + "]/elevation-ft=" + item->text ( 2 );
			list << "--prop:environment/clouds/layer[" + buffer2 + "]/thickness-ft=" + item->text ( 1 );
			list << "--prop:environment/clouds/layer[" + buffer2 + "]/coverage=" + item->text ( 0 );
			item = ui_widget.treeWidget_clouds->itemBelow ( item );
			i++;
		}
	}

	if ( ui_widget.radioButton_realWeather->isChecked() )
	{
		list << "--enable-real-weather-fetch";
	}

	/*if ( ui_widget.radioButton_metar->isChecked() )
	{
		 list = decodeMetar();
	}*/

	return true;
}

void KFFOpt_weather::saveSettings()
{
	QStringList list;
	QTreeWidgetItem* item;
	QString buffer = "";

	item = ui_widget.treeWidget_clouds->topLevelItem ( 0 );

	while ( item )
	{
		for ( int i = 0 ; i < ui_widget.treeWidget_clouds->columnCount() ; ++i )
		{
			buffer.append ( item->text ( i ) + "|" );
		}

		list << buffer;

		item = ui_widget.treeWidget_clouds->itemBelow ( item );
	}

	Settings::setWeather_wind_speed ( ui_widget.SpinBox_DirectionWind->value() );

	Settings::setWeather_wind_direction ( ui_widget.SpinBox_SpeedWind->value() );
	Settings::setWeather_wind_random ( ui_widget.CB_RandomWind->isChecked() );
	Settings::setWeather_wind_random ( ui_widget.SpinBox_Visibility->value() );
	Settings::setWeather_turbulences ( ui_widget.Slider_Turbulence->value() );
	Settings::setWeather_clouds ( list );
	Settings::setWeather_selected ( m_grp->checkedId() );
	Settings::self()->writeConfig();
}

void KFFOpt_weather::loadSettings()
{
	QTreeWidgetItem* clouditem;
	QStringList list, itemdata;
	QStringList::Iterator it;

	ui_widget.treeWidget_clouds->clear();
	list = Settings::weather_clouds();

	for ( it = list.begin() ; it != list.end() ; it++ )
	{
		itemdata = it->split ( "|" );
		clouditem = new QTreeWidgetItem ( ui_widget.treeWidget_clouds, itemdata );
		//clouditem->setIcon( 0, m_towerIcon );
		ui_widget.treeWidget_clouds->addTopLevelItem ( clouditem );
		itemdata.clear();
	}

	ui_widget.SpinBox_DirectionWind->setValue ( Settings::weather_wind_speed() );

	ui_widget.SpinBox_SpeedWind->setValue ( Settings::weather_wind_direction() );
	ui_widget.CB_RandomWind->setChecked ( Settings::weather_wind_random() );
	ui_widget.SpinBox_Visibility->setValue ( Settings::weather_wind_random() );
	ui_widget.Slider_Turbulence->setValue ( Settings::weather_turbulences() );
	m_grp->button ( Settings::weather_selected() )->setChecked ( true );
	enableWidget ( Settings::weather_selected() );
}

void KFFOpt_weather::showContextMenu ( const QPoint &pos )
{
	KIconLoader loader;
	QPixmap pixmap;
	QIcon icon;
	QAction* remove;
	KMenu menu ( this );
	QPoint offset ( 0, 40 );

	pixmap = loader.loadIcon ( "edit-delete", KIconLoader::Small );
	icon.addPixmap ( pixmap );
	remove = new QAction ( icon, tr2i18n ( "&Remove" ), this );
	remove->setStatusTip ( tr2i18n ( "Remove this cloud layer" ) );
	connect ( remove, SIGNAL ( triggered() ), this, SLOT ( delCeilingSlot() ) );

	menu.addAction ( remove );
	menu.exec ( mapToGlobal ( pos + ui_widget.tabWidget_edited->pos() + ui_widget.treeWidget_clouds->pos() + offset ) );
}

void KFFOpt_weather::delCeilingSlot()
{
	QTreeWidgetItem* item;

	item = ui_widget.treeWidget_clouds->currentItem();
	ui_widget.treeWidget_clouds->takeTopLevelItem ( ui_widget.treeWidget_clouds->indexOfTopLevelItem ( item ) );
}

void KFFOpt_weather::addCeilingSlot()
{
	QStringList itemdata;
	QString buffer;
	QTreeWidgetItem* clouditem;
	//unused int index;

	//index = ui_widget.treeWidget_clouds->indexOfTopLevelItem(  );
	if ( m_update || ( ui_widget.treeWidget_clouds->topLevelItemCount() < 6 ) )
	{
		switch ( ui_widget.ComboBox_Clouds->currentIndex() )
		{

			case 0:
				buffer = "few";
				break;

			case 1:
				buffer = "scattered";
				break;

			case 2:
				buffer = "broken";
				break;

			case 3:
				buffer = "overcast";
				break;

			default:
				return;
		}
		if ( m_update )
		{
			clouditem = ui_widget.treeWidget_clouds->currentItem();
			clouditem->setText ( 0, buffer );
			clouditem->setText ( 1, ui_widget.SpinBox_CloudsAltitude->text() );
			clouditem->setText ( 2, ui_widget.SpinBox_CloudsTickness->text() );
			m_update = false;
			ui_widget.BTN_Clouds_Add->setText ( i18n ( "Add" ) );
		}
		else
		{
			itemdata << buffer;
			itemdata << ui_widget.SpinBox_CloudsAltitude->text();
			itemdata << ui_widget.SpinBox_CloudsTickness->text();
			clouditem = new QTreeWidgetItem ( ui_widget.treeWidget_clouds, itemdata );
			//clouditem->setIcon( 0, m_towerIcon );
			ui_widget.treeWidget_clouds->addTopLevelItem ( clouditem );
		}
	}
}

void KFFOpt_weather::updateItem ( QTreeWidgetItem * item, int column )
{
	int index = -1;

	m_update = true;
	ui_widget.SpinBox_CloudsAltitude->setValue ( item->text ( 1 ).toInt() );
	ui_widget.SpinBox_CloudsTickness->setValue ( item->text ( 2 ).toInt() );
	if ( item->text ( 0 ) == "few" )
	{
		index = 0;
	}
	else if ( item->text ( 0 ) == "scattered" )
	{
		index = 1;
	}
	else if ( item->text ( 0 ) == "broken" )
	{
		index = 2;
	}
	else if ( item->text ( 0 ) == "overcast" )
	{
		index = 3;
	}
	ui_widget.ComboBox_Clouds->setCurrentIndex ( index );
	ui_widget.BTN_Clouds_Add->setText ( i18n ( "Update" ) );
}

void KFFOpt_weather::enableWindWidget ( int state )
{
	bool enabled = true;

	if ( state )
	{
		enabled = false;
	}

	ui_widget.textLabel_wind_speed->setEnabled ( enabled );

	ui_widget.textLabel_wind_direction->setEnabled ( enabled );
	ui_widget.SpinBox_DirectionWind->setEnabled ( enabled );
	ui_widget.SpinBox_SpeedWind->setEnabled ( enabled );
}


void KFFOpt_weather::enableWidget ( int button )
{
	switch ( button )
	{

		case 0:
		{
			ui_widget.btn_metarEditor->setEnabled ( false );
			ui_widget.tabWidget_edited->setEnabled ( false );
			break;
		}

		case 1:
		{
			ui_widget.btn_metarEditor->setEnabled ( true );
			ui_widget.tabWidget_edited->setEnabled ( false );
			break;
		}

		case 2:
		{
			ui_widget.btn_metarEditor->setEnabled ( false );
			ui_widget.tabWidget_edited->setEnabled ( true );
			break;
		}
	}
}
