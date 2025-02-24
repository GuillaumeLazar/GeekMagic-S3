#include <Arduino.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include "time.h"

// WiFi
const char* wifi_ssid = "REDACTED_WIFI_SSID"; 
const char* wifi_password = "REDACTED_WIFI_PASSWORD";

// NTP
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600 * 1;
const int   daylightOffset_sec = 3600 * 0;

TFT_eSPI tft;

void setup(){
    Serial.begin(115200);
    Serial.println("Hello GeekMagic S3");
     
    tft.begin();
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
    tft.setTextSize(3);
    tft.drawString("Connecting...", 0,50);
    Serial.println("Connecting...");
    WiFi.begin(wifi_ssid, wifi_password);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(100);
      }

    tft.fillScreen(TFT_BLACK);

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());

    char ipAddressStr[32];
    String ipAddress = WiFi.localIP().toString();
    ipAddress.toCharArray(ipAddressStr, ipAddress.length() + 1);
    tft.setTextSize(2);
    tft.drawString(ipAddressStr, 10,100);

    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    tft.setTextSize(4);
}

void loop(){
    char timeStr[16];
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("getLocalTime failed!");
    } else {
        Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
        sprintf(timeStr, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    }

    tft.drawString(timeStr, 20,150);

    delay(1000);
}
