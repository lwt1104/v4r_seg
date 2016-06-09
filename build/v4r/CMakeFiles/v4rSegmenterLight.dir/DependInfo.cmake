# The set of languages for which implicit dependencies are needed:
SET(CMAKE_DEPENDS_LANGUAGES
  "CXX"
  )
# The set of files for implicit dependencies of each language:
SET(CMAKE_DEPENDS_CHECK_CXX
  "/home/arc/Documents/v4r_seg/v4r/BoundaryRelations.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/BoundaryRelations.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/Capture.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/Capture.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/Centroid.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/Centroid.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/ClusterNormalsToPlanes.cc" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/ClusterNormalsToPlanes.cc.o"
  "/home/arc/Documents/v4r_seg/v4r/ColorHistogram3D.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/ColorHistogram3D.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/ContourDetector.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/ContourDetector.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/CustomRelationsLight.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/CustomRelationsLight.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/Device.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/Device.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/FileSystem.cc" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/FileSystem.cc.o"
  "/home/arc/Documents/v4r_seg/v4r/FindPlanes.cc" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/FindPlanes.cc.o"
  "/home/arc/Documents/v4r_seg/v4r/FitSize.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/FitSize.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/Graph.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/Graph.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/GraphCut.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/GraphCut.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/Kinect.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/Kinect.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/KinectData.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/KinectData.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/SVMPredictorSingle.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/SVMPredictorSingle.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/SegmenterLight.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/SegmenterLight.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/StructuralRelationsLight.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/StructuralRelationsLight.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/SurfaceModeling.cc" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/SurfaceModeling.cc.o"
  "/home/arc/Documents/v4r_seg/v4r/Texture.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/Texture.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/Utils.cc" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/Utils.cc.o"
  "/home/arc/Documents/v4r_seg/v4r/ZAdaptiveNormals.cc" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/ZAdaptiveNormals.cc.o"
  "/home/arc/Documents/v4r_seg/v4r/disjoint-set.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/disjoint-set.cpp.o"
  "/home/arc/Documents/v4r_seg/v4r/svm.cpp" "/home/arc/Documents/v4r_seg/build/v4r/CMakeFiles/v4rSegmenterLight.dir/svm.cpp.o"
  )
SET(CMAKE_CXX_COMPILER_ID "GNU")

# Preprocessor definitions for this target.
SET(CMAKE_TARGET_DEFINITIONS
  "DISABLE_DAVIDSDK"
  "DISABLE_DSSDK"
  "DISABLE_ENSENSO"
  "DISABLE_LIBUSB_1_0"
  "DISABLE_PCAP"
  "DISABLE_PNG"
  "DISABLE_RSSDK"
  "EIGEN_USE_NEW_STDVECTOR"
  "EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET"
  "FLANN_STATIC"
  "KINECT_CONFIG=\"/usr/local/include/v4r/SegmenterLight/config/KinectConfig.xml\""
  "LINUX"
  "SVM_MODEL=\"/usr/local/include/v4r/SegmenterLight/model/\""
  "qh_QHpointer"
  )

# Targets to which this target links.
SET(CMAKE_TARGET_LINKED_INFO_FILES
  )

# The include file search paths:
SET(CMAKE_C_TARGET_INCLUDE_PATH
  "/usr/include/opencv"
  "../."
  "../v4r/."
  "/usr/include/vtk-5.8"
  "/usr/local/include/pcl-1.8"
  "/usr/include/eigen3"
  "/usr/include/ni"
  "/usr/include/openni2"
  )
SET(CMAKE_CXX_TARGET_INCLUDE_PATH ${CMAKE_C_TARGET_INCLUDE_PATH})
SET(CMAKE_Fortran_TARGET_INCLUDE_PATH ${CMAKE_C_TARGET_INCLUDE_PATH})
SET(CMAKE_ASM_TARGET_INCLUDE_PATH ${CMAKE_C_TARGET_INCLUDE_PATH})
