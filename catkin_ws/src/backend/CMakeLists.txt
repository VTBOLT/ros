cmake_minimum_required(VERSION 2.8.3)
project(backend)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  genmsg
  message_generation
  )

## Declare ROS messages and services
#add_message_files(DIRECTORY msg FILES Num.msg)
#add_service_files(DIRECTORY srv FILES AddTwoInts.srv)
add_message_files(
  DIRECTORY
  msg
  FILES
  can_msg.msg
  motor_msg.msg
  batterytemp_msg.msg
  temp_msg.msg
  current_msg.msg
  emcy6_msg.msg
  emcy7_msg.msg
  drive7_msg.msg
  )
## Generate added messages and services
generate_messages(
  DEPENDENCIES
  std_msgs
  )

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS} can/ msg/)


add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})
#add_dependencies(talker beginner_tutorials_generate_messages_cpp)
add_dependencies(talker
  can/canrecieve.cpp
  can/interfacecan.cpp
  )

add_executable(listener1 src/listener1.cpp)
target_link_libraries(listener1 ${catkin_LIBRARIES})
#add_dependencies(listener1)

add_executable(listener2 src/listener2.cpp)
target_link_libraries(listener2 ${catkin_LIBRARIES})
#add_dependencies(listener2) 
