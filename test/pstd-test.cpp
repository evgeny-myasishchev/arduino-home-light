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

    TEST(vector, copy)
    {
        int values[] = {1, 2, 3, 4};

        pstd::vector<int> v(values);
        const auto copy = v;
        ASSERT_EQ(4, copy.size());

        for (int i = 0; i < copy.size(); i++)
        {
            ASSERT_EQ(values[i], copy[i]);
        }
    }
} // namespace
