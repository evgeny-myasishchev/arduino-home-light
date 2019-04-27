#ifndef test_random_h
#define test_random_h

namespace test
{

template <typename T>
T randomNumber(T min, T max)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<T> uni(100, 600);
    return uni(rng);
}

} // namespace test

#endif