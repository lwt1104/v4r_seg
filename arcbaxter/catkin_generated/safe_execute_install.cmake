execute_process(COMMAND "/home/arc/ros_ws/src/v4r_seg/arcbaxter/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/arc/ros_ws/src/v4r_seg/arcbaxter/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
