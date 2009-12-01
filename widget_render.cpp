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

#include "widget_render.h"
#include "settings.h"
#include "config.h"

#ifdef WITH_OPENSCENEGRAPH_ENABLED
	#include <osgViewer/ViewerEventHandlers>
	#include <osgGA/TrackballManipulator>
	#include <osgGA/FlightManipulator>
	#include <osgGA/DriveManipulator>
	#include <osgGA/KeySwitchMatrixManipulator>
	#include <osgGA/StateSetManipulator>
	#include <osgGA/AnimationPathManipulator>
	#include <osgGA/TerrainManipulator>
	#include <osgDB/ReadFile>
	#include <osgUtil/Optimizer>
	#include <osg/Node>
	#include <osg/Geometry>
	#include <osg/Geode>
	#include <osg/Notify>
	#include <osg/MatrixTransform>
	#include <osg/Texture2D>
	#include <osg/BlendFunc>
	#include <osg/Stencil>
	#include <osg/ColorMask>
	#include <osg/Depth>
	#include <osg/ClipNode>
	#include <osg/AnimationPath>
	
	//#include <simgear/misc/sg_path.hxx>
	#include <simgear/props/props.hxx>
	#include <simgear/debug/logstream.hxx>
	#include <simgear/scene/model/modellib.hxx>
#else
	#include <klocale.h>
#endif

#include <QDebug>

#ifdef WITH_OPENSCENEGRAPH_ENABLED
KFFWidget_Render::KFFWidget_Render( QWidget *parent )
	: ViewerQT( parent )
{
}
#else
KFFWidget_Render::KFFWidget_Render( QWidget *parent )
	: QLabel( parent )
{
	setAlignment( Qt::AlignCenter );
}
#endif

KFFWidget_Render::~KFFWidget_Render()
{
#ifdef WITH_OPENSCENEGRAPH_ENABLED
	_refreshtimer.stop();
#endif
}

void KFFWidget_Render::setSize( int width, int height )
{
	qDebug() << "render width : " << width;
	qDebug() << "render height : " << height;
	setGeometry( 0, 0, width, height );
}

void KFFWidget_Render::initWidget()
{
#ifdef WITH_OPENSCENEGRAPH_ENABLED
	changeSettings();
	setCameraManipulator( new osgGA::TrackballManipulator );

	// set up the camera manipulators.
	osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> manipulator = new osgGA::KeySwitchMatrixManipulator;

	manipulator->addMatrixManipulator( '1', "Trackball", new osgGA::TrackballManipulator() );
	manipulator->addMatrixManipulator( '2', "Flight", new osgGA::FlightManipulator() );
	manipulator->addMatrixManipulator( '3', "Drive", new osgGA::DriveManipulator() );
	manipulator->addMatrixManipulator( '4', "Terrain", new osgGA::TerrainManipulator() );

	setCameraManipulator( manipulator.get() );

	// add the state manipulator
	addEventHandler( new osgGA::StateSetManipulator( getCamera()->getOrCreateStateSet() ) );
    // add the thread model handler
	addEventHandler( new osgViewer::ThreadingHandler );
    // add the window size toggle handler
	addEventHandler(new osgViewer::WindowSizeHandler);
    // add the stats handler
	addEventHandler(new osgViewer::StatsHandler);
#else
	show();
#endif
}

bool KFFWidget_Render::loadModel( QString name )
{
	qDebug() << "load model : " << name;
#ifdef WITH_OPENSCENEGRAPH_ENABLED
	QString buffer;
	/*logbuf log;
	SGPropertyNode propNode;*/
	osg::ref_ptr<osg::Node> loadedModel;
	
	/*
	buffer = Settings::fg_root();
	buffer.append( "/AI/Aircraft/737/737-AirAlaska.xml" );

	loadedModel = simgear::SGModelLib::loadModel(buffer.toStdString(), &propNode);
	*/
	buffer = Settings::data_dir() + "/spaceship.osg";
	qDebug() << "Load model : " << buffer;
	loadedModel = osgDB::readNodeFile( buffer.toStdString() );
	if ( !loadedModel )
	{
		qDebug() << name << " : No data loaded.";
		return false;
	}

    // optimize the scene graph, remove redundant nodes and state etc.
	osgUtil::Optimizer optimizer;
	optimizer.optimize(loadedModel.get());

    // add a transform with a callback to animate the loaded model.
	osg::ref_ptr<osg::MatrixTransform> loadedModelTransform = new osg::MatrixTransform;
	loadedModelTransform->addChild(loadedModel.get());

	osg::ref_ptr<osg::NodeCallback> nc = new osg::AnimationPathCallback(loadedModelTransform->getBound().center(),osg::Vec3(0.0f,0.0f,1.0f),osg::inDegrees(45.0f));
	loadedModelTransform->setUpdateCallback(nc.get());

    // set the scene to render
	setSceneData(loadedModelTransform.get());

	show();
    // hint to tell viewer to request stencil buffer when setting up windows
	//osg::DisplaySettings::instance()->setMinimumNumStencilBits(8);

	return true;
#else
	QPixmap pixmap;
	
	if ( !pixmap.load ( name ) )
	{
		setText( i18n( "No image available" ) );
		return false;
	}
	setPixmap( pixmap );

	return true;
#endif
}

void KFFWidget_Render::changeSettings()
{
#ifdef WITH_OPENSCENEGRAPH_ENABLED
	double r = 0.0, g = 0.0, b = 0.0;

	r = ( Settings::render_color().red() / 255.0 );
	g = ( Settings::render_color().green() / 255.0 );
	b = ( Settings::render_color().blue() / 255.0 );

	getCamera()->setClearColor( osg::Vec4( r, g, b, 1.0 ) );
#endif
}

/******************************************************************************/

#ifdef WITH_OPENSCENEGRAPH_ENABLED

AdapterWidget::AdapterWidget( QWidget * parent, const char * name, const QGLWidget * shareWidget, WindowFlags f ):
		QGLWidget( parent, shareWidget, f )
{
	_gw = new osgViewer::GraphicsWindowEmbedded( 0, 0, width(), height() );
	setFocusPolicy( Qt::ClickFocus );
}

void AdapterWidget::resizeGL( int width, int height )
{
	qDebug() << "resizeGL";
	_gw->getEventQueue()->windowResize( 0, 0, width, height );
	_gw->resized( 0, 0, width, height );
}

void AdapterWidget::keyPressEvent( QKeyEvent* event )
{
	qDebug() << "keyPressEvent";
	_gw->getEventQueue()->keyPress(( osgGA::GUIEventAdapter::KeySymbol ) *( event->text().toAscii().data() ) );
}

void AdapterWidget::keyReleaseEvent( QKeyEvent* event )
{
	qDebug() << "keyReleaseEvent";
	_gw->getEventQueue()->keyRelease(( osgGA::GUIEventAdapter::KeySymbol ) *( event->text().toAscii().data() ) );
}

void AdapterWidget::mousePressEvent( QMouseEvent* event )
{
	int button = 0;

	qDebug() << "mousePressEvent";

	switch ( event->button() )
	{
		case( Qt::LeftButton ): button = 1;
			break;
		case( Qt::MidButton ): button = 2;
			break;
		case( Qt::RightButton ): button = 3;
			break;
		case( Qt::NoButton ): button = 0;
			break;

		default:
			button = 0;
			break;
	}

	_gw->getEventQueue()->mouseButtonPress( event->x(), event->y(), button );
}

void AdapterWidget::mouseReleaseEvent( QMouseEvent* event )
{
	int button = 0;

	qDebug() << "mouseReleaseEvent";

	switch ( event->button() )
	{
		case( Qt::LeftButton ): button = 1;
			break;
		case( Qt::MidButton ): button = 2;
			break;
		case( Qt::RightButton ): button = 3;
			break;
		case( Qt::NoButton ): button = 0;
			break;

		default:
			button = 0;
			break;
	}

	_gw->getEventQueue()->mouseButtonRelease( event->x(), event->y(), button );
}

void AdapterWidget::mouseMoveEvent( QMouseEvent* event )
{
	qDebug() << "mouseMoveEvent";
	_gw->getEventQueue()->mouseMotion( event->x(), event->y() );
}

void AdapterWidget::wheelEvent( QWheelEvent *event )
{
	qDebug() << "wheelEvent";
	_gw->getEventQueue()->mouseScroll(( event->delta() > 0 ) ?
	                                  osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN );
}

osgViewer::GraphicsWindow* AdapterWidget::getGraphicsWindow()
{
	return _gw.get();
}

const osgViewer::GraphicsWindow* AdapterWidget::getGraphicsWindow() const
{
	return _gw.get();
}

void AdapterWidget::resizeEvent( QResizeEvent * event )
{
	const QSize & size = event->size();

	qDebug() << "QOSGWidget::resizeEvent on " << qPrintable( objectName() )
	<< " - width is " << size.width()
	<< "; height is " << size.height();

	_gw->getEventQueue()->windowResize( 0, 0, size.width(), size.height() );
	_gw->resized( 0, 0, size.width(), size.height() );
}

/******************************************************************************/

ViewerQT::ViewerQT( QWidget * parent, const char * name, const QGLWidget * shareWidget, WindowFlags f ):
		AdapterWidget( parent, name, shareWidget, f )
{
	getCamera()->setViewport( new osg::Viewport( 0, 0, width(), height() ) );
	getCamera()->setProjectionMatrixAsPerspective( 30.0f, static_cast<double>( width() ) / static_cast<double>( height() ), 1.0f, 10000.0f );
	getCamera()->setGraphicsContext( getGraphicsWindow() );

	setThreadingModel( osgViewer::Viewer::SingleThreaded );

	connect( &_refreshtimer, SIGNAL( timeout() ), this, SLOT( updateGL() ) );
	_refreshtimer.start( 10 );
}

void ViewerQT::paintGL()
{
	frame();
}
#endif
