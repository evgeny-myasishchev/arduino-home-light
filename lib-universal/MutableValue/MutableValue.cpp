#include <MutableValue.h>

MutableValue::MutableValue(int val)
{
    prevValue = val;
    nextValue = val;
}

int MutableValue::value() {
    return nextValue;
}

void MutableValue::setValue(int val)
{
    nextValue = val;
}

void MutableValue::apply() {
    prevValue = nextValue;
}

bool MutableValue::hasChanged() {
    return prevValue != nextValue;
}