#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft;

void setup(){
    Serial.begin(115200);
    Serial.println("Hello World from GeekMagic S3");
     
    tft.begin();
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_SKYBLUE, TFT_BLACK);
    tft.setTextSize(4);
    tft.drawString("Hello", 55,50);
    tft.drawString("World!", 50,100);
}

void loop(){
    delay(1000);
}