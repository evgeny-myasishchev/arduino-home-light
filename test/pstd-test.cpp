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

TEST(vector, moveAssign)
{
    int values[] = {23, 431, 1421, 55323};

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
    auto v = pstd::vector<int>(values);
    return v;
}

TEST(vector, moveCreate)
{
    pstd::vector<int> v = createVector(12, 432);
    ASSERT_EQ(2, v.size());
    ASSERT_EQ(12, v[0]);
    ASSERT_EQ(432, v[1]);
}

TEST(vector, copyCreate)
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

TEST(vector, copyAssign)
{
    pstd::vector<int> v = createVector(4513, 8502);
    pstd::vector<int> copy;
    copy = v;

    ASSERT_EQ(2, copy.size());
    ASSERT_EQ(4513, copy[0]);
    ASSERT_EQ(8502, copy[1]);
}

TEST(vector, empty)
{
    pstd::vector<int> v;
    ASSERT_EQ(0, v.size());
}

} // namespace
