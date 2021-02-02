/**
 * @author Prateek Sahay
 * @date 2/2/21
 */

class TemperatureSensor
{
public:
    /**
     * Plug temperature sensor into an analog pin of Grove shield.
     */
    TemperatureSensor(int pin) : _pin(pin) {};

    /**
     * Returns temperature in Fahrenheit.
     */
    float sense()
    {
        int val = analogRead(_pin);
        float resistance = (float)(1023-val)*10000/val;
        float temperature_c = 1/(log(resistance/10000)/B+1/298.15)-273.15;
        float temperature_f = (temperature_c*1.8)+32;
        float temperature = temperature_f;
        return temperature;
    }

private:
    int _pin;
    const int B = 3975;
};
