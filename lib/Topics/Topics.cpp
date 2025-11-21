#include "Topics.h"
#include "ProjectConfig.h"

namespace Topics {
  const String& base() {
    static String t = ProjectConfig::baseTopic(); // ex "desk3/"
    return t;
  }
  
  // SHT31 topics
  const String& availability() {
    static String t = base() + "status";
    return t;
  }

  const String& tempState() {
    static String t = base() + "sensor/sht31_temperature";
    return t;
  }

  const String& tempDiscovery() {
    static String t =
      "homeassistant/sensor/" + String(ProjectConfig::deviceName()) +
      "_sht31_temperature/config";
    return t;
  }

  const String& humState() {
    static String t = base() + "sensor/sht31_humidity";
    return t;
  }

  const String& humDiscovery() {
    static String t =
      "homeassistant/sensor/" + String(ProjectConfig::deviceName()) +
      "_sht31_humidity/config";
    return t;
  }


  // Servo topics
  const String& servoCommand() {
    static String t = base() + "servo/angle/set";
    return t;
  }

  const String& servoState() {
    static String t = base() + "servo/angle/state";
    return t;
  }

  const String& servoDiscovery() {
    static String t =
      "homeassistant/number/" +
      String(ProjectConfig::deviceName()) +
      "_servo_angle/config";
    return t;
  }

}
