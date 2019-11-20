#include "ping-port-linux.h"
#include <ping-device-ping360.h>
#include "ping-message-common.h"
#include "ping-message-ping360.h"
#include "ping-port-linux.h"
#include <iostream>


int main(){
    const char* port = "/dev/ttyUSB0";
    PingPortLinux sonarPort = PingPortLinux(port);
    Ping360 sonar = Ping360(sonarPort);

if (!sonar.initialize(100)){
    printf("device initialization failed\n");
} else {
    printf("pass\n");
    printf("Device Type %d id %d hardware revision %d\n", sonar.device_type, sonar.device_id, sonar.device_revision);
    printf("Ping Protocol v%d.%d.%d\n", sonar.version_major, sonar.version_minor, sonar.version_patch);
    printf("Device Firmware v%d.%d.%d\n", sonar.firmware_version_major, sonar.firmware_version_minor, sonar.firmware_version_patch);
}

    return 0;
}