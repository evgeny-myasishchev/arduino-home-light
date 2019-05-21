#include <gtest/gtest.h>
#include <pstd.h>

namespace
{
    TEST(vector, ops)
    {
        int values[4] = {1, 2, 3, 4};

        pstd::vector<int> v(values);
        ASSERT_EQ(4, v.size());

        for (int i = 0; i < v.size(); i++)
        {
            ASSERT_EQ(values[i], v[i]);
        }
    }

    TEST(vector, init_var_args)
    {
        int values[4] = {1, 2, 3, 4};

        pstd::vector<int> v(4, 1, 2, 3, 4);
        ASSERT_EQ(4, v.size());

        for (int i = 0; i < v.size(); i++)
        {
            ASSERT_EQ(values[i], v[i]);
        }
    }
} // namespace
