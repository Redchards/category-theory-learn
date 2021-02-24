#ifndef KEISLI_HXX
#define KEISLI_HXX

#include <algorithm>
#include <cctype>
#include <concepts>
#include <cstring>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include "monoid.hxx"

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

template<class T>
auto identity(T x)
-> Writer<T>
{
    return { x, {} };
}

auto to_upper(const std::string& s)
-> Writer<std::string>
{
    std::string new_str{};

    ranges::transform(s, std::back_inserter(new_str), toupper);

    return { new_str, "[To upper]" };
}

auto to_lower(const std::string& s)
-> Writer<std::string>
{
    std::string new_str{};

    ranges::transform(s, std::back_inserter(new_str), tolower);

    return { new_str, "[To lower]" };
}

auto split_words(const std::string& s)
-> Writer<std::vector<std::string>>
{
    std::vector<std::string> result{""};

    for(auto c : s)
    {
        if(std::isspace(c))
        {
            result.emplace_back();
        }
        else
        {
            result.back().push_back(c);
        }
    }

    return { result, "[Split words]" };
}

auto capitalize(const std::string& s)
-> Writer<std::string>
{
    std::string res = s;

    if(!s.empty())
    {
        res[0] = std::toupper(res[0]);
    }

    return { res, "[Capitalize]" };
}

auto capitalize_words(const std::vector<std::string>& v)
-> Writer<std::vector<std::string>>
{
    std::vector<std::string> res;

    ranges::transform(v, std::back_inserter(res), [](const auto& s) { return capitalize(s).first; });

    return { res, "[Capitalize words]" };
}

// Without utilizing the concept of the Keisli category
namespace bad_way
{
    Writer<std::vector<std::string>> process(const std::string& s)
    {
        auto p1 = to_upper(s);
        auto p2 = split_words(p1.first);

        return { p2.first, p1.second + p2.second };
    }
}

// Better way
namespace neat
{
    auto compose(auto m2, auto m1)
    {
        return [m1, m2](auto x)
        {
            auto p1 = m1(x);
            auto p2 = m2(p1.first);

            return std::make_pair(p2.first, p1.second + p2.second);
        };
    }
}

// For any monoid as the second member of the pair
template<>
std::string mempty<std::string>{};

template<>
std::string mappend<std::string>(const std::string& lhs, const std::string& rhs)
{
    return lhs + rhs;
}

namespace monoid
{
    auto compose(auto m2, auto m1)
    {
        return [m1, m2](auto x)
        {
            auto p1 = m1(x);
            auto p2 = m2(p1.first);

            return std::make_pair(p2.first, mappend(p1.second, p2.second));
        };
    }
}

auto process(const std::string& s)
-> Writer<std::vector<std::string>>
{
    return monoid::compose(split_words, to_upper)(s);
}

auto process2(const std::string& s)
-> Writer<std::vector<std::string>>
{
    return monoid::compose(split_words, to_lower)(s);
}

#endif // KEISLI_HXX