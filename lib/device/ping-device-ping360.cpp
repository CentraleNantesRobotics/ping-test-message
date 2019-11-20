#include <ping-device-ping360.h>
#include <ping-message-common.h>
#include <ping-message-ping360.h>

Ping360::~Ping360()
{
  if (profile_data) {
   free(profile_data);
  }
}

bool Ping360::initialize(uint16_t pingIntervalMs)
{
  if (!PingDevice::initialize()) {
    return false;
  }

  // Configure ping interval
  // if (!set_ping_interval(pingIntervalMs)) {
  //   return false;
  // }

  return true;
}


 