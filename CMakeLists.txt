CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
PROJECT( MinimalOculusApp )


#
# Platform-dependent section
#
IF( WIN32 )
    #
    # Custom Windows include and link dirs for my machine:
    #
    SET( LIBS_HOME "C:/lib" )

    SET( OCULUSSDK_ROOT "${LIBS_HOME}/OculusSDK-0.2.2" )
    INCLUDE_DIRECTORIES( "${OCULUSSDK_ROOT}/LibOVR/Include" )
    INCLUDE_DIRECTORIES( "${OCULUSSDK_ROOT}/LibOVR/Src" )
    LINK_DIRECTORIES   ( "${OCULUSSDK_ROOT}/LibOVR/Lib/Win32" )

    SET( PLATFORM_LIBS
        libovrd.lib
        Winmm.lib
        )

ELSEIF( APPLE )
    SET( LIBS_HOME "~/Development/" )
    
    SET( OCULUSSDK_ROOT "${LIBS_HOME}/Oculus/OculusSDK" )
    INCLUDE_DIRECTORIES( "${OCULUSSDK_ROOT}/LibOVR/Include" )
    INCLUDE_DIRECTORIES( "${OCULUSSDK_ROOT}/LibOVR/Src" )
    LINK_DIRECTORIES   ( "${OCULUSSDK_ROOT}/LibOVR/Lib/MacOS/Debug/" )
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(IOKIT_LIBRARY IOKit)

    MARK_AS_ADVANCED (COCOA_LIBRARY
                      IOKIT_LIBRARY
                      )
    # Todo - build OVR with RTTI suppo
    SET(CMAKE_CXX_FLAGS "-fno-rtti")
    
    SET( PLATFORM_LIBS
        libovr.a ${COCOA_LIBRARY} ${IOKIT_LIBRARY}  
        )     
ELSEIF( UNIX )
    ADD_DEFINITIONS( -D_LINUX )
    SET( LIBS_HOME "~/lib" )
    
    SET( OCULUSSDK_ROOT "${LIBS_HOME}/OculusSDK" )
    INCLUDE_DIRECTORIES( "${OCULUSSDK_ROOT}/LibOVR/Include" )
    INCLUDE_DIRECTORIES( "${OCULUSSDK_ROOT}/LibOVR/Src" )
    LINK_DIRECTORIES   ( "${OCULUSSDK_ROOT}/LibOVR/Lib/Linux/Debug/x86_64" )
    
    SET( PLATFORM_LIBS
        -lovr
        -pthread
        -ludev
        )
ENDIF()


#
# Platform-independent section
#
FILE( GLOB_RECURSE SOURCE_FILES
    src/*.cpp
    src/*.h
    )


INCLUDE_DIRECTORIES("src")

ADD_EXECUTABLE( ${PROJECT_NAME}
    src/minimal_oculus_app.cpp
    )

TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
    ${PLATFORM_LIBS}
    )
