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

#ifndef WIDGET_RENDER_H
#define WIDGET_RENDER_H
#include "config.h"

#include <QWidget>
#include <QLabel>

#ifdef WITH_OPENSCENEGRAPH_ENABLED
	#include <osgViewer/Viewer>
	#include <QtCore/QString>
	#include <QtCore/QTimer>
	#include <QtGui/QKeyEvent>
	#include <QtOpenGL/QGLWidget>
	using Qt::WindowFlags;
#endif

#include <iostream>


class AdapterWidget;
class ViewerQT;

/**
 * @author
 */

#ifdef WITH_OPENSCENEGRAPH_ENABLED
class AdapterWidget : public QGLWidget
{

public:

	AdapterWidget( QWidget * parent = 0, const char * name = 0, const QGLWidget * shareWidget = 0, WindowFlags f = 0 );

	virtual ~AdapterWidget() {}

	osgViewer::GraphicsWindow* getGraphicsWindow();
	const osgViewer::GraphicsWindow* getGraphicsWindow() const;

protected:

	void init();

	virtual void resizeGL( int width, int height );
	virtual void keyPressEvent( QKeyEvent* event );
	virtual void keyReleaseEvent( QKeyEvent* event );
	virtual void mousePressEvent( QMouseEvent* event );
	virtual void mouseReleaseEvent( QMouseEvent* event );
	virtual void mouseMoveEvent( QMouseEvent* event );
	virtual void wheelEvent( QWheelEvent *event );
	virtual void resizeEvent( QResizeEvent * event );
	osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _gw;
};

class ViewerQT : public osgViewer::Viewer, public AdapterWidget
{

public:

	ViewerQT( QWidget * parent = 0, const char * name = 0, const QGLWidget * shareWidget = 0, WindowFlags f = 0 );

	virtual ~ViewerQT() {}
	
	virtual void paintGL();

protected:

	QTimer _refreshtimer;
};

class KFFWidget_Render : public ViewerQT
{
	Q_OBJECT

public:
	KFFWidget_Render( QWidget *parent = 0 );
	~KFFWidget_Render();

	void initWidget();
	void setSize( int width, int height );
	
public slots:
	virtual bool loadModel( const QString & name );
	virtual void changeSettings();

};
#else
class KFFWidget_Render : public QLabel
{
	Q_OBJECT

	public:
		KFFWidget_Render( QWidget *parent = 0 );

		~KFFWidget_Render();

		void initWidget();
		void setSize( int width, int height );
	
	public slots:
		virtual bool loadModel( const QString & name );
		virtual void changeSettings();

private:
};
#endif // WITH_OPENSCENEGRAPH_ENABLED

#endif // WIDGET_RENDER_H
