cmake_minimum_required(VERSION 2.8)
project(downsampling_image_transport)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

find_package(catkin REQUIRED COMPONENTS roscpp image_transport sensor_msgs dynamic_reconfigure)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

generate_dynamic_reconfigure_options(cfg/DownsamplingDyn.cfg)

catkin_package(
INCLUDE_DIRS include
LIBRARIES ${PROJECT_NAME}
CATKIN_DEPENDS roscpp image_transport sensor_msgs dynamic_reconfigure
)


include_directories(include
  ${catkin_INCLUDE_DIRS})

# add the plugin
add_library(${PROJECT_NAME} src/manifest.cpp src/downsampling_publisher.cpp
src/downsampling_subscriber.cpp)

add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})

install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
	FILES_MATCHING PATTERN "*.h"
	)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
