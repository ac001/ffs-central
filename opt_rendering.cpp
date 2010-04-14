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

#include "opt_rendering.h"
#include "settings.h"


KFFOpt_rendering::KFFOpt_rendering( QWidget *parent )
		: KFFOpt_skeleton( parent )
{
	//QString img = Settings::data_dir() + "/clouds.svg"; pete@ffs nuked image

	ui_widget.setupUi ( this );
	wSetupHeader(ui_widget.wHeaderLabel);
	//ui_widget.widgetLogo->load ( img ); pete@ffs nuked image
	
	m_shadingGrp = new QButtonGroup( this );
	m_shadingGrp->addButton( ui_widget.RB_Shading_flat, 0 );
	m_shadingGrp->addButton( ui_widget.RB_Shading_smooth, 1 );
	
	m_fogGrp = new QButtonGroup( this );
	m_fogGrp->addButton( ui_widget.RB_Fog_0, 0 );
	m_fogGrp->addButton( ui_widget.RB_Fog_1, 1 );
	m_fogGrp->addButton( ui_widget.RB_Fog_2, 2 );
}


KFFOpt_rendering::~KFFOpt_rendering()
{
}

void KFFOpt_rendering::saveSettings()
{
	Settings::setRenderingResolution( ui_widget.ComboBox_Resolution->currentIndex() );
	Settings::setRenderingResolutionBpp( ui_widget.ComboBox_Resolution_bpp->currentIndex() );
	Settings::setRenderingDistanceAttenuation( ui_widget.CB_DistanceAttenuation->isChecked() );
	Settings::setRenderingSpecularHighlight( ui_widget.CB_SpecularHighlight->isChecked() );
	Settings::setRenderingEnhancedLighting( ui_widget.CB_EnhancedLighting->isChecked() );
	Settings::setRenderingClouds( ui_widget.CB_Clouds->isChecked() );
	Settings::setRenderingClouds3d( ui_widget.CB_Clouds3d->isChecked() );
	Settings::setRenderingRandomObjects( ui_widget.CB_RandomObjects->isChecked() );
	Settings::setRenderingWireframeObjects( ui_widget.CB_WireframeObjects->isChecked() );
	Settings::setRenderingMousePointer( ui_widget.CB_MousePointer->isChecked() );
	Settings::setRenderingSkyBlend( ui_widget.CB_SkyBlend->isChecked() );
	Settings::setRenderingHorizonEffect( ui_widget.CB_HorizonEffect->isChecked() );
	Settings::setRenderingTextures( ui_widget.CB_Textures->isChecked() );
	Settings::setRenderingLightning( ui_widget.CB_Lightning->isChecked() );
	Settings::setRenderingPrecipitation( ui_widget.CB_Precipitation->isChecked() );
	Settings::setRenderingAiTraffic( ui_widget.CB_AiTraffic->isChecked() );
	Settings::setRenderingShading( m_shadingGrp->checkedId() );
	Settings::setRenderingFog( m_fogGrp->checkedId() );
	Settings::self()->writeConfig();
}

void KFFOpt_rendering::loadSettings()
{
	QString buffer, buffer2;

	buffer.setNum(Settings::resolution_x());
	buffer2.setNum(Settings::resolution_y());
	buffer2.prepend(buffer + "x");
	
	ui_widget.ComboBox_Resolution->removeItem(ui_widget.ComboBox_Resolution->count() - 1);
	ui_widget.ComboBox_Resolution->addItem(buffer2);
	ui_widget.ComboBox_Resolution->setCurrentIndex( Settings::renderingResolution() );
	ui_widget.ComboBox_Resolution_bpp->setCurrentIndex( Settings::renderingResolutionBpp() );	
	m_fogGrp->button( Settings::renderingFog() )->setChecked( true );
	m_shadingGrp->button( Settings::renderingShading() )->setChecked( true );	
	ui_widget.CB_DistanceAttenuation->setChecked( Settings::renderingDistanceAttenuation() );
	ui_widget.CB_SpecularHighlight->setChecked( Settings::renderingSpecularHighlight() );
	ui_widget.CB_EnhancedLighting->setChecked( Settings::renderingEnhancedLighting() );
	ui_widget.CB_Clouds->setChecked( Settings::renderingClouds() );
	ui_widget.CB_Clouds3d->setChecked( Settings::renderingClouds3d() );
	ui_widget.CB_RandomObjects->setChecked( Settings::renderingRandomObjects() );
	ui_widget.CB_WireframeObjects->setChecked( Settings::renderingWireframeObjects() );
	ui_widget.CB_MousePointer->setChecked( Settings::renderingMousePointer() );
	ui_widget.CB_SkyBlend->setChecked( Settings::renderingSkyBlend() );
	ui_widget.CB_HorizonEffect->setChecked( Settings::renderingHorizonEffect() );
	ui_widget.CB_Textures->setChecked( Settings::renderingTextures() );
	ui_widget.CB_Lightning->setChecked( Settings::renderingLightning() );
	ui_widget.CB_Precipitation->setChecked( Settings::renderingPrecipitation() );
	ui_widget.CB_AiTraffic->setChecked( Settings::renderingAiTraffic() );
}

bool KFFOpt_rendering::getOptions(QStringList & list)
{
	if ( ui_widget.CB_RandomObjects->isChecked() )
	{
		list << "--enable-random-objects";
	}
	else
	{
		list << "--disable-random-objects";
	}

	if ( ui_widget.CB_SkyBlend->isChecked() )
	{
		list << "--enable-skyblend";
	}
	else
	{
		list << "--disable-skyblend";
	}

	if ( ui_widget.CB_Textures->isChecked() )
	{
		list << "--enable-textures";
	}
	else
	{
		list << "--disable-textures";
	}

	if ( ui_widget.CB_HorizonEffect->isChecked() )
	{
		list << "--enable-horizon-effect";
	}
	else
	{
		list << "--disable-horizon-effect";
	}

	if ( ui_widget.CB_Clouds->isChecked() )
	{
		list << "--enable-clouds";
	}
	else
	{
		list << "--disable-clouds";
	}

	if ( ui_widget.CB_Clouds3d->isChecked() )
	{
		list << "--enable-clouds3d";
	}
	else
	{
		list << "--disable-clouds3d";
	}

	if ( ui_widget.CB_EnhancedLighting->isChecked() )
	{
		list << "--enable-enhanced-lighting";
	}
	else
	{
		list << "--disable-enhanced-lighting";
	}

	if ( ui_widget.CB_MousePointer->isChecked() )
	{
		list << "--enable-mouse-pointer";
	}
	else
	{
		list << "--disable-mouse-pointer";
	}

	if ( ui_widget.CB_DistanceAttenuation->isChecked() )
	{
		list << "--enable-distance-attenuation";
	}
	else
	{
		list << "--disable-distance-attenuation";
	}

	if ( ui_widget.CB_SpecularHighlight->isChecked() )
	{
		list << "--enable-specular-highlight";
	}
	else
	{
		list << "--disable-specular-highlight";
	}

	if ( ui_widget.RB_Shading_flat->isChecked() )
	{
		list << "--shading-flat";
	}

	if ( ui_widget.RB_Shading_smooth->isChecked() )
	{
		list << "--shading-smooth";
	}

	list << "--geometry=" + ui_widget.ComboBox_Resolution->currentText();

	list << "--bpp=" + ui_widget.ComboBox_Resolution_bpp->currentText();

	if ( ui_widget.CB_Lightning->isChecked() )
	{
		list << "--prop:sim/rendering/lightning-enable[0]=true";
	}
	else
	{
		list << "--prop:sim/rendering/lightning-enable[0]=false";
	}

	if ( ui_widget.CB_Precipitation->isChecked() )
	{
		list << "--prop:sim/rendering/precipitation-enable[0]=true";
	}
	else
	{
		list << "--prop:sim/rendering/precipitation-enable[0]=false";
	}

	if ( ui_widget.CB_WireframeObjects->isChecked() )
	{
		list << "--enable-wireframe" ;
	}
	else
	{
		list << "--disable-wireframe" ;
	}

	if ( ui_widget.CB_AiTraffic->isChecked() )
	{
		list << "--enable-ai-models";
		list << "--prop:sim/ai-traffic/enabled[0]=true";
		list << "--prop:sim/ai-traffic/level[0]=2";
	}
	else
	{
		list << "--disable-ai-models";
	}

	return true;
}

