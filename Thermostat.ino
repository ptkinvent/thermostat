/*
 * Maintains set temperature and displays it to LCD screen.
 *
 * Requires Seeed Grove shield. Attach temperature sensor on A0,
 * potentiometer on A1, light sensor on A2, LCD screen on any I2C port
 */

#include "rgb_lcd.h"
#include "TemperatureSensor.h"
#include "RotationSensor.h"
#include "LightSensor.h"
#include "CircularBuffer.h"
#include "Relay.h"



rgb_lcd lcd;
TemperatureSensor temperatureSensor(A0);
RotationSensor rotationSensor(A1, RotationSensor::INCREMENT_CW);
LightSensor lightSensor(A2);
CircularBuffer<float> circularBuffer(100);
Relay relay(13);



void setup()
{
    Serial.begin(9600);
    
    // Set up the LCD screen's number of columns and rows:
    lcd.begin(16, 2);
}



void loop()
{
    circularBuffer.push_back(temperatureSensor.sense());
    float currTemperature = circularBuffer.getMean();
    float setPoint = getSetpoint();
    float deadbandSize = 2.0;
    float minThreshold = setPoint - deadbandSize/2;
    float maxThreshold = setPoint + deadbandSize/2;
    float minLightLevel = 0;

    float lightLevel = lightSensor.sense();
    if (lightLevel < minLightLevel)
    {
        lightLevel = minLightLevel;
    }

    if (minThreshold < currTemperature && currTemperature < maxThreshold)
    {
        // Do nothing if currTemperature is very close to setPoint. This prevents rapid
        // flipping of the relay if currTemperature fluctuates around setPoint.
        lcd.setRGB(255*lightLevel, 0, 255*lightLevel);
    }
    else if (currTemperature <= minThreshold)
    {
        lcd.setRGB(255*lightLevel, 0, 0);
        relay.on();
    }
    else
    {
        lcd.setRGB(0, 0, 255*lightLevel);
        relay.off();
    }

    lcd.setCursor(0, 0);
    lcd.print("Current: ");
    lcd.print(currTemperature);
    lcd.print(" F");

    lcd.setCursor(0, 1);
    lcd.print("Desired: ");
    lcd.print(setPoint);
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
