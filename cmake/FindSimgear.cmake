################################################################################
#                                   SIMGEAR                                    #
################################################################################
# SIMGEAR

set(SEARCH_LIBRARIES_PATH
    /usr/lib
    /usr/lib64
    /usr/local/lib
    /usr/local/lib64
    /opt/lib
    /opt/lib64
    /opt/simgear/lib
    /opt/simgear/lib64
   )

set(SEARCH_INCLUDE_PATH
    /usr/include/simgear
    /usr/local/include/simgear
    /opt/include/simgear
    /opt/simgear/include/simgear
   )

set( ALL_LIBRARIES_FOUND TRUE )

find_path(SIMGEAR_INCLUDE_DIR version.h ${SEARCH_INCLUDE_PATH} )

#
# -lsgroute -lsgsky -lsgsound -lsgephem -lsgtgdb -lsgmodel -lsgbvh
# -lsgmaterial -lsgutil -lsgtiming -lsgio -lsgscreen -lsgmath -lsgbucket
#  -lsgprops -lsgdebug -lsgmagvar -lsgmisc -lsgnasal -lsgxml -lsgsound
#  -lsgserial -lsgstructure -lsgenvironment -lplibpuaux -lplibpu -lplibfnt
#  -lplibjs -lplibnet -lplibsg -lplibul   -lsgthreads
#

set( SIMGEAR_TO_FOUND_LIBRARIES
     #lsgroute - seems to be not required
     #lsgskysgsound - seems to be not required
     sgephem
     sgtgdb
     sgmodel
     sgbvh
     sgmaterial
     sgutil
     sgtiming
     sgio
     sgscreen
     sgmath
     sgbucket
     sgprops
     sgdebug
     sgmagvar
     sgmisc
     sgnasal
     sgxml
     sgsound
     sgserial
     sgstructure
     sgenvironment
     sgthreads
   )

foreach( loop_var ${SIMGEAR_TO_FOUND_LIBRARIES} )
	find_library(SIMGEAR_LIBRARY NAMES ${loop_var} PATH ${SEARCH_LIBRARIES_PATH} )
	if (NOT SIMGEAR_LIBRARY MATCHES "-NOTFOUND")
	    set(SIMGEAR_LIBRARIES ${SIMGEAR_LIBRARIES} ${SIMGEAR_LIBRARY} )
	else()
	    message(STATUS "Library ${loop_var} not found")
	    set( ALL_LIBRARIES_FOUND FALSE )
	    unset(SIMGEAR_INCLUDE_DIR)
	    unset(SIMGEAR_LIBRARIES)
        break()
	endif()
endforeach()

if(SIMGEAR_INCLUDE_DIR AND ALL_LIBRARIES_FOUND)
   set(SIMGEAR_FOUND TRUE)
else()
   set(SIMGEAR_FOUND FALSE)
endif()


if (SIMGEAR_FOUND)
    message(STATUS "Found Simgear")
else (SIMGEAR_FOUND)
    if (SIMGEAR_FIND_REQUIRED)
        message(FATAL_ERROR "Could not found all Simgear libraries")
    endif(SIMGEAR_FIND_REQUIRED)
endif (SIMGEAR_FOUND)
