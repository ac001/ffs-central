cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)
project(kfreeflight)
include(version.cmake)
option( WITH_OSG_RENDERING "Activate Aircraft 3D rendering with OpenSceneGraph" ON )

set(CMAKE_INSTALL_PREFIX "/usr/local")

# FG_ROOT
if ( NOT WITH_FG_ROOT )
    if ( DEFINED ENV{FG_ROOT} )
        set ( WITH_FG_ROOT $ENV{FG_ROOT} )
    else ( DEFINED ENV{FG_ROOT} )
        set ( WITH_FG_ROOT "/usr/share/games/flightgear" )
    endif ( DEFINED ENV{FG_ROOT} )
endif ( NOT WITH_FG_ROOT )
set( WITH_FG_ROOT ${WITH_FG_ROOT} CACHE STRING "Set the FG_ROOT path" )

# FG_SCENERY
if ( NOT WITH_FG_SCENERY )
    if ( DEFINED ENV{FG_SCENERY} )
        set ( WITH_FG_SCENERY $ENV{FG_SCENERY} )
    else ( DEFINED ENV{FG_SCENERY} )
        unset ( WITH_FG_SCENERY )
    endif ( DEFINED ENV{FG_SCENERY} )
endif ( NOT WITH_FG_SCENERY )
set( WITH_FG_SCENERY ${WITH_FG_SCENERY} CACHE STRING "Set the FG_SCENERY path, multiple paths can be entered separate by a colon ','" )

message(STATUS "*** Building KFreeFlight ${kfreeflight_VERSION} ***")

find_package(KDE4 REQUIRED)
include (KDE4Defaults)
find_package (Marble REQUIRED)
find_package (MarbleWidget REQUIRED)
find_package(Msgfmt REQUIRED)
find_package(Gettext REQUIRED)
SET(CMAKE_MODULE_PATH "${kfreeflight_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

if ( WITH_OSG_RENDERING )
    set( WITH_OPENSCENEGRAPH_ENABLED TRUE )
    find_package (OpenGL REQUIRED)
    find_package(OpenSceneGraph REQUIRED COMPONENTS osgGA osgDB osgUtil osgViewer osgAnimation)
    find_package (Plib REQUIRED)
    #find_package (Simgear REQUIRED)
    message(STATUS "3D rendering is active")
else( WITH_OSG_RENDERING )
    set(WITH_OPENSCENEGRAPH_ENABLED FALSE)
endif( WITH_OSG_RENDERING )

configure_file(${kfreeflight_SOURCE_DIR}/config.h.cmake
               ${kfreeflight_BINARY_DIR}/config.h)

configure_file(${kfreeflight_SOURCE_DIR}/kfreeflight.kcfg.cmake
               ${kfreeflight_BINARY_DIR}/kfreeflight.kcfg)

set(kfreeflight_SRCS
    kfreeflight.cpp
    kfreeflight.h
    main.cpp
    kfreeflightview.cpp
    kfreeflightview.h
    pref_page1.cpp
    pref_page1.h
    pref_page2.cpp
    pref_page2.h
    pref_page3.cpp
    pref_page3.h
    pref_page4.cpp
    pref_page4.h
    pref_page5.cpp
    pref_page5.h
    opt_skeleton.cpp
    opt_skeleton.h
    opt_airport.cpp
    opt_airport.h
    opt_property.cpp
    opt_property.h
    opt_common.cpp
    opt_common.h
    opt_rendering.cpp
    opt_rendering.h
    opt_weather.cpp
    opt_weather.h
    opt_othersopt.cpp
    opt_othersopt.h
    opt_carrier.cpp
    opt_carrier.h
    opt_aircraft.cpp
    opt_aircraft.h
    opt_position.cpp
    opt_position.h
    opt_datetime.cpp
    opt_datetime.h
    opt_flightplan.cpp
    opt_flightplan.h
    opt_network.cpp
    opt_network.h
    opt_radio.cpp
    opt_radio.h
    opt_scenery.cpp
    opt_scenery.h
    win_messages.cpp
    win_messages.h
    win_airports.cpp
    win_airports.h
    win_calculator.cpp
    win_calculator.h
    win_coordinates.cpp
    win_coordinates.h
    win_metarview.cpp
    win_metarview.h
    win_metarcreate.cpp
    win_metarcreate.h
    win_flightplan.cpp
    win_flightplan.h
    win_worldview.cpp
    win_worldview.h
    win_chooser.cpp
    win_chooser.h
    metar.cpp
    metar.h
    sgcoremag.h
    widget_render.cpp
    widget_render.h
    shared.h
   )

set (LIBRARIES_TO_LINK
     ${MARBLE_LIBRARY}
     ${LIBMARBLEWIDGET_LIBRARY}
     ${KDE4_KDEUI_LIBS}
     ${KDE4_KIO_LIBS}
     ${X11_X11_LIB}
    )

if( WITH_OSG_RENDERING )
    set (LIBRARIES_TO_LINK
         ${LIBRARIES_TO_LINK}
         ${OPENGL_gl_LIBRARY}
         ${OPENGL_glu_LIBRARY}
         ${OPENSCENEGRAPH_LIBRARIES}
         ${QT_QTOPENGL_LIBRARY}
         ${PLIB_LIBRARIES}
         ${SIMGEAR_LIBRARIES}
        )
else()
    unset ( OPENSCENEGRAPH_INCLUDE_DIRS )
    unset ( SIMGEAR_INCLUDE_DIR )
    unset ( PLIB_INCLUDE_DIR )
endif()


include_directories(${kfreeflight_SOURCE_DIR}
                    ${kfreeflight_BINARY_DIR}
                    ${OPENSCENEGRAPH_INCLUDE_DIRS}
                    ${PLIB_INCLUDE_DIR}
                    ${SIMGEAR_INCLUDE_DIR}
                    ${MARBLE_INCLUDE_DIR}
                    ${KDE4_INCLUDES}
                    ${QT_INCLUDES}
                   )

kde4_add_ui_files(kfreeflight_SRCS
                  kfreeflightview_base.ui
                  prefs_page1_base.ui
                  prefs_page2_base.ui
                  prefs_page3_base.ui
                  prefs_page4_base.ui
                  prefs_page5_base.ui
                  option_airport_base.ui
                  option_property_base.ui
                  option_common_base.ui
                  option_rendering_base.ui
                  option_weather_base.ui
                  option_othersopt_base.ui
                  option_carrier_base.ui
                  option_aircraft_base.ui
                  option_scenery_base.ui
                  option_position_base.ui
                  option_datetime_base.ui
                  option_flightplan_base.ui
                  option_network_base.ui
                  option_radio_base.ui
                  win_calculator_base.ui
                  win_messages_base.ui
                  win_airport_base.ui
                  win_metarview_base.ui
                  win_metarcreate_base.ui
                  win_coordinates_base.ui
                  win_flightplan_base.ui
                  win_chooser_base.ui
                 )

kde4_add_kcfg_files(kfreeflight_SRCS settings.kcfgc )

kde4_add_executable(kfreeflight ${kfreeflight_SRCS})

target_link_libraries(kfreeflight ${LIBRARIES_TO_LINK} )

install(TARGETS kfreeflight DESTINATION ${INSTALL_TARGETS_DEFAULT_ARGS} )

########### install files ###############

set(KFREEFLIGHT_DATA_FILES
    kfreeflightui.rc
    splash.jpeg
    accueil.svg
    clouds.svg
    carrier.svg
    aircraft1.svg
    aircraft2.svg
    world.svg
    x29.svg
    spaceship.osg
   )

install( FILES kfreeflight.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES ${kfreeflight_BINARY_DIR}/kfreeflight.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
message(STATUS ${KCFG_INSTALL_DIR})
install( FILES ${KFREEFLIGHT_DATA_FILES} DESTINATION  ${KDE4_DATA_DIR}/kfreeflight )
message(STATUS ${KDE4_DATA_DIR})
kde4_install_icons( ${ICON_INSTALL_DIR} )

add_subdirectory( pics )
add_subdirectory( po )
add_subdirectory( doc )
