#include <Arduino.h>
#include <LittleFS.h>
#include "my_debug.h"
#include <TFT_eSPI.h>
#include "btn.h"

TFT_eSPI tft;
void set_tft_brt(int brt);
#define LCD_BL_PWM_CHANNEL 0
void set_tft_brt(int brt){
    //digitalWrite(TFT_BL, brt);
    ledcSetup(LCD_BL_PWM_CHANNEL, 5000, 8);
    ledcAttachPin(TFT_BL, LCD_BL_PWM_CHANNEL);
    ledcWrite(LCD_BL_PWM_CHANNEL, brt);
}

/////////////////////////////////////////////////////////////////
void setup(){
    Serial.begin(115200);
    DBG_PTN("Hello GeekMagic S3");
     
    tft.begin();
    set_tft_brt(100);
    tft.fillScreen(TFT_GREEN);
    tft.setTextColor(TFT_BLACK, TFT_RED);
    tft.setTextSize(4);
    tft.drawString("GeekMagic", 10,100);
    btn_init();
}

void loop(){
    btn_update();
}