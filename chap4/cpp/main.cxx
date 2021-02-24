#include <iostream>

#include "keisli.hxx"

int main()
{
    // Simple compose
    auto p = process("Hello World!");

    std::cout << "Displaying processed string : " << std::endl;
    for(const auto& w : p.first)
    {
        std::cout << w << std::endl;
    }

    std::cout << "Logging..." << std::endl;
    std::cout << p.second << std::endl;

    // Compose the composition
    p = monoid::compose(capitalize_words, process2)("hello world");

    std::cout << "Displaying processed string : " << std::endl;
    for(const auto& w : p.first)
    {
        std::cout << w << std::endl;
    }

    std::cout << "Logging..." << std::endl;
    std::cout << p.second << std::endl;

    std::cout << std::boolalpha;

    std::cout << is_even(4) << std::endl;
    std::cout << is_even(5) << std::endl;
    std::cout << is_odd(4) << std::endl;
    std::cout << is_odd(5) << std::endl;

    return 0;
}