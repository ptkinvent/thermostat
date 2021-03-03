/**
 * @author Prateek Sahay
 * @date 2/2/21
 */

class RotationSensor
{
public:
    enum Direction
    {
        INCREMENT_CW,
        INCREMENT_CCW
    };

    /**
     * Plug potentiometer into an analog pin of Grove shield.
     */
    RotationSensor(int pin, Direction dir) : _pin(pin), _dir(dir) {};

    /**
     * Returns position 0-1
     */
    float sense()
    {
        int val = analogRead(_pin);
        float ratio = (float) val / 1024.0;
        return (_dir == INCREMENT_CCW) ? ratio : 1 - ratio;
    }

private:
    int _pin;
    Direction _dir;
};
