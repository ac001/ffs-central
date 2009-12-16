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
 *     (___)_)   File : win_metarview.cpp                   ||--|| *         *
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

#include "win_metarview.h"
#include "settings.h"

#include <kmessagebox.h>

KFFWin_metarView::KFFWin_metarView ( QWidget *parent )
		: QWidget ( parent )
{
	QStringList list;
	QStringList::Iterator it;

	ui_widget.setupUi ( this );
	m_progress = 0;
	m_id = 0;

	list = Settings::airport_favorite();
	for ( it = list.begin() ; it != list.end() ; it++ )
	{
		ui_widget.comboBox_favorite->addItem ( it->replace ( ":", " : " ) );
	}

	connect ( ui_widget.comboBox_favorite,

	          SIGNAL ( activated ( const QString & ) ),
	          SLOT ( setFavorite ( const QString & ) )
	        );

	connect ( ui_widget.pushButton_download,
	          SIGNAL ( clicked() ),
	          SLOT ( download() )
	        );

	connect ( &m_ftp,
	          SIGNAL ( dataTransferProgress ( qint64, qint64 ) ),
	          SLOT ( setProgress ( qint64, qint64 ) )
	        );
	connect ( &m_ftp,
	          SIGNAL ( commandStarted ( int ) ),
	          SLOT ( cmdStarted ( int ) )
	        );
	connect ( &m_ftp,
	          SIGNAL ( commandFinished ( int, bool ) ),
	          SLOT ( cmdFinished ( int, bool ) )
	        );
	connect ( &m_ftp,
	          SIGNAL ( done ( bool ) ),
	          SLOT ( display ( bool ) )
	        );
}


KFFWin_metarView::~KFFWin_metarView()
{
}

void KFFWin_metarView::setAirport ( QString airport )
{
	ui_widget.lineEdit_AirportID->setText ( airport );
}

void KFFWin_metarView::setFavorite ( const QString & favorite )
{
	ui_widget.lineEdit_AirportID->setText ( favorite.section ( " : ", 0, 0 ) );
}

void KFFWin_metarView::download()
{
	QString buffer = i18n ( "the METAR file already exists\nTry to download an up-to-date METAR ?" );
	QString icao;
	if ( !m_progress )
	{
		m_progress = new KProgressDialog ( this,
		                                   i18n ( "Weather informations" ),
		                                   i18n ( "Download real weather" )
		                                 );

		connect ( m_progress,
		          SIGNAL ( cancelClicked() ),
		          &m_ftp,
		          SLOT ( abort() )
		        );
	}

	m_progress->setAttribute ( Qt::WA_DeleteOnClose );

	m_progress->setAutoClose ( false );
	m_progress->setAutoReset ( false );
	m_progress->setAllowCancel ( true );
	m_progress->show();

	icao = ui_widget.lineEdit_AirportID->text().toUpper();
	m_file.setFileName ( "/tmp/" + icao + ".txt" );
	if ( m_file.open ( QFile::ReadOnly ) )
	{
		//return;
		m_file.close();
		switch ( KMessageBox::questionYesNo ( this, buffer ) )
		{
			case KMessageBox::Yes:
			{
				break;
			}
			case KMessageBox::No:
			{
				display ( false );
				return;
			}
		}
	}
	else
	{
		qDebug() << "Cannot open file in read mode : " << m_file.fileName();
	}

	if ( !m_file.open ( QFile::WriteOnly ) )
	{
		qDebug() << "Cannot open file in write mode : " << m_file.fileName();
		return;
	}

	m_ftp.connectToHost ( Settings::metar_website() );
	m_ftp.login();
	m_ftp.cd ( Settings::metar_website_dir() );
	m_ftp.get ( icao + Settings::metar_website_extension(), &m_file );
	m_ftp.close();
}

void KFFWin_metarView::cmdStarted ( int cmdID )
{
	QString text;

	switch ( cmdID - m_id )
	{

		case 1:
		{
			text = i18n ( "Connection" );
			m_currentID = 1;
			break;
		}

		case 2:
		{
			text = i18n ( "Login" );
			m_currentID = 2;
			break;
		}

		case 3:
		{
			text = i18n ( "Change directory" );
			m_currentID = 3;
			break;
		}

		case 4:
		{
			text = i18n ( "Download" );
			m_currentID = 4;
			break;
		}

		case 5:
		{
			text = i18n ( "Close" );
			m_currentID = 5;
			break;
		}
		default:
		{
			text.setNum ( cmdID );
			text.prepend ( "id of ftp command : " );
			m_currentID++;
			break;
		}
	}

	if ( m_progress )
	{
		m_progress->setLabelText ( text );
	}
	qDebug() << text;
}

void KFFWin_metarView::cmdFinished ( int cmdID, bool error )
{
	if ( error )
	{
		qDebug() << "FTP error on ID " << cmdID;
		m_ftp.clearPendingCommands();
		m_ftp.abort();
		m_ftp.close();
	}
}

void KFFWin_metarView::setProgress ( qint64 step, qint64 totalStep )
{
	if ( m_progress )
	{
		if ( totalStep != m_progress->progressBar()->maximum() )
		{
			m_progress->progressBar()->setRange ( 0, totalStep );
		}
		m_progress->progressBar()->setValue ( step );
	}
	qDebug() << "total step = " << totalStep << ", step=" << step;
}

void KFFWin_metarView::display ( bool error_encoured )
{
	QFile file;
	QTextStream stream;
	QString buffer;
	QStringList list;
	QStringList::Iterator it;

	m_progress->hide();

	m_id += m_currentID;
	m_file.close();

	ui_widget.lineEdit_Temperature->clear();
	ui_widget.lineEdit_TemperatureMin->clear();
	ui_widget.lineEdit_Presure->clear();
	ui_widget.lineEdit_Visibility->clear();
	ui_widget.textEdit_PO->clear();
	ui_widget.lineEdit_WindSpeedMax->clear();
	ui_widget.lineEdit_WindDirection->clear();
	ui_widget.lineEdit_WindSpeed->clear();
	ui_widget.lineEdit_WindDirectionVariable->clear();
	ui_widget.lineEdit_Date->clear();
	ui_widget.lineEdit_Time->clear();
	ui_widget.lineEdit_Airport->clear();
	ui_widget.lineEdit_CloudAltitude1->clear();
	ui_widget.lineEdit_CloudAltitude2->clear();
	ui_widget.lineEdit_CloudAltitude3->clear();
	ui_widget.lineEdit_CloudsString1->clear();
	ui_widget.lineEdit_CloudsString2->clear();
	ui_widget.lineEdit_CloudsString3->clear();
	ui_widget.textEdit_METAR->clear();
	m_metar.clear();

	if ( error_encoured )
	{
		qDebug() << "RETURN after error";
		return;
	}

	if ( !m_file.open ( QFile::ReadOnly ) )
	{
		qDebug() << "metar file can not be opened";
		return;
	}

	stream.setDevice ( &m_file );

	while ( !stream.atEnd() )
	{
		buffer.append ( stream.readLine() + "\n" );
	}
	m_file.close();
	m_metar.setMetar ( buffer );
	ui_widget.textEdit_METAR->insertPlainText ( buffer );
	ui_widget.lineEdit_Airport->setText ( m_metar.getID() );
	ui_widget.lineEdit_Date->setText ( m_metar.getDate().toString ( "yyyy/MM/dd" ) );
	ui_widget.lineEdit_Time->setText ( m_metar.getTime().toString ( "hh:mm" ) );
	ui_widget.lineEdit_WindDirection->setText ( m_metar.getWindDirection() );
	ui_widget.lineEdit_WindSpeed->setText ( m_metar.getWindSpeed() );
	ui_widget.lineEdit_WindDirectionVariable->setText ( m_metar.getWindDirGrp() );
	ui_widget.lineEdit_WindSpeedMax->setText ( m_metar.getWindSpeedMax() );
	ui_widget.lineEdit_Presure->setText ( m_metar.getPresure() );
	ui_widget.lineEdit_Temperature->setText ( m_metar.getTemperature() );
	ui_widget.lineEdit_TemperatureMin->setText ( m_metar.getDewpoint() );
	ui_widget.lineEdit_Humidity->setText ( m_metar.getHumidity() );
	ui_widget.textEdit_PO->clear();
	list = m_metar.getPhenomenaStr();
	for ( it = list.begin() ; it != list.end() ; ++it )
	{
		ui_widget.textEdit_PO->append ( *it );
	}
	ui_widget.lineEdit_Visibility->setText ( m_metar.getVisibility() );
	ui_widget.lineEdit_verticalvisibility->setText ( m_metar.getVerticalVisibility() );
	ui_widget.lineEdit_CloudAltitude1->setText ( m_metar.getCloudsAltitude ( 0 ) );
	ui_widget.lineEdit_CloudAltitude2->setText ( m_metar.getCloudsAltitude ( 1 ) );
	ui_widget.lineEdit_CloudAltitude3->setText ( m_metar.getCloudsAltitude ( 2 ) );
	ui_widget.lineEdit_CloudsString1->setText ( m_metar.getCloudsStr ( 0 ) );
	ui_widget.lineEdit_CloudsString2->setText ( m_metar.getCloudsStr ( 1 ) );
	ui_widget.lineEdit_CloudsString3->setText ( m_metar.getCloudsStr ( 2 ) );
}
