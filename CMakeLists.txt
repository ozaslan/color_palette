cmake_minimum_required(VERSION 3.5.1)
project(color_utils)

## Add support for C++11, supported in ROS Kinetic and newer
add_definitions(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roslib 
)

## System dependencies are found with CMake's conventions
find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenCV 3 REQUIRED)
                  
MESSAGE( STATUS "OpenCV Library Found : " ${OpenCV_FOUND} )                                                                                                             
MESSAGE( STATUS "OpenCV Libraries     : " ${OpenCV_LIBRARIES} )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES color_palette color_library
  CATKIN_DEPENDS roslib
  DEPENDS EIGEN3 Boost OpenCV 
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  include
)

add_library(color_palette src/color_palette.cc)
target_link_libraries(color_palette ${catkin_LIBRARIES})

add_library(color_library src/color_library.cc)
target_link_libraries(color_library color_palette ${catkin_LIBRARIES})

add_executable(test_color_library test/test_color_library.cc)
target_link_libraries(test_color_library color_library ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
