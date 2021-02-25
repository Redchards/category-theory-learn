#include <cstdint>
#include <iostream>
#include <string>

// Helper
template<class T>
T not_defined(T);

// Monoid concept
template<class T>
T mempty = not_defined(mempty<T>);

template<class T>
T mappend(const T&, const T&) = delete;

template<class T>
T mappend(T, T) = delete;

template<class M>
concept Monoid = requires(M m)
{
    mempty<M>;
    mappend(m, m);
};

// String monoid
template<>
std::string mempty<std::string> = std::string{};

template<>
std::string mappend<std::string>(const std::string& lhs, const std::string& rhs)
{
    return lhs + rhs;
}

// Bool with op AND monoid
template<>
bool mempty<bool> = true;

template<>
bool mappend<bool>(bool lhs, bool rhs)
{
    return lhs && rhs;
}

// Addition mod 3 monoid
template<>
int8_t mempty<int8_t> = 0;

template<>
int8_t mappend<int8_t>(int8_t lhs, int8_t rhs)
{
    return (lhs + rhs) % 3;
}

int main()
{
    std::cout << "Nothing here..." << std::endl;

    return 0;
}