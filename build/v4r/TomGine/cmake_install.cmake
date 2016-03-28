# Install script for directory: /home/lwt1104/Downloads/SegmenterLight/v4r/TomGine

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/v4r/TomGine" TYPE DIRECTORY FILES "")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/v4r/TomGine" TYPE FILE FILES
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/GLEvent.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/GLInput.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/GLWindow.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/headers.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/ply.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/PlyStructure.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgCamera.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgCollission.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgEngine.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgError.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgErrorMetric.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgFont.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgFrameBufferObject.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgFrustum.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgLight.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgMaterial.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgMathlib.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgModel.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgModelLoader.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgPlot2D.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgPose.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgQuaternion.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgRenderModel.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgShapeCreator.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgSingleton.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgTexture.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgTextureModel.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgTimer.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgTomGine.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/tgTomGineThread.h"
    "/home/lwt1104/Downloads/SegmenterLight/v4r/TomGine/ub3Image.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libv4rTomGine.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libv4rTomGine.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libv4rTomGine.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/lwt1104/Downloads/SegmenterLight/lib/libv4rTomGine.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libv4rTomGine.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libv4rTomGine.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libv4rTomGine.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

