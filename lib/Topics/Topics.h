#pragma once
#include <Arduino.h>

namespace Topics {
  const String& base();
  const String& availability();
  const String& tempState();
  const String& tempDiscovery();
  const String& humState();
  const String& humDiscovery();

    const String& servoCommand();
  const String& servoState();    
  const String& servoDiscovery();
}
