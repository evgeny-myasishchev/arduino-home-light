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

    // TODO: Failing
    // pstd::vector<int> v2(4, 1, 2, 3, 4);
    // assertEqual(4, v2.size());

    // for (int i = 0; i < v2.size(); i++)
    // {
    //     assertEqual(values[i], v2[i]);
    // }
}