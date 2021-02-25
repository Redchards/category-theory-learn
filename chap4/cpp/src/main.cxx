#include <iostream>

#include <keisli.hxx>
#include <partial.hxx>

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

    // Challenge section
    std::cout << "CHALLENGE SECTION" << std::endl;

    std::cout << "sqrt(1/x) for x = 5 => " << safe_root_reciprocal(5) << std::endl;
    std::cout << "sqrt(1/x) for x = 1 => " << safe_root_reciprocal(1) << std::endl;
    std::cout << "sqrt(1/x) for x = 0 => " << safe_root_reciprocal(0) << std::endl;
    std::cout << "sqrt(1/x) for x = -5 => " << safe_root_reciprocal(-5) << std::endl;

    return 0;
}