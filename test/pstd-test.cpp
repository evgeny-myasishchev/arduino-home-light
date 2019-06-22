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

    pstd::vector<int> createVector(const int val1, const int val2)
    {
        int values[] = {val1, val2};
        return pstd::vector<int>(values);
    }

    TEST(vector, copyExternal)
    {
        pstd::vector<int> v = createVector(12, 432);
        ASSERT_EQ(2, v.size());
        ASSERT_EQ(12, v[0]);
        ASSERT_EQ(432, v[1]);
    }

    TEST(vector, empty)
    {
        pstd::vector<int> v;
        ASSERT_EQ(0, v.size());
    }
} // namespace
