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

TEST(vector, move)
{
    int values[] = {1, 2, 3, 4};

    pstd::vector<int> v;
    v = pstd::vector<int>(values);
    ASSERT_EQ(4, v.size());

    for (int i = 0; i < v.size(); i++)
    {
        ASSERT_EQ(values[i], v[i]);
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

class testClass
{
public:
    pstd::vector<int> values;

    testClass(pstd::vector<int> v)
    {
        values = v;
    }
};

TEST(vector, classCtorParam)
{
    pstd::vector<int> v = createVector(4513, 8502);
    testClass tc(v);

    ASSERT_EQ(2, tc.values.size());
    ASSERT_EQ(4513, tc.values[0]);
    ASSERT_EQ(8502, tc.values[1]);
}

TEST(vector, empty)
{
    pstd::vector<int> v;
    ASSERT_EQ(0, v.size());
}

} // namespace
