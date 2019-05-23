#include <ArduinoUnit.h>
#include <pstd.h>

test(psdt_vector)
{
    int values[4] = {1, 2, 3, 4};

    pstd::vector<int> v(values);
    assertEqual(4, v.size());

    for (int i = 0; i < v.size(); i++)
    {
        assertEqual(values[i], v[i]);
    }
}