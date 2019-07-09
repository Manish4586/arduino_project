/*  
 *  Arduino Projects By Manish4586
 *  Source Code : https://GitHub.com/Manish4586
 *  Telegram Contact : https://t.me/Manish4586
 *  Author : Manish4586 <manish.n.manish45@gmail.com>
 *  Status : Debugging
*/

/*
 *  This driver is for ssd1306 I.C based Monochrome panels. 
 *  Currently this driver is specified for i2c panels. 
 */
 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    LED_BUILTIN 
#define PANEL         0x3D

void setup() {
    Serial.begin(19200);

#if defined(OLED_RESET)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#else
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
#endif

#if defined(PANEL)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D))
#else
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
#endif
{
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Hello, world!");
  display.display();
  delay(2000);  
}

void loop() {}

