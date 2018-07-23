class MutableValue
{
private:
    volatile int prevValue;
    volatile int nextValue;
public:
    MutableValue(int);
    int value();
    void setValue(int);
    void apply();
    bool hasChanged();
};