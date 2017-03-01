#include <unistd.h>
//#include "can/cancomm.h"
#include <signal.h>
#include <iomanip>
#include <iostream>


class InterfaceCan{
public:
  void run();
  void runCan();
};


void my_handler(int s);

void InterfaceCan::run()
{
  float i = 0;

  /*while (1)
    {
        emit updateRPM(i);
        i = i + 0.5;
        sleep(1);
	}*/

  //runCan();
}

void InterfaceCan::runCan() {
  std::cout << "runCan called" << std::endl;
  //system("modprobe vcan");
  //system("ip link set vcan0 up type vcan bitrate 250000");
  //system("ifconfig vcan0 up");
  char* argv2[2];
  argv2[0] = " ";
  argv2[1] = "can0";
  struct canfd_frame message;
  struct sigaction siginthandler;
  siginthandler.sa_handler = my_handler;
  sigemptyset(&siginthandler.sa_mask);
  siginthandler.sa_flags=0;
  sigaction(SIGINT, &siginthandler, NULL);
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
  time_t end = time(NULL) + 20;

  while (1)
    {
      message = canrecieve(2, argv2);
      if (message.len > 0)
	{
	  //std::cout << message.can_id << std::endl;
	  switch(message.can_id)
	    {
	    case 0x186:
	      {
		std::cout << "0x186" << std::endl;
		rpm = (message.data[1] << 8 | message.data[0]);
		//emit updateRPM(rpm);
		RMS_current = (message.data[7] << 8 | message.data[6]);
		//emit updateRMScurr(RMS_current);
		DC_voltage = (message.data[5] << 8 | message.data[4]);
		//emit updateDCvolt(DC_voltage/100.0);
		drive6stat = (message.data[3] << 8 | message.data[2]);
		//emit sendD6stat(drive6stat);
		break;
	      }
	    case 0x183:
	      {
		batterytemp = (message.data[5] << 8 | message.data[4]);
		//emit updateBatteryTemp(batterytemp);
		break;
	      }
	    case 0x286:
	      {
		std::cout << "0x286" << std::endl;
		HS_temp = (message.data[1] << 8 | message.data[0]);
		//emit updateHStemp(HS_temp);
		motor_temp = (message.data[3] << 8 | message.data[2]);
		//emit updateMotorTemp(motor_temp);
		voltage_angle = (message.data[7] << 8 | message.data[6]);
		//emit updateVoltAngle(voltage_angle);
		break;
	      }
	    case 0x386:
	      {
		IQ_current = (message.data[1] << 8 | message.data[0]);
		//emit updateIQcurr(IQ_current);
		break;
	      }
	    case 0x086:
	      {
		EMCY6 = (message.data[1] << 8 | message.data[0]);
		//emit sendEMCY6(EMCY6);
		break;
	      }
	    case 0x087:
	      {
		EMCY7 = (message.data[1] << 8 | message.data[0]);
		//emit sendEMCY7(EMCY7);
		break;
	      }
	    case 0x187:
	      {
		drive7stat = (message.data[3] << 8 | message.data[2]);
		//emit sendD7stat(drive7stat);
		break;
	      }
	    default: {}
	    }
	}
      //else
      //{
      //   cout << "Recieved CAN Error" << endl;
      //   // Log and error here? otherwise do nothing...
      //}
    }
}

void my_handler(int s)
{
  exit(0);
}
