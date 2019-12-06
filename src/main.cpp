#include "ping-port-linux.h"
#include <ping-device.h>
#include "ping-message-common.h"
#include "ping-message-ping360.h"
#include "ping-port-linux.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include "time.h"


double getSamplePeriod(double sample_period, double _samplePeriodTickDuration = 25e-9)
{
    return sample_period*_samplePeriodTickDuration;
}

double transmitDurationMax(double samplePeriod, double _firmwareMaxTransmitDuration = 500)
{   
  return std::min(_firmwareMaxTransmitDuration, getSamplePeriod(samplePeriod) * 64e6);
}

double calculateSamplePeriod(double distance, double numberOfSamples, double speedOfSound, double _samplePeriodTickDuration = 25e-9)
{
    return 2*distance/(numberOfSamples*speedOfSound*_samplePeriodTickDuration);
}

double adjustTransmitDuration(double distance, double samplePeriod, double speedOfSound, double _firmwareMinTransmitDuration = 5)
{
    double duration = 8000 * distance / speedOfSound;
    double transmit_duration = std::max(2.5*getSamplePeriod(samplePeriod)/1000, duration);
    return std::max(_firmwareMinTransmitDuration, std::min(transmitDurationMax(samplePeriod), transmit_duration));
}
 

int main(){
    srand(time(NULL));

    const char* port = "/dev/ttyUSB0";
    PingPortLinux sonarPort(port);
    PingDevice sonar = PingDevice(sonarPort);
    std::vector<uint8_t> _data;
    sonar.initialize();
    printf("pass\n");
    printf("Device Type %d id %d hardware revision %d\n", sonar.device_type, sonar.device_id, sonar.device_revision);
    printf("Ping Protocol v%d.%d.%d\n", sonar.version_major, sonar.version_minor, sonar.version_patch);
    printf("Device Firmware v%d.%d.%d\n", sonar.firmware_version_major, sonar.firmware_version_minor, sonar.firmware_version_patch);
    int angle = 0;
    while(true){
      // Sonar params    
      double num_points = 10;         // 1200 points
      int gain = 0;                  // Low gain
      angle = (angle + 1) % 400;               // 200ᵍ
      int transmit_frequency = 740;  // Default frequency
      float speedOfSound = 1500;
      int range = 30;          // 30m range
      float sample_period = calculateSamplePeriod(range, num_points, speedOfSound);
      float transmit_duration = adjustTransmitDuration(range, sample_period, speedOfSound);

      // Create the transducer message now with the new values
      ping360_transducer transducer_message;
      int mode = 1;
      transducer_message.set_mode(mode);
      std::cout << "-Mode: " <<transducer_message.mode() << std::endl;
      transducer_message.set_gain_setting(gain);
      std::cout << "-Gain: " <<transducer_message.gain_setting() << std::endl;
      transducer_message.set_angle(angle);
      std::cout << "-Angle: " <<transducer_message.angle() << std::endl;
      transducer_message.set_transmit_duration(transmit_duration);
      std::cout << "-Duration " <<transducer_message.transmit_duration() << std::endl;
      transducer_message.set_sample_period(sample_period);
      std::cout << "-Period: " <<transducer_message.sample_period() << std::endl;
      transducer_message.set_transmit_frequency(transmit_frequency);
      std::cout << "-Freq: " <<transducer_message.transmit_frequency() << std::endl;
      transducer_message.set_number_of_samples(num_points);
      std::cout << "-Nsamples: " <<transducer_message.number_of_samples() << std::endl;
      transducer_message.set_transmit(true);
      std::cout << "-Transmit: " <<transducer_message.transmit() << std::endl;
      transducer_message.updateChecksum();
      sonar.writeMessage(transducer_message);
      // std::cout << settingsData.data() << std::endl;
      ping_message* reply = sonar.waitMessage(2300, 100000);
      ping360_device_data deviceData = *static_cast<const ping360_device_data*>(reply);
      
      int _angle = deviceData.angle();
      std::cout << "Angle: "<< angle << std::endl;
      _data.resize(deviceData.data_length());
      std::cout << deviceData.data_length() << std::endl;
      for (int i = 0; i < num_points; i++) {
          // _data.replace(i, deviceData.data()[i] / 255.0);
          _data[i] = deviceData.data()[i] / 255.0;
          std::cout << _data[i] << std::endl;
      }
    }
    

    return 0;
}