#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "display.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 oled(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1
);

void displayInit()
{
    if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("OLED not found!"));
        while(1);
             // Don't proceed, loop forever
    }

    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextColor(SSD1306_WHITE);
    oled.setCursor(0, 0);
    oled.println(F("GarryBot Initialized"));
    oled.display();
}

void displayShow(
    float angle,
    float kp,
    float ki,
    float kd,
    int pidOutput,
    int leftPWM,
    int rightPWM
)
{
  oled.clearDisplay();

    oled.setTextSize(1);

    oled.setCursor(0, 0);
    oled.print("Angle: ");
    oled.print(angle, 2);

    oled.setCursor(0, 15);
    oled.print("Kp: ");
    oled.print(kp, 2);

    oled.setCursor(64, 15);
    oled.print("Ki: ");
    oled.print(ki, 2);

    oled.setCursor(0, 30);
    oled.print("Kd: ");
    oled.print(kd, 2);

    oled.setCursor(0, 45);
    oled.print("PID: ");
    oled.print(pidOutput);

    oled.setCursor(64, 45);
    oled.print("Left: ");
    oled.print(leftPWM);

    oled.setCursor(0, 55);
    oled.print("Right: ");
    oled.print(rightPWM);

    oled.display();
}