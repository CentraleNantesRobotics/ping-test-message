#include "ping-port-linux.h"
#include <ping-device.h>
#include "ping-message-common.h"
#include "ping-port-linux.h"
#include <iostream>


int main(){
    const char* port = "/dev/ttyUSB0";
    PingPortLinux sonarPort = PingPortLinux(port);
    PingDevice sonar = PingDevice(sonarPort);

 if (!sonar.initialize()){
     printf("device initialization failed\n");
 } else {
     //ping_message oi = sonar.read();
     //std::cout <<  << std::endl;
     printf("pass\n");
     printf("Device Type %d id %d hardware revision %d\n", sonar.device_type, sonar.device_id, sonar.device_revision);
     printf("Ping Protocol v%d.%d.%d\n", sonar.version_major, sonar.version_minor, sonar.version_patch);
     printf("Device Firmware v%d.%d.%d\n", sonar.firmware_version_major, sonar.firmware_version_minor, sonar.firmware_version_patch);
 }

    return 0;
}