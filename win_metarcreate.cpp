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

#include "win_metarcreate.h"
#include "settings.h"
#include "shared.h"

#include <kiconloader.h>
#include <kmessagebox.h>
#include <kmenu.h>

#include <QLineEdit>
#include <QTreeWidget>
#include <QDebug>

KFFWin_metarCreate::KFFWin_metarCreate ( QWidget *parent )
		: QWidget ( parent )
{
	QStringList list;
	QStringList::Iterator it;

	ui_widget.setupUi ( this );

	list = m_metar.getPhenomenaPrefixListStr();
	ui_widget.comboBox_POPrefix->addItems ( list );
	list.clear();

	list = m_metar.getPhenomenaDescriptorListStr();
	ui_widget.comboBox_PODesc->addItems ( list );
	list.clear();

	list = m_metar.getPhenomenaListStr();
	ui_widget.comboBox_PO->addItems ( list );
	list.clear();
	
	list = m_metar.getCloudsListStr();
	ui_widget.comboBox_cloudsString1->addItems ( list );
	ui_widget.comboBox_cloudsString2->addItems ( list );
	ui_widget.comboBox_cloudsString3->addItems ( list );
	list.clear();

	m_unitGrp = new QButtonGroup ( this );
	m_unitGrp->addButton ( ui_widget.radioButton_metricsystem, 0 );
	m_unitGrp->addButton ( ui_widget.radioButton_imperialsystem, 1 );
	m_unitGrp->button ( 1 )->setChecked ( true );

	init();

	list = Settings::airport_favorite();
	for ( it = list.begin() ; it != list.end() ; it++ )
	{
		ui_widget.comboBox_favorite->addItem ( it->replace ( ":", " : " ) );
	}

	connect ( ui_widget.comboBox_favorite,
	          SIGNAL ( activated ( const QString & ) ),
	          SLOT ( setFavorite ( const QString & ) )
	        );
	connect ( ui_widget.checkBox_windDirectionGroup,
	          SIGNAL ( stateChanged ( int ) ),
	          SLOT ( enableWindDirectionGroup ( int ) )
	        );
	connect ( ui_widget.checkBox_windSpeedMax,
	          SIGNAL ( stateChanged ( int ) ),
	          SLOT ( enableWindMaxSpeed ( int ) )
	        );
	connect ( ui_widget.checkBox_cloudLayer1,
	          SIGNAL ( stateChanged ( int ) ),
	          SLOT ( enableCloudLayer1 ( int ) )
	        );
	connect ( ui_widget.checkBox_cloudLayer2,
	          SIGNAL ( stateChanged ( int ) ),
	          SLOT ( enableCloudLayer2 ( int ) )
	        );
	connect ( ui_widget.checkBox_cloudLayer3,
	          SIGNAL ( stateChanged ( int ) ),
	          SLOT ( enableCloudLayer3 ( int ) )
	        );
	connect ( ui_widget.checkBox_verticalVisibility,
	          SIGNAL ( stateChanged ( int ) ),
	          SLOT ( enableVerticalVisibility ( int ) )
	        );
	connect ( ui_widget.checkBox_auto,
	          SIGNAL ( stateChanged ( int ) ),
	          SLOT ( enableAuto ( int ) )
	        );
	connect ( ui_widget.btn_generate,
	          SIGNAL ( clicked () ),
	          SLOT ( generate () )
	        );
	connect ( ui_widget.spinBox_temperature,
	          SIGNAL ( valueChanged ( int ) ),
	          SLOT ( getHumidity () )
	        );
	connect ( ui_widget.spinBox_dewpoint,
	          SIGNAL ( valueChanged ( int ) ),
	          SLOT ( getHumidity () )
	        );
	connect ( ui_widget.comboBox_presureUnit,
	          SIGNAL ( activated ( int ) ),
	          SLOT ( changePresureUnit ( int ) )
	        );
	connect ( ui_widget.comboBox_visibilityUnit,
	          SIGNAL ( activated ( int ) ),
	          SLOT ( changeVisibilityUnit ( int ) )
	        );
	connect ( ui_widget.comboBox_visibilityUnit,
	          SIGNAL ( activated ( int ) ),
	          SLOT ( enablePoorVisibility () )
	        );
	connect ( ui_widget.spinBox_visibility,
	          SIGNAL ( valueChanged ( int ) ),
	          SLOT ( enablePoorVisibility () )
	        );
	connect ( ui_widget.comboBox_poorVisibility,
	          SIGNAL ( activated ( int ) ),
	          SLOT ( disablePoorVisibility ( int ) )
	        );
	connect ( ui_widget.pushButton_addPrecipitations,
	          SIGNAL ( clicked () ),
	          SLOT ( addPrecipitations () )
	        );
	connect ( ui_widget.comboBox_verticalVisibilityUnit,
	          SIGNAL ( activated ( int ) ),
	          SLOT ( changeVerticalVisibilityUnit ( int ) )
	        );
	ui_widget.treeWidget_precipitations->setContextMenuPolicy ( Qt::CustomContextMenu );
	connect ( ui_widget.treeWidget_precipitations,
	          SIGNAL ( customContextMenuRequested ( const QPoint & ) ),
	          this,
	          SLOT ( showContextMenu ( const QPoint & ) )
	        );
	m_metar.clear();
	enablePoorVisibility();
}


KFFWin_metarCreate::~KFFWin_metarCreate()
{
}

void KFFWin_metarCreate::setAirport ( QString airport )
{
	ui_widget.lineEdit_airport->setText ( airport );
}

void KFFWin_metarCreate::setFavorite ( const QString & favorite )
{
	ui_widget.lineEdit_airport->setText ( favorite.section ( " : ", 0, 0 ) );
}

void KFFWin_metarCreate::init()
{
	enableWindDirectionGroup ( 0 );
	enableWindMaxSpeed ( 0 );
	enableCloudLayer1 ( 0 );
	enableCloudLayer2 ( 0 );
	enableCloudLayer3 ( 0 );
	enableVerticalVisibility ( 0 );
	ui_widget.kdatewidget_metarDate->setDate ( QDate::currentDate() );
	ui_widget.timeEdit_metarTime->setTime ( QTime::currentTime() );
	getHumidity();
}

void KFFWin_metarCreate::enableWindDirectionGroup ( int state )
{
	ui_widget.spinBox_windDirectionVariable1->setEnabled ( state );
	ui_widget.spinBox_windDirectionVariable2->setEnabled ( state );
}

void KFFWin_metarCreate::enableWindMaxSpeed ( int state )
{
	ui_widget.spinBox_windSpeedMax->setEnabled ( state );
	ui_widget.txtLabel_windSpeedMaxUnit->setEnabled ( state );
}

void KFFWin_metarCreate::enableCloudLayer1 ( int state )
{
	ui_widget.spinBox_cloudAltitude1->setEnabled ( state );
	ui_widget.txtLabel_altitudeUnit1->setEnabled ( state );
	ui_widget.comboBox_cloudsString1->setEnabled ( state );
}

void KFFWin_metarCreate::enableCloudLayer2 ( int state )
{
	ui_widget.spinBox_cloudAltitude2->setEnabled ( state );
	ui_widget.txtLabel_altitudeUnit2->setEnabled ( state );
	ui_widget.comboBox_cloudsString2->setEnabled ( state );
}

void KFFWin_metarCreate::enableCloudLayer3 ( int state )
{
	ui_widget.spinBox_cloudAltitude3->setEnabled ( state );
	ui_widget.txtLabel_altitudeUnit3->setEnabled ( state );
	ui_widget.comboBox_cloudsString3->setEnabled ( state );
}

void KFFWin_metarCreate::enableVerticalVisibility ( int state )
{
	ui_widget.spinBox_verticalVisibility->setEnabled ( state );
	ui_widget.comboBox_verticalVisibilityUnit->setEnabled ( state );
}

void KFFWin_metarCreate::enableAuto ( int state )
{
	if ( state )
	{
		ui_widget.checkBox_cloudLayer1->setChecked( false );
		ui_widget.checkBox_cloudLayer2->setChecked( false );
		ui_widget.checkBox_cloudLayer3->setChecked( false );
	}
	ui_widget.checkBox_cloudLayer1->setEnabled( !state );
	enableCloudLayer1( !state );
	ui_widget.checkBox_cloudLayer2->setEnabled( !state );
	enableCloudLayer2( !state );
	ui_widget.checkBox_cloudLayer3->setEnabled( !state );
	enableCloudLayer3( !state );
}

/*
when value change, when unit change and system unit change
*/
void KFFWin_metarCreate::disablePoorVisibility ( int index )
{
	if ( !index )
	{
		ui_widget.comboBox_poorVisibility->hide();
		ui_widget.spinBox_visibility->setValue ( 1 );
		ui_widget.spinBox_visibility->show();
	}
}

void KFFWin_metarCreate::enablePoorVisibility()
{
	if ( ( ui_widget.comboBox_visibilityUnit->currentIndex() == 1 ) &&
	        ( ui_widget.spinBox_visibility->value() < 1 ) )
	{
		ui_widget.comboBox_poorVisibility->setCurrentIndex ( 1 );
		ui_widget.comboBox_poorVisibility->show();
		ui_widget.spinBox_visibility->hide();
	}
	else
	{
		ui_widget.comboBox_poorVisibility->hide();
		ui_widget.spinBox_visibility->show();
	}
}

void KFFWin_metarCreate::changePresureUnit ( int index )
{
	double val = ui_widget.kdoublenuminput_presure->value();

	if ( index )
	{
		ui_widget.kdoublenuminput_presure->setMinimum ( 0.0 );
		ui_widget.kdoublenuminput_presure->setMaximum ( 2000.0 );
		ui_widget.kdoublenuminput_presure->setDecimals ( 0 );
		ui_widget.kdoublenuminput_presure->setSingleStep ( 1.0 );
		ui_widget.kdoublenuminput_presure->setValue ( inHgTomBars ( val ) );
	}
	else
	{
		ui_widget.kdoublenuminput_presure->setMinimum ( 20.0 );
		ui_widget.kdoublenuminput_presure->setMaximum ( 40.0 );
		ui_widget.kdoublenuminput_presure->setDecimals ( 2 );
		ui_widget.kdoublenuminput_presure->setSingleStep ( 0.01 );
		ui_widget.kdoublenuminput_presure->setValue ( mBarsToinHg ( val ) );
	}
}

void KFFWin_metarCreate::changeVisibilityUnit ( int index )
{
	double val = ui_widget.spinBox_visibility->value();

	if ( index )
	{
		ui_widget.spinBox_visibility->setMaximum ( 10 );
		ui_widget.spinBox_visibility->setValue ( ( int ) mToUSMile ( val ) );
	}
	else
	{
		ui_widget.spinBox_visibility->setMaximum ( 9999 );
		ui_widget.spinBox_visibility->setValue ( ( int ) usMileToM ( val ) );
	}
}

void KFFWin_metarCreate::changeVerticalVisibilityUnit ( int index )
{
	double val = ui_widget.spinBox_verticalVisibility->value();
	int displayed;

	if ( index )
	{
		ui_widget.spinBox_verticalVisibility->setMaximum( 20000 );
		// get around number
		val = footToMeter ( val );
		displayed = ( val / 100 );
		displayed *= 100;
	}
	else
	{
		ui_widget.spinBox_verticalVisibility->setMaximum( 50000 );
		// get around number
		val = meterToFoot( val );
		displayed = ( val / 100 );
		displayed *= 100;
	}
	ui_widget.spinBox_verticalVisibility->setValue ( displayed );
}

void KFFWin_metarCreate::getHumidity()
{
	m_metar.setTemperature ( ui_widget.spinBox_temperature->text() );
	m_metar.setDewpoint ( ui_widget.spinBox_dewpoint->text() );
	ui_widget.lineEdit_humidity->setText ( m_metar.getHumidity() );
}

void KFFWin_metarCreate::addPrecipitations()
{
	QTreeWidgetItem * item;
	QStringList list;
	QString buffer, errostr;
	KFFPhenomena phenomena;

	phenomena.prefix = ui_widget.comboBox_POPrefix->currentText();
	phenomena.descriptor = ui_widget.comboBox_PODesc->currentText();
	phenomena.phenomena = ui_widget.comboBox_PO->currentText();
	if ( !m_metar.isPhenomenaValid( phenomena, errostr ) )
	{
		KMessageBox::sorry ( this, errostr );
		return;
	}

	list << ui_widget.comboBox_POPrefix->currentText();
	list << ui_widget.comboBox_PODesc->currentText();
	list << ui_widget.comboBox_PO->currentText();
	item = new QTreeWidgetItem ( ui_widget.treeWidget_precipitations, list );
	ui_widget.treeWidget_precipitations->addTopLevelItem ( item );
}

void KFFWin_metarCreate::generate()
{
	QString buffer;
	int index = 0;
	double val;
	QStringList list;
	QTreeWidgetItem* item;
	KFFPhenomena phenomena;
	KFFPhenomenaList phenomenas;

	m_metar.clear();

	// Set Location ID
	if ( ui_widget.lineEdit_airport->text().isEmpty() )
	{
		KMessageBox::sorry ( this, i18n ( "Airport ID cannot be empty" ) );
		return;
	}
	m_metar.setID ( ui_widget.lineEdit_airport->text() );

	if ( ui_widget.radioButton_metricsystem->isChecked() )
	{
		m_metar.setUnitSystem ( KFFMetar::UNIT_METRIC );
	}
	else
	{
		m_metar.setUnitSystem ( KFFMetar::UNIT_IMPERIAL );
	}

	// Set Temperature and dewpoint and calculate humidity
	getHumidity();

	// Set auto METAR if any
	m_metar.setAutoReport ( ui_widget.checkBox_auto->isChecked() );

	// Set Date
	m_metar.setDate ( ui_widget.kdatewidget_metarDate->date() );
	// Set Time
	m_metar.setTime ( ui_widget.timeEdit_metarTime->time() );

	// Set wind parameters
	m_metar.setWindDirection ( ui_widget.spinBox_windDirection->text() );
	m_metar.setWindSpeed ( ui_widget.spinBox_windSpeed->text() );
	if ( ui_widget.checkBox_windDirectionGroup->isChecked() )
	{
		m_metar.setWindDirGrp ( ui_widget.spinBox_windDirectionVariable1->text(),
		                        ui_widget.spinBox_windDirectionVariable2->text() );
	}
	if ( ui_widget.checkBox_windSpeedMax->isChecked() )
	{
		m_metar.setWindSpeedMax ( ui_widget.spinBox_windSpeedMax->text() );
	}

	// Set Visibility
	buffer .clear();
	val = ui_widget.spinBox_visibility->value();
	if ( ui_widget.comboBox_poorVisibility->isVisible() )
	{
		buffer = ui_widget.comboBox_poorVisibility->currentText();
	}
	else
	{
		if ( ui_widget.comboBox_visibilityUnit->currentIndex() == 0 &&
		        ui_widget.radioButton_imperialsystem->isChecked() )
		{
			val = mToUSMile ( val );
			if ( val < 1.0 )
			{
				if ( val <= 0.25 )
				{
					buffer = "1/4";
				}
				else if ( val <= 0.5 )
				{
					buffer = "1/2";
				}
				else if ( val <= 0.75 )
				{
					buffer = "3/4";
				}
			}
		}
		else if ( ui_widget.comboBox_visibilityUnit->currentIndex() == 1 &&
		          ui_widget.radioButton_metricsystem->isChecked() )
		{
			val = usMileToM ( val );
		}
	}

	if ( buffer.isEmpty() )
	{
		buffer.setNum ( val, 'f', 0 );
	}
	m_metar.setVisibility ( buffer );

	// Presure
	val = ui_widget.kdoublenuminput_presure->value();
	if ( ui_widget.comboBox_presureUnit->currentIndex() == 1 &&
	        ui_widget.radioButton_imperialsystem->isChecked() )
	{
		val = mBarsToinHg ( val ) * 100.0;
	}
	else if ( ui_widget.comboBox_presureUnit->currentIndex() == 0 )
	{
		if ( ui_widget.radioButton_metricsystem->isChecked() )
		{
			val = inHgTomBars ( val );
		}
		else
		{
			val = val * 100.0;
		}
	}
	buffer.setNum ( val, 'f', 0 );
	m_metar.setPresure ( buffer );

	// Set Cloud Layers
	//m_metar.setClouds( QString clouds, QString altitude, int layer )
	if ( ui_widget.checkBox_cloudLayer1->isChecked() )
	{
		buffer = getCloud ( ui_widget.comboBox_cloudsString1->currentIndex() );
		m_metar.setClouds ( buffer, ui_widget.spinBox_cloudAltitude1->text(), index++ );
	}
	if ( ui_widget.checkBox_cloudLayer2->isChecked() )
	{
		buffer = getCloud ( ui_widget.comboBox_cloudsString2->currentIndex() );
		m_metar.setClouds ( buffer, ui_widget.spinBox_cloudAltitude2->text(), index++ );
	}
	if ( ui_widget.checkBox_cloudLayer3->isChecked() )
	{
		buffer = getCloud ( ui_widget.comboBox_cloudsString3->currentIndex() );
		m_metar.setClouds ( buffer, ui_widget.spinBox_cloudAltitude3->text(), index++ );
	}

	// Precipitations and Obscuring

	item = ui_widget.treeWidget_precipitations->topLevelItem ( 0 );

	while ( item )
	{
		phenomena.clear();
		phenomena.prefix = item->text ( 0 );
		phenomena.descriptor = item->text ( 1 );
		phenomena.phenomena = item->text ( 2 );
		phenomenas << phenomena;
		item = ui_widget.treeWidget_precipitations->itemBelow ( item );
	}
	m_metar.setPhenomena ( phenomenas );

	ui_widget.txtEdit_metar->setText ( m_metar.getMetar() );
}

void KFFWin_metarCreate::showContextMenu ( const QPoint & pos )
{
	KIconLoader loader;
	QPixmap pixmap;
	QIcon icon;
	QAction* remove;
	QAction* removeall;
	QAction* moveup;
	QAction* movedown;
	KMenu menu ( this );

	pixmap = loader.loadIcon ( "edit-delete", KIconLoader::Small );
	icon.addPixmap ( pixmap );
	remove = new QAction ( icon, tr2i18n ( "&Remove" ), this );
	remove->setStatusTip ( tr2i18n ( "Remove this phenomena" ) );
	connect ( remove, SIGNAL ( triggered() ), this, SLOT ( removePhenomena() ) );
	
	pixmap = loader.loadIcon ( "edit-clear-list", KIconLoader::Small );
	icon.addPixmap ( pixmap );
	removeall = new QAction ( icon, tr2i18n ( "&Clear list" ), this );
	removeall->setStatusTip ( tr2i18n ( "Remove all phenomenas" ) );
	connect ( removeall, SIGNAL ( triggered() ), ui_widget.treeWidget_precipitations, SLOT( clear() ) );

	pixmap = loader.loadIcon ( "arrow-up", KIconLoader::Small );
	icon.addPixmap ( pixmap );
	moveup = new QAction ( icon, tr2i18n ( "Move &up" ), this );
	moveup->setStatusTip ( tr2i18n ( "Move up this phenomena" ) );
	connect ( moveup, SIGNAL ( triggered() ), this, SLOT ( moveUpPhenomena() ) );

	pixmap = loader.loadIcon ( "arrow-down", KIconLoader::Small );
	icon.addPixmap ( pixmap );
	movedown = new QAction ( icon, tr2i18n ( "Move &down" ), this );
	movedown->setStatusTip ( tr2i18n ( "Move down this phenomena" ) );
	connect ( movedown, SIGNAL ( triggered() ), this, SLOT ( moveDownPhenomena() ) );

	menu.addAction ( removeall );
	menu.addSeparator();
	menu.addAction ( remove );
	menu.addSeparator();
	menu.addAction ( moveup );
	menu.addAction ( movedown );
	menu.exec ( mapToGlobal ( pos + ui_widget.treeWidget_precipitations->pos() ) );
}

void KFFWin_metarCreate::removePhenomena()
{
	QTreeWidgetItem* item;

	item = ui_widget.treeWidget_precipitations->currentItem();
	if ( item )
	{
		delete item;
	}
}

void KFFWin_metarCreate::moveUpPhenomena()
{
	QTreeWidgetItem* item;
	int index;

	item = ui_widget.treeWidget_precipitations->currentItem();
	index = ui_widget.treeWidget_precipitations->indexOfTopLevelItem ( item );
	if ( index > 0 )
	{
		item = ui_widget.treeWidget_precipitations->takeTopLevelItem ( index );
		ui_widget.treeWidget_precipitations->insertTopLevelItem ( --index, item );
		ui_widget.treeWidget_precipitations->setCurrentItem ( item );
	}
}

void KFFWin_metarCreate::moveDownPhenomena()
{
	QTreeWidgetItem* item;
	int index, maxindex;

	item = ui_widget.treeWidget_precipitations->currentItem();
	index = ui_widget.treeWidget_precipitations->indexOfTopLevelItem ( item );
	maxindex = ui_widget.treeWidget_precipitations->topLevelItemCount();
	if ( index < --maxindex )
	{
		item = ui_widget.treeWidget_precipitations->takeTopLevelItem ( index );
		ui_widget.treeWidget_precipitations->insertTopLevelItem ( ++index, item );
		ui_widget.treeWidget_precipitations->setCurrentItem ( item );
	}
}

// Work around
// Class KFFMetar must provide cloud name list (i18n) and get abreviation by its i18n name
QString getCloud ( int index )
{
	QString str;

	switch ( index )
	{
		case 0:
		{
			str = "FEW";
			break;
		}
		case 1:
		{
			str = "SCT";
			break;
		}
		case 2:
		{
			str = "BKN";
			break;
		}
		case 3:
		{
			str = "OVC";
			break;
		}
		default :
		{
			str.clear();
		}
	}
	return str;
}
