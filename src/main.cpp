#include "ping-port-linux.h"
#include <ping-device.h>
// #include "ping-message-common.h"
#include "ping-message-ping360.h"
#include "ping-port-linux.h"
#include <iostream>


int main(){
    const char* port = "/dev/ttyUSB0";
    PingPortLinux sonarPort = PingPortLinux(port);
    PingDevice sonar = PingDevice(sonarPort);

 if (!sonar.initialize()){
     printf("device initialization failed\n");
 } else {
    //std::cout <<  << std::endl;
    printf("pass\n");
    printf("Device Type %d id %d hardware revision %d\n", sonar.device_type, sonar.device_id, sonar.device_revision);
    printf("Ping Protocol v%d.%d.%d\n", sonar.version_major, sonar.version_minor, sonar.version_patch);
    printf("Device Firmware v%d.%d.%d\n", sonar.firmware_version_major, sonar.firmware_version_minor, sonar.firmware_version_patch);
    
    uint16_t id = 2300;
    
    // Send settings
    for (uint16_t i = 0; i < 400; i = i + 10)
    {
      ping360_transducer settingsData = ping360_transducer(1200);
      settingsData.set_mode(1);
      settingsData.set_gain_setting(1);
      settingsData.set_angle(i);
      settingsData.set_transmit_duration(32);
      settingsData.set_transmit_frequency(750);
      settingsData.set_sample_period(80);
      settingsData.set_number_of_samples(1200);
      settingsData.set_transmit(1);
      sonar.writeMessage(settingsData);
      sonar.waitMessage(2601, 4000); 
    }
    // sonar.writeMessage(settings);

    // ping_message* oi = sonar.request(id, 1000);
    // ping360_transducer trans(*oi);
    // ping360_device_data deviceData = ping360_device_data(*oi); // *static_cast<const ping360_device_data*>(&oi);
    // uint16_t angle = deviceData.angle();
    
     
    //  std::cout << trans.gain_setting() << std::endl;
 }

    return 0;
}