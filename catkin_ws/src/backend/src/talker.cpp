#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include "canrecieve.cpp"
//#include "caninterface.cpp"
#include "can_msg.h"
#include "motor_msg.h"
#include "batterytemp_msg.h"
#include "temp_msg.h"
#include "current_msg.h"
#include "emcy6_msg.h"
#include "emcy7_msg.h"
#include "drive7_msg.h"

#include <iostream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::Publisher chatter_can = n.advertise<backend::can_msg>("chatter_can", 1000);
  ros::Publisher chatter_motor = n.advertise<backend::motor_msg>("chatter_motor", 1000);
  ros::Publisher chatter_batterytemp = n.advertise<backend::batterytemp_msg>("chatter_batterytemp", 1000);
  ros::Publisher chatter_temp = n.advertise<backend::temp_msg>("chatter_temp", 1000);
  ros::Publisher chatter_current = n.advertise<backend::current_msg>("chatter_current", 1000);
  ros::Publisher chatter_emcy6 = n.advertise<backend::emcy6_msg>("chatter_emcy6", 1000);
  ros::Publisher chatter_emcy7 = n.advertise<backend::emcy7_msg>("chatter_emcy7", 1000);
  ros::Publisher chatter_drive7 = n.advertise<backend::drive7_msg>("chatter_drive7", 1000);

	  
  
  ros::Rate loop_rate(10);
  
  struct canfd_frame message;
  char* argv2[2];
  argv2[0] = " ";
  argv2[1] = "can0";
  int count = 0;
  
  while (ros::ok())
    {
      std::cout << "while loop" << std::endl;
      std::string name;
      std::string value;
      signed short batterytemp = 0;
      signed short rpm = 0;
      signed short RMS_current = 0;
      signed short DC_voltage = 0;
      signed short HS_temp = 0;
      signed short motor_temp = 0;
      signed short voltage_angle = 0;
      signed short IQ_current = 0;
      signed short EMCY6 = 0;
      signed short EMCY7 = 0;
      signed short drive6stat = 0;
      signed short drive7stat = 0;
      
      backend::can_msg c_msg;
      backend::motor_msg motor_msg;
      backend::batterytemp_msg batterytemp_msg;
      backend::temp_msg temp_msg;
      backend::current_msg current_msg;
      backend::emcy6_msg emcy6_msg;
      backend::emcy7_msg emcy7_msg;
      backend::drive7_msg drive7_msg;
			 
      
      std::cout << "calling canrecieve" << std::endl;
      message = canrecieve(2, argv2, std::cin);

      switch(message.can_id)
	{
	case 0x186:
	  {
	    rpm = (message.data[1] << 8 | message.data[0]);
	    RMS_current = (message.data[7] << 8 | message.data[6]);
	    DC_voltage = (message.data[5] << 8 | message.data[4]);
	    drive6stat = (message.data[3] << 8 | message.data[2]);
	    motor_msg.can_id = message.can_id;
	    motor_msg.rpm = rpm;
	    motor_msg.RMS_current;
	    motor_msg.DC_voltage;
	    motor_msg.drive6stat;
	    chatter_motor.publish(motor_msg);
	    ROS_INFO("[can_id], data: [%i], %i", motor_msg.can_id, motor_msg.rpm);
	    break;
	  }
	case 0x183:
	  {

	    batterytemp = (message.data[5] << 8 | message.data[4]);
	    //std:: cout << "battery temp " << std::hex << batterytemp << std::endl;
	    batterytemp_msg.can_id = message.can_id;
	    batterytemp_msg.data = batterytemp;
	    chatter_batterytemp.publish(batterytemp_msg);
	    ROS_INFO("[can_id], data: [%i], %i", batterytemp_msg.can_id, batterytemp_msg.data);
	    break;
	  }
	case 0x286:
	  {
	    HS_temp = (message.data[1] << 8 | message.data[0]);
	    motor_temp = (message.data[3] << 8 | message.data[2]);
	    voltage_angle = (message.data[7] << 8 | message.data[6]);
	    temp_msg.can_id = message.can_id;
	    temp_msg.HS_temp = HS_temp;
	    temp_msg.motor_temp = motor_temp;
	    temp_msg.motor_temp = voltage_angle;
	    ROS_INFO("[can_id], data: [%i], %i", temp_msg.can_id, temp_msg.HS_temp);
	    chatter_temp.publish(temp_msg);
	    break;
	  }
	case 0x386:
	  {
	    IQ_current = (message.data[1] << 8 | message.data[0]);
	    current_msg.data = IQ_current;
	    chatter_current.publish(current_msg);
	    ROS_INFO("[can_id], data: [%i], %i", current_msg.can_id, current_msg.data);
	    break;
	  }
	case 0x086:
	  {
	    EMCY6 = (message.data[1] << 8 | message.data[0]);
	    emcy6_msg.data = EMCY6;
	    chatter_emcy6.publish(emcy6_msg);
	    ROS_INFO("[can_id], data: [%i], %i", emcy6_msg.can_id, emcy6_msg.data);
	  break;
	  }
	case 0x087:
	  {
	    EMCY7 = (message.data[1] << 8 | message.data[0]);
	    emcy7_msg.data = EMCY7;
	    chatter_emcy7.publish(emcy7_msg);
	    ROS_INFO("[can_id], data: [%i], %i", emcy7_msg.can_id, emcy7_msg.data);
	    break;
	  }
	case 0x187:
	  {
	    drive7stat = (message.data[3] << 8 | message.data[2]);
	    drive7_msg.data = drive7stat;
	    chatter_drive7.publish(drive7_msg);
	    ROS_INFO("[can_id], data: [%i], %i", drive7_msg.can_id, drive7_msg.data);
	    break;
	  }
	}  
      
      if(count > 80)
	exit(0);
      else
	count++;
      
      ros::spinOnce();

      loop_rate.sleep();
    }


  return 0;
    }
