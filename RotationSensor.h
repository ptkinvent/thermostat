/**
 * @author Prateek Sahay
 * @date 2/2/21
 */

class RotationSensor
{
public:
    /**
     * Plug potentiometer into an analog pin of Grove shield.
     */
    RotationSensor(int pin) : _pin(pin) {};

    /**
     * Returns position 0-1
     */
    float sense()
    {
        int val = analogRead(_pin);
        float ratio = (float) val / 1024.0;
        return ratio;
    }

private:
    int _pin;
};
