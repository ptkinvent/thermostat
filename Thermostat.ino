/*
 * Detects temperature and displays it to LCD screen.
 * Requires Seeed Grove shield. Attach Temp sensor on A0, LCD on any I2C port
 */

#include "rgb_lcd.h"
#include "TemperatureSensor.h"
#include "RotationSensor.h"
#include "CircularBuffer.h"



rgb_lcd lcd;
TemperatureSensor temperatureSensor(A0);
RotationSensor rotationSensor(A1);
CircularBuffer<float> circularBuffer(100);



void setup()
{
    Serial.begin(9600);
    
    // Set up the LCD screen's number of columns and rows:
    lcd.begin(16, 2);
    
    delay(100);
}



void loop()
{
    circularBuffer.push_back(temperatureSensor.sense());
    float temperature = circularBuffer.getMean();
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
 * Reads the value from the potentiometer and returns a temperature setpoint
 * between 60-80 deg F
 */
float getSetpoint()
{
    float minTemp = 60;
    float maxTemp = 90;
    float pot = rotationSensor.sense();
    return round(minTemp + (maxTemp - minTemp) * pot);
}
