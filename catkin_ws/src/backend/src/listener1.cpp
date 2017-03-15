#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include <iostream>

#include "/home/pi/catkin_ws/devel/include/backend/can_msg.h"

//void chatterCallback_string(const std_msgs::String::ConstPtr& msg)
void chatterCallback_string(const backend::can_msg::ConstPtr& msg)
{
  //ROS_INFO("I heard: [%i]", msg->can_id);
  ROS_INFO("[can_id], data: [%i], %i", msg->can_id, msg->data);
  if(msg->can_id == 387)
    std::cout << "battery temp signal" << std::endl;
  
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener1");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("chatter_can", 1000, chatterCallback_string);

  ros::spin();

  return 0;
}
