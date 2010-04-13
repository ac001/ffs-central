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

#include "opt_carrier.h"
#include "settings.h"

#include <kmessagebox.h>

#include <QButtonGroup>
#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomElement>
#include <QMap>

KFFOpt_carrier::KFFOpt_carrier( QWidget *parent )
		: KFFOpt_skeleton( parent )
{
	//QString img = Settings::data_dir() + "/carrier.svg"; pete@ffs nuked image

	ui_widget.setupUi ( this );
	//ui_widget.widgetLogo->load ( img ); pete@ffs nuked image

	connect( ui_widget.btn_Reload,
	         SIGNAL( clicked() ),
	         SLOT( reload() )
	       );
	connect( ui_widget.combo_CarrierList,
	         SIGNAL( activated( QString ) ),
	         SLOT( setCarrier( QString ) )
		   );
	reloadCarrier(false);
}


KFFOpt_carrier::~KFFOpt_carrier()
{
}

void KFFOpt_carrier::reload()
{
	reloadCarrier(true);
}

void KFFOpt_carrier::reloadCarrier(bool showMessage)
{
	ui_widget.combo_CarrierList->clear();
	ui_widget.combo_place->clear();
	scenariiList.clear();
	getCarrier();
	int i = 0;

	QMapIterator<QString, KFFCarrierData> it( m_carriers );

	while ( it.hasNext() )
	{
		it.next();
		ui_widget.combo_CarrierList->insertItem( i, it.key() );
		if (i == 0)
		{
			setCarrier(it.key());
		}
		i++;
	}
	loadSettings();
	if (showMessage)
	{
		KMessageBox::information(this, i18n("Reloaded") );
	}
}

void KFFOpt_carrier::setCarrier( QString carrier)
{
	QStringList list;QStringList::Iterator it;
	int i = 0;

	ui_widget.combo_place->clear();
	for ( it = m_carriers[carrier].place.begin() ; it != m_carriers[carrier].place.end() ; ++it)
	{
		ui_widget.combo_place->insertItem( i++, *it );
	}
}

void KFFOpt_carrier::saveSettings()
{
	Settings::setCarrier_selected(ui_widget.combo_CarrierList->currentIndex());
	Settings::setCarrier_place(ui_widget.combo_place->currentIndex());
	Settings::self()->writeConfig();
}

void KFFOpt_carrier::loadSettings()
{
	ui_widget.combo_place->setCurrentIndex(Settings::carrier_place());
	ui_widget.combo_CarrierList->setCurrentIndex(Settings::carrier_selected());
}

bool KFFOpt_carrier::getOptions(QStringList & list)
{
	emit( needScenario(scenariiList, ui_widget.combo_CarrierList->currentText()) );
	list << "--carrier=" + ui_widget.combo_CarrierList->currentText();
	list << "--parkpos=" + ui_widget.combo_place->currentText();
	return true;
}

void KFFOpt_carrier::getCarrier()
{
	QDir directory;
	QString buffer, filename;
	QStringList list, filter;
	QStringList::Iterator it;
	QFile file;

	// make list of all xml file in $FG_ROOT/AI directory
	directory.setPath( Settings::fg_root() + "/AI" );
	filter << "*.xml";
	list = directory.entryList ( filter, QDir::Files, QDir::Name );

	// For each file

	for ( it = list.begin(); it != list.end(); ++it )
	{
		filename = Settings::fg_root() + "/AI/" + *it;
		file.setFileName( filename );

		if ( file.open( QFile::ReadOnly ) )
		{
			searchData( &file );
			file.close();
		}
	}
}

void KFFOpt_carrier::searchData( QFile* file )
{
	QDomDocument doc;
	QDomElement root;
	QDomNode parent;
	QDomNode child;
	QDomNode parking;
	QDomElement e_parent;
	QDomElement e_child;
	QDomElement e_parking;
	bool isCarrier = false;
	KFFCarrierData carrier;
	QString name;

	if ( doc.setContent( file ) )
	{
		root = doc.documentElement();
		parent = root.firstChild().firstChild();

		while ( !parent.isNull() )
		{
			isCarrier = false;
			e_parent = parent.toElement();

			if ( !e_parent.isNull() )
			{
				if ( e_parent.tagName() == "entry" )
				{
					child = parent.firstChild();

					while ( !child.isNull() )
					{
						e_child = child.toElement();

						if ( !e_child.isNull() )
						{
							if ( e_child.tagName() == "type" )
							{
								if ( e_child.text() == "carrier" )
								{
									isCarrier = true;
									carrier.filename = file->fileName();
									scenariiList << file->fileName();
								}
							}

							if ( e_child.tagName() == "name" )
							{
								if ( isCarrier )
								{
									name = e_child.text();
									carrier.name = e_child.text();
								}
							}

							if ( e_child.tagName() == "model" )
							{
								if ( isCarrier )
								{
									carrier.model = e_child.text();
								}
							}

							if ( e_child.tagName() == "parking-pos" )
							{
								if ( isCarrier )
								{
									parking = child.firstChild();

									while ( !parking.isNull() )
									{
										e_parking = parking.toElement();

										if ( !e_parking.isNull() )
										{
											if ( e_parking.tagName() == "name" )
											{
												carrier.place << e_parking.text();
											}
										}

										parking = parking.nextSibling();
									}
								}
							}

						}

						child = child.nextSibling();
					}
				}
			}

			if (( !name.isEmpty() ) && (!m_carriers.contains(name)))
			{
				m_carriers[name] = carrier;
			}

			parent = parent.nextSibling();
		}
	}
	else
	{
		qDebug() << file->fileName() << "is not a valide xml file" ;
	}
}

KFFCarrierData::KFFCarrierData()
{
}

KFFCarrierData::~KFFCarrierData()
{
}


void KFFCarrierData::clear()
{
	name.clear();
	model.clear();
	place.clear();
}

