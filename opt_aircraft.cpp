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

#include "opt_aircraft.h"
#include "settings.h"
#include "win_messages.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomElement>
#include <QDir>
#include <QStringList>

#include <QMessageBox>
#include <kfiledialog.h>

KFFOpt_aircraft::KFFOpt_aircraft( QWidget *parent )
		: KFFOpt_skeleton( parent )
{
	//QString img = Settings::data_dir() + "/aircraft1.svg"; nuked pete@ffs

	ui_widget.setupUi( this );
	//ui_widget.widgetLogo->load( img );

	m_process = 0;
	/* nuked pete@ffs
	m_render = new KFFWidget_Render( ui_widget.widget_scene );
	m_render->initWidget();
	m_render->setSize( ui_widget.widget_scene->width(),
	                   ui_widget.widget_scene->height()
	                 );
	*/
	m_url = KUrl::fromPath ( Settings::fg_root() );
	
	connect( ui_widget.btn_Reload,
	         SIGNAL( clicked() ),
	         SLOT( reload() )
	       );
	/*
	connect( ui_widget.combo_Aircraft,
	         SIGNAL( activated( QString ) ),
	         SLOT( setAircraft( QString ) )
	       ); 
	*/
	
	
	//** Setup Main Model
	model_Aircraft = new QStandardItemModel(this);
	model_Aircraft->setColumnCount(2);
	QStringList headerLabelsList;
	headerLabelsList << "Aircraft" << "Description";
	model_Aircraft->setHorizontalHeaderLabels(headerLabelsList);
	
	//** Setup Proxy filter model
	pmodel_Aircraft = new QSortFilterProxyModel(this);
	pmodel_Aircraft->setSourceModel(model_Aircraft);
	
	//** Setup Tree view + events
	ui_widget.tree_Aircraft->setAlternatingRowColors(true);
	ui_widget.tree_Aircraft->setModel(pmodel_Aircraft);
	connect( ui_widget.tree_Aircraft->selectionModel(),
	         SIGNAL( selectionChanged (const QItemSelection&, const QItemSelection&) ),
	         SLOT( setAircraft() )
	       );
		   
	//** Connect txt_Filter to filter proxy
	connect( ui_widget.txt_Filter,
			 SIGNAL( textChanged (const QString&) ),
			 SLOT ( on_txt_filter(const QString&) )
		   );
		   
	//* other events
	connect( ui_widget.btn_LoadModel,
	         SIGNAL( clicked() ),
	         SLOT( loadModel() )
	       );
	/* connect( this,
	         SIGNAL( settingsChanged() ),
	         m_render,
	         SLOT( changeSettings() )
	       );
	*/
}

KFFOpt_aircraft::~KFFOpt_aircraft()
{
	if ( m_process )
	{
		delete m_process;
	}
}

void KFFOpt_aircraft::resizeEvent( QResizeEvent * event )
{
	/* nuked pete@ffs 
	m_render->setSize( ui_widget.widget_scene->width(),
	                   ui_widget.widget_scene->height()
	                 );
	*/
}

void KFFOpt_aircraft::reload()
{
	reloadList( true );
}

void KFFOpt_aircraft::setAircraft()
{
	QString buffer;
	QString *aircraft = new QString("aircraft");
	buffer = Settings::fg_root();
	buffer.append( "/Aircraft/");
	buffer.append( aircraft );
	buffer.append( "/thumbnail.jpg" );
	
	//m_render->loadModel( aircraft.section( " - ", 0, 0 ) );
}

void KFFOpt_aircraft::reloadList( bool showMessage )
{
	getAircraft();

	if ( showMessage )
	{
		QMessageBox::information( this, "TODO-TITLE", i18n( "Reloaded" ) );
	}
}

void KFFOpt_aircraft::saveSettings()
{
	Settings::setAircraftFailure_Pitot( ui_widget.kcfg_aircraftFailure_Pitot->isChecked() );
	Settings::setAircraftFailure_Static( ui_widget.kcfg_aircraftFailure_Static->isChecked() );
	Settings::setAircraftFailure_System( ui_widget.kcfg_aircraftFailure_System->isChecked() );
	Settings::setAircraftFailure_Vacuum( ui_widget.kcfg_aircraftFailure_Vacuum->isChecked() );
	Settings::setAircraftFuelFreeze( ui_widget.kcfg_aircraftFuelFreeze->isChecked() );
	Settings::setAircraftFreeze( ui_widget.kcfg_aircraftFreeze->isChecked() );
	//Settings::setAircraft_selected( ui_widget.combo_Aircraft->currentIndex() ); #TODO
	Settings::self()->writeConfig();
}

void KFFOpt_aircraft::loadSettings()
{
	reloadList( false );
	ui_widget.kcfg_aircraftFailure_Pitot->setChecked( Settings::aircraftFailure_Pitot() );
	ui_widget.kcfg_aircraftFailure_Static->setChecked( Settings::aircraftFailure_Static() );
	ui_widget.kcfg_aircraftFailure_System->setChecked( Settings::aircraftFailure_System() );
	ui_widget.kcfg_aircraftFailure_Vacuum->setChecked( Settings::aircraftFailure_Vacuum() );
	ui_widget.kcfg_aircraftFuelFreeze->setChecked( Settings::aircraftFuelFreeze() );
	ui_widget.kcfg_aircraftFreeze->setChecked( Settings::aircraftFreeze() );
	//setAircraft( ui_widget.combo_Aircraft->currentText() ); #TODO
	emit( settingsChanged() );
}

bool KFFOpt_aircraft::getOptions( QStringList & list )
{
	if ( !ui_widget.tree_Aircraft->selectionModel()->hasSelection() )
	{
		QMessageBox::critical( this, "TODO - was sorry() ?", i18n( "No aircraft selected" ) );
	}
	//return;
	//list << "--aircraft=" + ui_widget.combo_Aircraft->currentText().section( ' ', 0, 0 );

	if ( ui_widget.kcfg_aircraftFreeze->isChecked() )
	{
		list << "--enable-freeze";
	}
	else
	{
		list << "--disable-freeze";
	}

	if ( ui_widget.kcfg_aircraftFuelFreeze->isChecked() )
	{
		list << "--enable-fuel-freeze";
	}
	else
	{
		list << "--disable-fuel-freeze";
	}

	if ( ui_widget.kcfg_aircraftFailure_Pitot->isChecked() )
	{
		list << "--failure=pitot";
	}

	if ( ui_widget.kcfg_aircraftFailure_Static->isChecked() )
	{
		list << "--failure=static";
	}

	if ( ui_widget.kcfg_aircraftFailure_System->isChecked() )
	{
		list << "--failure=electrical";
	}

	if ( ui_widget.kcfg_aircraftFailure_Vacuum->isChecked() )
	{
		list << "--failure=vacuum";
	}

	return true;
}

void KFFOpt_aircraft::loadModel()
{
	QString buffer;
	return; //TODO dead for now - pete@ff
	buffer = KFileDialog::getOpenFileName ( m_url, QString(), this );
	if ( !buffer.isEmpty() )
	{
		//m_render->loadModel( buffer );
	}
	buffer.truncate( buffer.lastIndexOf("/") );
	m_url = KUrl::fromPath ( buffer );
}

void KFFOpt_aircraft::getAircraft()
{
	QStringList dirlist, setfilelist, namefilter;
	QStringList::Iterator it, it2;
	QString dirname, id;
	QDir dir, aircraftdir;
	KFFAircraftData data;

	/*dirname = Settings::fg_root();
	dirname.append( "/Aircraft/" );
	dir.cd( dirname );

	namefilter << "*-set.xml";
	
	dirlist = dir.entryList( QDir::Dirs, QDir::Name );
	for ( it = dirlist.begin() ; it != dirlist.end() ; ++it )
	{
		if ( ( *it == "." ) || ( *it == ".." ) ) continue;
		qDebug() << "KFF ###############" << *it;
		aircraftdir.cd( dirname + "/" + *it );
		setfilelist = aircraftdir.entryList( namefilter, QDir::Files, QDir::Name );
		for ( it2 = setfilelist.begin() ; it2 != setfilelist.end() ; ++it2 )
		{
			qDebug() << "File : " << *it2;
			
			if ( searchData( dirname + "/" + *it + "/" + *it2, data ) )
			{
				qDebug() << "description = " << data.description;
				qDebug() << "model = " << data.model;
				//qDebug() << "texture = " << data.texture;
				id = it2->remove( "-set.xml" );
				qDebug() << "id = " << id;
			}
		}
	}*/
	
	m_input.clear();

	if ( !m_process )
	{
		m_process = new KProcess;
		m_process->setOutputChannelMode( KProcess::SeparateChannels );
		connect( m_process, SIGNAL( readyReadStandardOutput() ), SLOT( readData() ) );
		connect( m_process, SIGNAL( readyReadStandardError() ), SLOT( readError() ) );
		connect( m_process,
		         SIGNAL( finished( int, QProcess::ExitStatus ) ),
		         SLOT( closeProcess( int, QProcess::ExitStatus ) )
		       );
	}

	if ( m_process->state() != QProcess::NotRunning )
	{
		return;
	}

	m_output->insertTitle( "Aircraft process" );

	m_process->clearProgram();

	m_process->setProgram( *Settings::fg_exe().begin() );

	*m_process << "--fg-root=" + Settings::fg_root();
	*m_process << "--show-aircraft";


	m_process->start();

	m_output->insertText( m_process->program().join( " " ) );
}

bool KFFOpt_aircraft::searchData( QString filename, KFFAircraftData & data )
{
	QFile file;

	qDebug() << filename;
	file.setFileName( filename );

	if ( !file.open( QFile::ReadOnly ) )
	{
		return false;
	}
	file.close();
	
	return true;

	
}

void KFFOpt_aircraft::readData()
{
	m_input.append( m_process->readAllStandardOutput() );
}

void KFFOpt_aircraft::readError()
{
	m_error.append( m_process->readAllStandardOutput() );
}

void KFFOpt_aircraft::closeProcess( int code, QProcess::ExitStatus status )
{
	QStringList::Iterator it;
	QStringList list;
	QString buffer, aircraft;
	int i = 0;

	buffer.setNum( code );
	m_output->insertText( "Aircraft process finished with code " + buffer );
	m_error = m_error.simplified();

	if ( !m_error.isEmpty() )
	{
		m_output->insertError( m_error );
	}

	if ( status == QProcess::NormalExit && code == 0 )
	{
		list = m_input.split( '\n' );
		//ui_widget.combo_Aircraft->clear();
		//ui_widget.tree_Aircraft->model()->removeRows(0, 
		int row_count = 0;
		for ( it = list.begin() ; it != list.end() ; it++ )
		{
			buffer = it->simplified();

			if ( it == list.begin() )
			{
				//ui_widget.combo_Aircraft->insertItem( i++, buffer );
				// add widget ?? dont understand when this is called
			}
			else if ( !buffer.isEmpty() )
			{
				//aircraft = buffer.section( ' ', 0, 0 ) + " - " + buffer.section( ' ', 1 );
				//ui_widget.combo_Aircraft->insertItem( i++, aircraft );
				
				model_Aircraft->insertRow(row_count);
				//* Insert new node in tree, col 0 = model, 1 == Descrption?
				QStandardItem *aircraftItem = new QStandardItem();
				//#TODO - set icon + check favourite
				aircraftItem->setText( buffer.section( ' ', 0, 0 ) );
				model_Aircraft->setItem(row_count, 0, aircraftItem);

				QStandardItem *descriptionItem = new QStandardItem();
				descriptionItem->setText( buffer.section( ' ', 1 ) );
				model_Aircraft->setItem(row_count, 1, descriptionItem);
				
				//ui_widget.tree_Aircraft->addTopLevelItem(aItem);
				row_count++;
			}
		}

		//ui_widget.combo_Aircraft->setCurrentIndex( Settings::aircraft_selected() );
	}
	else
	{
		m_input = m_input.simplified();

		if ( !m_input.isEmpty() )
		{
			m_output->insertError( m_input );
		}
	}
}

//* Set filter on grid
void KFFOpt_aircraft::on_txt_filter( const QString& txt)
{
		//QRegExp *reggie = new QRegExp(txt); ## TODO case insensitive eg 74 ing = 747 Boeing === description
		pmodel_Aircraft->setFilterRegExp(txt);
		pmodel_Aircraft->setFilterKeyColumn(1);
}
