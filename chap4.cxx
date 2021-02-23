#include <algorithm>
#include <cctype>
#include <cstring>
#include <string>
#include <utility>

namespace ranges
{
    template<class Container, class OutputIt, class F>
    constexpr void transform(const Container& c, OutputIt output_it, const F& f)
    {
        std::transform(std::begin(c), std::end(c), output_it, f);
    }
}

template<class T>
using Writer = std::pair<T, std::string>;

auto to_upper(const std::string& s)
-> Writer<std::string>
{
    std::string new_str{};

    ranges::transform(s, std::back_inserter(new_str), toupper);

    return { new_str, "To upper " };
}

// Without utilizing the concept of the Keisli category
namespace bad_way
{

}

int main()
{
    return 0;
}