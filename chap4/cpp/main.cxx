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

    return 0;
}