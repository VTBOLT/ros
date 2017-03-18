#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include "/home/pi/catkin_ws/devel/include/backend/can_msg.h"
#include "/home/pi/catkin_ws/devel/include/backend/motor_msg.h"
#include "/home/pi/catkin_ws/devel/include/backend/batterytemp_msg.h"
#include "/home/pi/catkin_ws/devel/include/backend/temp_msg.h"
#include "/home/pi/catkin_ws/devel/include/backend/current_msg.h"
#include "/home/pi/catkin_ws/devel/include/backend/emcy6_msg.h"
#include "/home/pi/catkin_ws/devel/include/backend/emcy7_msg.h"
#include "/home/pi/catkin_ws/devel/include/backend/drive7_msg.h"
#include <iostream>

#define RPM         0
#define BATT_TEMP   1
#define RMS_CURRENT 2
#define DC_VOLTS    3
#define HS_TEMP     4
#define MOTOR_TEMP  5
#define VOLT_ANGLE  6
#define IQ_CURRENT  7
#define EMCY6       8
#define EMCY7       9
#define D6_STAT     10
#define D7_STAT     11

void chatterCallback_motor(const backend::motor_msg::ConstPtr& msg)
{
  //ROS_INFO("motor [can_id]: [%i] rpm: %i RMS_currentL %i DC_voltage: %i drive6stat: %i", msg->can_id, msg->rpm, msg->RMS_current, msg->DC_voltage, msg->drive6stat);
  std::cout << "<" << RPM << ">;<" << msg->rpm << ">" << std::endl;
  std::cout << "<" << RMS_CURRENT << ">;<" << msg->RMS_current << ">" << std::endl;
  std::cout << "<" << DC_VOLTS << ">;<" << msg->DC_voltage << ">" << std::endl;
}

void chatterCallback_batterytemp(const backend::batterytemp_msg::ConstPtr& msg)
{
  //ROS_INFO("batterytemp [can_id]: [%i] batterytemp: %i", msg->can_id, msg->data);
  std::cout << "<" << BATT_TEMP << ">;<" << msg->data << ">" << std::endl;
}

void chatterCallback_temp(const backend::temp_msg::ConstPtr& msg)
{
  //ROS_INFO("temp [can_id]: [%i], HS_temp: %i motor_temp: %i voltage_angle: %i", msg->can_id, msg->HS_temp, msg->motor_temp, msg->voltage_angle);
  std::cout << "<" << HS_TEMP << ">;<" << msg->HS_temp << ">" << std::endl;
  std::cout << "<" << MOTOR_TEMP << ">;<" << msg->motor_temp << ">" << std::endl;
  std::cout << "<" << VOLT_ANGLE << ">;<" << msg->voltage_angle << ">" << std::endl;
}

void chatterCallback_current(const backend::current_msg::ConstPtr& msg)
{
  //ROS_INFO("current [can_id]: [%i], IQ_current: %i", msg->can_id, msg->data);
  std::cout << "<" << IQ_CURRENT << ">;<" << msg->data << ">" << std::endl;
}

void chatterCallback_emcy6(const backend::emcy6_msg::ConstPtr& msg)
{
  //ROS_INFO("EMCY6 [can_id]: [%i], emcy6: %i", msg->can_id, msg->data);
  std::cout << "<" << EMCY6 << ">;<" << msg->data << ">" << std::endl;
}

void chatterCallback_emcy7(const backend::emcy7_msg::ConstPtr& msg)
{
  //ROS_INFO("EMCY7 [can_id]: [%i], emcy7: %i", msg->can_id, msg->data);
  std::cout << "<" << EMCY7 << ">;<" << msg->data << ">" << std::endl;
}

void chatterCallback_drive7(const backend::drive7_msg::ConstPtr& msg)
{
  //ROS_INFO("drive7 [can_id]: [%i], drive7: %i", msg->can_id, msg->data);
  std::cout << "<" << D7_STAT  << ">;<" << msg->data << ">" << std::endl;
}


int main(int argc, char **argv)
{
  //std::cout << "listener2 called" << std::endl;
  ros::init(argc, argv, "listener2");

  ros::NodeHandle n;

  ros::Subscriber sub1 = n.subscribe("chatter_motor", 1000, chatterCallback_motor);
  ros::Subscriber sub2 = n.subscribe("chatter_batterytemp", 1000, chatterCallback_batterytemp);
  ros::Subscriber sub3 = n.subscribe("chatter_temp", 1000, chatterCallback_temp);
  ros::Subscriber sub4 = n.subscribe("chatter_current", 1000, chatterCallback_current);
  ros::Subscriber sub5 = n.subscribe("chatter_emcy6", 1000, chatterCallback_emcy6);
  ros::Subscriber sub6 = n.subscribe("chatter_emcy7", 1000, chatterCallback_emcy7);
  ros::Subscriber sub7 = n.subscribe("chatter_drive7", 1000, chatterCallback_drive7);
	
  ros::spin();

  return 0;
}
