//
// Author:
//   Chris03.com
//
// Purpose:
//   Accept OTA (over the air) updates.
//
// Hardware:
//   ESP
//

#include <Arduino.h>
#include "wifi.h"
#include "web.h"

void setup()
{
  Serial.begin(115200);
  delay(500);
  setupWifi();
  setupWeb();
}

void loop()
{
  handleOTA();
  handleWeb();
}
