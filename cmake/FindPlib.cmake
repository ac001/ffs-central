################################################################################
#                                   PLIB                                       #
################################################################################
# PLIB

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
    /usr/include/plib
    /usr/local/include/plib
    /opt/include/plib
    /opt/plib/include/plib
   )

set( ALL_LIBRARIES_FOUND TRUE )

find_path(PLIB_INCLUDE_DIR ssg.h ${SEARCH_INCLUDE_PATH} )

set( PLIB_TO_FOUND_LIBRARIES
     plibpuaux
     plibpu
     plibfnt
     plibjs
     plibnet
     plibsg
     plibul
   )

foreach( loop_var ${PLIB_TO_FOUND_LIBRARIES} )
	find_library(PLIB_LIBRARY NAMES ${loop_var} PATH ${SEARCH_LIBRARIES_PATH} )
	if (NOT PLIB_LIBRARY MATCHES "-NOTFOUND")
	    set(PLIB_LIBRARIES ${PLIB_LIBRARIES} ${PLIB_LIBRARY} )
	else()
	    message(STATUS "Library ${loop_var} not found")
	    set( ALL_LIBRARIES_FOUND FALSE )
	    unset(PLIB_INCLUDE_DIR)
	    unset(PLIB_LIBRARIES)
        break()
	endif()
endforeach()

if(PLIB_INCLUDE_DIR AND ALL_LIBRARIES_FOUND)
   set(PLIB_FOUND TRUE)
else()
   set(PLIB_FOUND FALSE)
endif()

if (PLIB_FOUND)
    message(STATUS "Found plib")
else (PLIB_FOUND)
    if (PLIB_FIND_REQUIRED)
        message(FATAL_ERROR "Could not found all plib libraries")
    endif(PLIB_FIND_REQUIRED)
endif (PLIB_FOUND)