# Arduino Thermostat #

Arduino project to control the temperature in my room using a thermostat and relay.

## Hardware ##

 1. Connect the Grove Shield to Arduino Uno.
 2. Attach RGB LCD screen to any I2C port on the shield.
 3. Attach temperature sensor to A0 on the shield.
 4. Attach potentiometer to A1 on the shield
 5. Connect positive terminal of relay to port 13 and negative terminal of relay to ground.

## Usage ##
Set the desired temperature using the potentiometer. The readout is displayed on the LCD screen.

Note there is a deadzone of +/- 1 degree on either side of the desired temperature to prevent fast flipping of the relay when the current temperature is close to the desired temperature.
