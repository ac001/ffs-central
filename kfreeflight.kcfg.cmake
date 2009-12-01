<?xml version="1.0" encoding="UTF-8"?>
<kcfg xmlns="http://www.kde.org/standards/kcfg/1.0"
      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
      xsi:schemaLocation="http://www.kde.org/standards/kcfg/1.0
      http://www.kde.org/standards/kcfg/1.0/kcfg.xsd" >
      <kcfgfile name="kfreeflightrc"/>
  <group name="KFreeFlight">
    <entry name="app_talkative" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="fgfs_messages" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="r3D_rendering" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="systray" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="minimized" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="render_color" type="Color">
	    <default>2,31,93</default>
    </entry>
    <entry name="data_dir" type="String">
    </entry>
    <entry name="marble_theme" type="Int">
	    <default>0</default>
    </entry>
    <entry name="metar_website" type="String">
	    <default>tgftp.nws.noaa.gov</default>
    </entry>
    <entry name="metar_website_dir" type="String">
	    <default>data/observations/metar/stations</default>
    </entry>
    <entry name="metar_website_extension" type="String">
	    <default>.TXT</default>
    </entry>
  </group>
  <group name="FlightGear">
    <entry name="fg_root" type="String">
	    <default>@WITH_FG_ROOT@</default>
    </entry>
    <entry name="fg_addon_sceneries" type="StringList">
	    <default>@WITH_FG_SCENERY@</default>
    </entry>
    <entry name="fg_exe" type="StringList">
	    <default>fgfs</default>
    </entry>
    <entry name="http_host" type="String">
	    <default>localhost</default>
    </entry>
    <entry name="http_port" type="UInt">
	    <default>5500</default>
    </entry>
    <entry name="resolution_x" type="UInt">
	    <default>1600</default>
    </entry>
    <entry name="resolution_y" type="UInt">
	    <default>1200</default>
    </entry>
    <entry name="fg_singleton" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="terrasync_dir" type="String">
	    <default>/tmp</default>
    </entry>
    <entry name="terra_nice_enabled" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="terra_nice" type="Int">
	    <default>0</default>
    </entry>
    <entry name="terra_close" type="Bool">
	    <default>true</default>
    </entry>
  </group>
  <group name="Atlas">
    <entry name="atlas_exe" type="String">
	    <default>Atlas</default>
    </entry>
    <entry name="img_dir" type="String">
	    <default>/tmp</default>
    </entry>
    <entry name="glut_font" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="atlas_singleton" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="atlas_nice_enabled" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="atlas_nice" type="Int">
	    <default>0</default>
    </entry>
    <entry name="atlas_close" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="atlas_version" type="Bool">
	    <default>false</default>
    </entry>
  </group>
  <group name="Common">
    <entry name="common_splashscreen" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="common_gameMode" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="common_fullscreen" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="common_introMusic" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="common_sound" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="common_joystick" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="common_autoCoordon" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="common_unitMeter" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="common_NMEA" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="common_AtlasToo" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="common_serverHttp" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="common_terrasync" type="Bool">
	    <default>false</default>
    </entry>
  </group>
  <group name="Rendering">
    <entry name="renderingResolution" type="Int">
	    <default>0</default>
    </entry>
    <entry name="renderingResolutionBpp" type="Int">
	    <default>3</default>
    </entry>
    <entry name="renderingShading" type="Int">
	    <default>1</default>
    </entry>
    <entry name="renderingFog" type="Int">
	    <default>2</default>
    </entry>
    <entry name="renderingDistanceAttenuation" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="renderingSpecularHighlight" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="renderingEnhancedLighting" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="renderingClouds" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="renderingClouds3d" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="renderingRandomObjects" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="renderingWireframeObjects" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="renderingMousePointer" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="renderingSkyBlend" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="renderingHorizonEffect" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="renderingTextures" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="renderingLightning" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="renderingPrecipitation" type="Bool">
	    <default>true</default>
    </entry>
    <entry name="renderingAiTraffic" type="Bool">
	    <default>true</default>
    </entry>
  </group>
  <group name="Airport">
    <entry name="airport_favorite" type="StringList">
    </entry>
    <entry name="airport_id" type="String">
    </entry>
    <entry name="airport_runway" type="String">
    </entry>
  </group>
  <group name="Carrier">
    <entry name="carrier_selected" type="Int">
    </entry>
    <entry name="carrier_place" type="Int">
    </entry>
  </group>
  <group name="Aircraft">
    <entry name="aircraft_selected" type="Int">
    </entry>
    <entry name="aircraftFailure_Pitot" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="aircraftFailure_Static" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="aircraftFailure_System" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="aircraftFailure_Vacuum" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="aircraftFuelFreeze" type="Bool">
	    <default>false</default>
    </entry>
    <entry name="aircraftFreeze" type="Bool">
	    <default>false</default>
    </entry>
  </group>
  <group name="Position">
    <entry name="position_selected" type="Int">
    </entry>
    <entry name="position_altitude" type="Int">
    </entry>
    <entry name="position_speed" type="Int">
    </entry>
    <entry name="position_heading" type="Int">
    </entry>
    <entry name="position_longitude" type="Double">
    </entry>
    <entry name="position_latitude" type="Double">
    </entry>
  </group>
  <group name="scenarii">
    <entry name="scenarii_selected" type="StringList">
    </entry>
  </group>
  <group name="property">
    <entry name="property_available" type="StringList">
	    <default>controls/gear/brake-parking=1,sim/presets/fuel=1</default>
    </entry>
    <entry name="property_selected" type="StringList">
    </entry>
  </group>
  <group name="personnal">
    <entry name="personnal_available" type="StringList">
    </entry>
    <entry name="personnal_selected" type="StringList">
    </entry>
  </group>
  <group name="datetime">
    <entry name="datetime_selected" type="Int">
    </entry>
    <entry name="datetime_timeofday" type="Int">
    </entry>
    <entry name="datetime_season" type="Int">
    </entry>
  </group>
  <group name="network">
    <entry name="network_myip" type="String">
	    <default>192.168.0.1</default>
    </entry>
    <entry name="network_callsign" type="String">
	    <default>kfreeflight</default>
    </entry>
    <entry name="network_server" type="StringList">
	    <default>mpserver01.flightgear.org</default>
    </entry>
    <entry name="network_port" type="UInt">
	    <default>5500</default>
    </entry>
    <entry name="network_refresh" type="UInt">
	    <default>10</default>
    </entry>
    <entry name="network_selected" type="Int">
    </entry>
  </group>
  <group name="radio">
    <entry name="radio_nav1" type="Double">
    </entry>
    <entry name="radio_nav1standby" type="Double">
    </entry>
    <entry name="radio_nav1radial" type="Int">
    </entry>
    <entry name="radio_nav2" type="Double">
    </entry>
    <entry name="radio_nav2standby" type="Double">
    </entry>
    <entry name="radio_nav2radial" type="Int">
    </entry>
    <entry name="radio_adf" type="Int">
    </entry>
    <entry name="radio_adfstandby" type="Int">
    </entry>
    <entry name="radio_adfrotation" type="Int">
    </entry>
    <entry name="radio_selected_dme" type="Int">
    </entry>
    <entry name="radio_dme" type="Double">
    </entry>
    <entry name="radio_tacan1" type="Int">
    </entry>
    <entry name="radio_tacan2" type="Int">
    </entry>
    <entry name="radio_tacan3" type="Int">
    </entry>
    <entry name="radio_tacanletter" type="Int">
    </entry>
    <entry name="radio_com1" type="Double">
    </entry>
    <entry name="radio_com1standby" type="Double">
    </entry>
    <entry name="radio_com2" type="Double">
    </entry>
    <entry name="radio_com2standby" type="Double">
    </entry>
    <entry name="radio_festival" type="Bool">
    </entry>
    <entry name="radio_voices" type="Bool">
    </entry>
  </group>
  <group name="flightplan">
    <entry name="flightplan_selected" type="Int">
    </entry>
    <entry name="flightplan_list" type="StringList">
    </entry>
  </group>
  <group name="weather">
    <entry name="weather_wind_speed" type="Int">
    	<default>0</default>
    </entry>
    <entry name="weather_wind_direction" type="Int">
    	<default>0</default>
    </entry>
    <entry name="weather_wind_random" type="Bool">
    	<default>false</default>
    </entry>
    <entry name="weather_visibility" type="Int">
    	<default>0</default>
    </entry>
    <entry name="weather_turbulences" type="Int">
    	<default>0</default>
    </entry>
    <entry name="weather_clouds" type="StringList">
    </entry>
    <entry name="weather_selected" type="Int">
    </entry>
  </group>
</kcfg>
