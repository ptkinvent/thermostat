/*
 * Detects temperature and displays it to LCD screen.
 * Requires Seeed Grove shield. Attach Temp sensor on A0, LCD on any I2C port
 */

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
const int colorR = 0;
const int colorG = 0;
const int colorB = 50;
const int pinTemperature = A0;     // Pin of temperature sensor
const int B = 3975;                // B value of the thermistor
const float temperatureBias = 0.0;
const int pinPotentiometer = A1;   // Pin of potentiometer

void setup()
{
    Serial.begin(9600);
    
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    delay(1000);
}

void loop()
{
    float temperature = getTemperature();
    float setPoint = getSetpoint();

    if (temperature < setPoint)
    {
        lcd.setRGB(255, 0, 0);
    }
    else
    {
        lcd.setRGB(0, 0, 255);
    }

    lcd.setCursor(0, 0);
    lcd.print("Desired: ");
    lcd.print(setPoint);
    lcd.print(" F");

    lcd.setCursor(0, 1);
    lcd.print("Current: ");
    lcd.print(temperature);
    lcd.print(" F");
    delay(100);
}

/**
 * Gets the current temperature and returns it in Fahrenheit
 */
float getTemperature()
{
    int val = analogRead(pinTemperature);
    float resistance = (float)(1023-val)*10000/val;
    float temperature_c = 1/(log(resistance/10000)/B+1/298.15)-273.15;
    float temperature_f = (temperature_c*1.8)+32;
    float temperature = temperature_f + temperatureBias;
    return temperature;
}

/**
 * Gets the current potentiometer position and returns it as a percentage 0-1
 */
float getPotentiometer()
{
    int val = analogRead(pinPotentiometer);
    float ratio = (float) val / 1024.0;
    return ratio;
}

/**
 * Reads the value from the potentiometer and returns a temperature setpoint
 * between 60-80 deg F
 */
float getSetpoint()
{
    float minTemp = 60;
    float maxTemp = 90;
    float pot = getPotentiometer();
    return round(minTemp + (maxTemp - minTemp) * pot);
}
