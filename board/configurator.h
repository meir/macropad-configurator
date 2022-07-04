
#ifndef Configurator_h
#define Configurator_h

#include <Preferences.h>
#include <ArduinoJson.h>

class Configurator {
  private:
    bool _started;

    Preferences _preferences;

  public:
    Configurator();
    DynamicJsonDocument getConfig();
    void handleClient();
};

#endif
