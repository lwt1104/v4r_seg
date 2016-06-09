# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "arcbaxter: 1 messages, 3 services")

set(MSG_I_FLAGS "-Iarcbaxter:/home/arc/ros_ws/src/arcbaxter/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(arcbaxter_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/srv/Vision.srv" NAME_WE)
add_custom_target(_arcbaxter_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arcbaxter" "/home/arc/ros_ws/src/arcbaxter/srv/Vision.srv" ""
)

get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/msg/point2d.msg" NAME_WE)
add_custom_target(_arcbaxter_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arcbaxter" "/home/arc/ros_ws/src/arcbaxter/msg/point2d.msg" ""
)

get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/srv/VisionVertical.srv" NAME_WE)
add_custom_target(_arcbaxter_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arcbaxter" "/home/arc/ros_ws/src/arcbaxter/srv/VisionVertical.srv" ""
)

get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/srv/Kinect.srv" NAME_WE)
add_custom_target(_arcbaxter_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "arcbaxter" "/home/arc/ros_ws/src/arcbaxter/srv/Kinect.srv" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(arcbaxter
  "/home/arc/ros_ws/src/arcbaxter/msg/point2d.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arcbaxter
)

### Generating Services
_generate_srv_cpp(arcbaxter
  "/home/arc/ros_ws/src/arcbaxter/srv/Vision.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arcbaxter
)
_generate_srv_cpp(arcbaxter
  "/home/arc/ros_ws/src/arcbaxter/srv/Kinect.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arcbaxter
)
_generate_srv_cpp(arcbaxter
  "/home/arc/ros_ws/src/arcbaxter/srv/VisionVertical.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arcbaxter
)

### Generating Module File
_generate_module_cpp(arcbaxter
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arcbaxter
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(arcbaxter_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(arcbaxter_generate_messages arcbaxter_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/srv/Vision.srv" NAME_WE)
add_dependencies(arcbaxter_generate_messages_cpp _arcbaxter_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/msg/point2d.msg" NAME_WE)
add_dependencies(arcbaxter_generate_messages_cpp _arcbaxter_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/srv/VisionVertical.srv" NAME_WE)
add_dependencies(arcbaxter_generate_messages_cpp _arcbaxter_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/srv/Kinect.srv" NAME_WE)
add_dependencies(arcbaxter_generate_messages_cpp _arcbaxter_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(arcbaxter_gencpp)
add_dependencies(arcbaxter_gencpp arcbaxter_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS arcbaxter_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(arcbaxter
  "/home/arc/ros_ws/src/arcbaxter/msg/point2d.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arcbaxter
)

### Generating Services
_generate_srv_lisp(arcbaxter
  "/home/arc/ros_ws/src/arcbaxter/srv/Vision.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arcbaxter
)
_generate_srv_lisp(arcbaxter
  "/home/arc/ros_ws/src/arcbaxter/srv/Kinect.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arcbaxter
)
_generate_srv_lisp(arcbaxter
  "/home/arc/ros_ws/src/arcbaxter/srv/VisionVertical.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arcbaxter
)

### Generating Module File
_generate_module_lisp(arcbaxter
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arcbaxter
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(arcbaxter_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(arcbaxter_generate_messages arcbaxter_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/srv/Vision.srv" NAME_WE)
add_dependencies(arcbaxter_generate_messages_lisp _arcbaxter_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/msg/point2d.msg" NAME_WE)
add_dependencies(arcbaxter_generate_messages_lisp _arcbaxter_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/srv/VisionVertical.srv" NAME_WE)
add_dependencies(arcbaxter_generate_messages_lisp _arcbaxter_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/srv/Kinect.srv" NAME_WE)
add_dependencies(arcbaxter_generate_messages_lisp _arcbaxter_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(arcbaxter_genlisp)
add_dependencies(arcbaxter_genlisp arcbaxter_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS arcbaxter_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(arcbaxter
  "/home/arc/ros_ws/src/arcbaxter/msg/point2d.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arcbaxter
)

### Generating Services
_generate_srv_py(arcbaxter
  "/home/arc/ros_ws/src/arcbaxter/srv/Vision.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arcbaxter
)
_generate_srv_py(arcbaxter
  "/home/arc/ros_ws/src/arcbaxter/srv/Kinect.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arcbaxter
)
_generate_srv_py(arcbaxter
  "/home/arc/ros_ws/src/arcbaxter/srv/VisionVertical.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arcbaxter
)

### Generating Module File
_generate_module_py(arcbaxter
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arcbaxter
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(arcbaxter_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(arcbaxter_generate_messages arcbaxter_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/srv/Vision.srv" NAME_WE)
add_dependencies(arcbaxter_generate_messages_py _arcbaxter_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/msg/point2d.msg" NAME_WE)
add_dependencies(arcbaxter_generate_messages_py _arcbaxter_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/srv/VisionVertical.srv" NAME_WE)
add_dependencies(arcbaxter_generate_messages_py _arcbaxter_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/arc/ros_ws/src/arcbaxter/srv/Kinect.srv" NAME_WE)
add_dependencies(arcbaxter_generate_messages_py _arcbaxter_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(arcbaxter_genpy)
add_dependencies(arcbaxter_genpy arcbaxter_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS arcbaxter_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arcbaxter)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/arcbaxter
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
add_dependencies(arcbaxter_generate_messages_cpp std_msgs_generate_messages_cpp)

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arcbaxter)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/arcbaxter
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
add_dependencies(arcbaxter_generate_messages_lisp std_msgs_generate_messages_lisp)

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arcbaxter)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arcbaxter\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/arcbaxter
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
add_dependencies(arcbaxter_generate_messages_py std_msgs_generate_messages_py)
