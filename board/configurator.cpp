
#include "configurator.h"
#include "graphics.h"
#include "Adafruit_TinyUSB.h"

#include <Arduino.h>
#include <WString.h>

#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

WebServer _server(80);
DynamicJsonDocument _config(1024);

const char* ssid = "ssid";
const char* pass = "pass";

void http_getConfig() {
  _server.send(200, "text/plain", "hiya!");
}

void http_saveConfig() {
  if(!_server.hasArg("plain")) {
    _server.send(400, "application/json", "{\"error\":{\"code\":1,\"message\":\"no body given\"}}");
    return;
  }
  String body = _server.arg("plain");
  DeserializationError err = deserializeJson(_config, body);
  if (err) {
    _server.send(400, "application/json", "{\"error\":{\"code\":2,\"message\":\"" + String(err.f_str()) + "\"}}");
    return;
  }
  _server.send(200, "application/json", body);
}

void http_redirect() {
  _server.send(404, "text/plain", "Not Found");
}

void http_root() {
  _server.send(200, "text/plain", "hiya!");
}

Configurator::Configurator() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  delay(10000);
  _started = false;
}

DynamicJsonDocument Configurator::getConfig() {
  return _config;
}

int attempt = 0;

void Configurator::handleClient() {
  if(WiFi.status() != WL_CONNECTED) {
    gfx_println("");
    gfx_println("Connecting to " + String(ssid));
    int n = WiFi.scanNetworks();
    gfx_println("Status: " + String(WiFi.status(), DEC));
    gfx_println("Attempt: " + String(attempt, DEC));
    gfx_println("Networks found: " + String(n, DEC));
    for (int i = 0; i < n; i++) {
      gfx_println(String(i, DEC) + ": " + String(WiFi.SSID(i)));
    }
    if (WiFi.status() == WL_DISCONNECTED) {
      WiFi.begin(ssid, pass);
      attempt++;
      delay(10000);
    }
    return;
  }

  if(_started == false) {
    tft().fillScreen(ST77XX_BLACK);
    _server.begin();
    _server.on("/", http_root);
    _server.on("/config/get", http_getConfig);
    _server.on("/config/save", http_saveConfig);
    _server.onNotFound(http_redirect);
    _started = true;
  }

  gfx_println("");
  gfx_println(WiFi.localIP().toString());

  _server.handleClient();
}
