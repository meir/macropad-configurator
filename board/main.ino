#include "Adafruit_TinyUSB.h"
#include "matrix.h"
#include "graphics.h"
#include "configurator.h"

#include <vector>
#include <Encoder.h>
#include <Arduino.h>
#include <WString.h>
#include <ArduinoJson.h>

uint8_t const desc_hid_report[] =
{
  TUD_HID_REPORT_DESC_KEYBOARD()
};

Adafruit_USBD_HID usb_hid(desc_hid_report, sizeof(desc_hid_report), HID_ITF_PROTOCOL_KEYBOARD, 2, false);

std::vector<int> columns { A0, A1 };
std::vector<int> rows { A2, A3, A4 };

Encoder encoder(12, 13);
Matrix matrix(columns, rows);
Configurator configurator;

void setup()
{
  usb_hid.begin();

  gfx_init();

  matrix.Init();

  // wait until device mounted
  while( !TinyUSBDevice.mounted() ) delay(1);
}


void loop()
{
  // poll gpio once each 2 ms
  delay(2);

  if(TinyUSBDevice.suspended()) {
    TinyUSBDevice.remoteWakeup();
  }
  if(!usb_hid.ready()) return;

  gfx_reset();

  matrix.Scan();
  int value = encoder.read();

  configurator.handleClient();

  gfx_println(String(value, DEC));

  int state = matrix.GetState(0);

  if(matrix.GetState(0) == 1) {
    uint8_t keycode[] = {0x00F7};
    usb_hid.keyboardReport(0, 0, keycode);
  }else{
    usb_hid.keyboardRelease(0);
  }
}
