/**
 * @author Prateek Sahay
 * @date 2/2/21
 */

template <typename T>
class CircularBuffer
{
public:
    CircularBuffer(int size) : _size(size)
    {
        _array = (T*) calloc(_size, sizeof(T));
        clear();
    }

    void clear()
    {
        memset(_array, 0, sizeof(T)*_size);
    }

    void push_back(T element)
    {
        _array[_last] = element;
        _last = (_last + 1) % _size;
        _numRealElements = min(_numRealElements++, _size);
    }

    float getMean()
    {
        float sum = 0;
        for (int i=0; i<_numRealElements; i++)
        {
            sum += _array[i];
        }
        return sum / _numRealElements;
    }

private:
    int _last;            // Index of last item in the array
    T* _array;
    int _size;
    int _numRealElements; // Keeps track of how many elements have actually been populated so far
};
