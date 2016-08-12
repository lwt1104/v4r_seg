# Install script for directory: /home/arclab/Downloads/v4r_seg/v4r

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
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/v4r/SegmenterLight/model" TYPE DIRECTORY FILES "")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/v4r/SegmenterLight/model" TYPE FILE FILES
    "/home/arclab/Downloads/v4r_seg/v4r/model/param.txt"
    "/home/arclab/Downloads/v4r_seg/v4r/model/PP-Trainingsset.txt.scaled.model"
    "/home/arclab/Downloads/v4r_seg/v4r/model/param.txt.fast"
    "/home/arclab/Downloads/v4r_seg/v4r/model/PP-Trainingsset.txt.scaled.model.fast"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/v4r/SegmenterLight/config" TYPE DIRECTORY FILES "")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/v4r/SegmenterLight/config" TYPE FILE FILES "/home/arclab/Downloads/v4r_seg/v4r/KinectConfig.xml")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/v4r/SegmenterLight" TYPE DIRECTORY FILES "")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/v4r/SegmenterLight" TYPE FILE FILES
    "/home/arclab/Downloads/v4r_seg/v4r/disjoint-set.h"
    "/home/arclab/Downloads/v4r_seg/v4r/Edge.h"
    "/home/arclab/Downloads/v4r_seg/v4r/GraphCut.h"
    "/home/arclab/Downloads/v4r_seg/v4r/Graph.h"
    "/home/arclab/Downloads/v4r_seg/v4r/ClusterNormalsToPlanes.hh"
    "/home/arclab/Downloads/v4r_seg/v4r/PPlane.h"
    "/home/arclab/Downloads/v4r_seg/v4r/ZAdaptiveNormals.hh"
    "/home/arclab/Downloads/v4r_seg/v4r/SurfaceModeling.hh"
    "/home/arclab/Downloads/v4r_seg/v4r/BoundaryRelations.h"
    "/home/arclab/Downloads/v4r_seg/v4r/ColorHistogram3D.h"
    "/home/arclab/Downloads/v4r_seg/v4r/StructuralRelationsLight.h"
    "/home/arclab/Downloads/v4r_seg/v4r/CustomRelationsLight.h"
    "/home/arclab/Downloads/v4r_seg/v4r/Texture.h"
    "/home/arclab/Downloads/v4r_seg/v4r/SegmenterLight.h"
    "/home/arclab/Downloads/v4r_seg/v4r/ContourDetector.h"
    "/home/arclab/Downloads/v4r_seg/v4r/SurfaceModel.hpp"
    "/home/arclab/Downloads/v4r_seg/v4r/Relation.h"
    "/home/arclab/Downloads/v4r_seg/v4r/svm.h"
    "/home/arclab/Downloads/v4r_seg/v4r/SVMPredictorSingle.h"
    "/home/arclab/Downloads/v4r_seg/v4r/Capture.h"
    "/home/arclab/Downloads/v4r_seg/v4r/Device.h"
    "/home/arclab/Downloads/v4r_seg/v4r/Kinect.h"
    "/home/arclab/Downloads/v4r_seg/v4r/KinectData.h"
    "/home/arclab/Downloads/v4r_seg/v4r/FileSystem.hh"
    "/home/arclab/Downloads/v4r_seg/v4r/Utils.hh"
    "/home/arclab/Downloads/v4r_seg/v4r/FitSize.h"
    "/home/arclab/Downloads/v4r_seg/v4r/Centroid.h"
    "/home/arclab/Downloads/v4r_seg/v4r/FindPlanes.hh"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libv4rSegmenterLight.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libv4rSegmenterLight.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libv4rSegmenterLight.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/arclab/Downloads/v4r_seg/lib/libv4rSegmenterLight.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libv4rSegmenterLight.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libv4rSegmenterLight.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libv4rSegmenterLight.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libv4rSegmenterLight.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/SegmenterLight" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/SegmenterLight")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/SegmenterLight"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/arclab/Downloads/v4r_seg/build/SegmenterLight")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/SegmenterLight" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/SegmenterLight")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/SegmenterLight")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/SegmenterLight")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

