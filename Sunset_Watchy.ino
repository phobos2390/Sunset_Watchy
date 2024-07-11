#include "Sunset_watchface.h"
#include "settings.h"
#include <WiFi.h>
//#include <string>

//#define MAX_CHARACTER_LENGTH 128

extern RTC_DATA_ATTR bool WIFI_CONFIGURED;

//Cli_Terminal terminal (MAX_CHARACTER_LENGTH);
Sunset_watchface watchface(settings);

void setup() 
{
  // put your setup code here, to run once:
  watchface.initPositions();
  watchface.init();

  /*/
  Serial.begin(9600);
  Serial.print(">");
  terminal.commands[0] = Command("Search Available Wifi", [](String str) -> void 
  { 
    uint8_t res = WiFi.scanNetworks();
    if (res == WIFI_SCAN_FAILED)
    {
      Serial.println("WiFi Scanning Failed");
    }
    else if (res == 0)
    {
      Serial.println("No Wifi Networks Found");
    }
    else if (res > 0)
    {
      Serial.print("Found ");
      Serial.print(res);
      Serial.println(" Networks");
      for(uint8_t i = 0; i < res; i++)
      {
        Serial.print("  ");
        Serial.print(i+1);
        Serial.print(". ");
        Serial.print(WiFi.SSID(i));
      }
    }
  });
  terminal.commands[1] = Command("Set Wifi Credentials", [](String str) -> void 
  { 
    Serial.println("Input SSID Then Press ENTER: ");
    String SSID = Serial.readStringUntil((char)10);
    Serial.println("Input Password Then Press ENTER: ");
    String Password = Serial.readStringUntil((char)10);
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID,Password);
    Serial.print("Connecting to WiFi ..");
    for (uint8_t i = 0; i < 10; i++)
    {
      if(WiFi.status() != WL_CONNECTED) 
      {
        Serial.print('.');
        delay(1000);
      }
      else
      {
        break;
      }
    }
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.print("Failed to connect to WiFi");
    }
    else
    {
      Serial.println(WiFi.localIP());
      WIFI_CONFIGURED = true;
    }
  });
  terminal.commands[2] = Command("Help", [](String str) -> void 
  {
    Serial.println("Search Available Wifi: Searches for Wifi Networks Networks");
    Serial.println("Set Wifi Credentials: Sets SSID and Password Credentials for Wifi");
    Serial.println("Help: Shows command options");
  });
  //*/
}

void loop() 
{
  //terminal.cli_cal();
}
