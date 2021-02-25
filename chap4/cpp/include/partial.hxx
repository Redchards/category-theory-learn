#ifndef PARTIAL_HXX
#define PARTIAL_HXX

#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>

#include <keisli.hxx>
#include <monoid.hxx>

namespace
{

template<class T>
union ValueHolder
{
    uint8_t placeholder;
    T x;
};

}

struct nullopt_t{};

constexpr nullopt_t nullopt;

template<class T>
class optional
{
public:
    optional() = default;

    optional(const T& v) 
    : is_valid{ true },
      value_hodler{ .x=v }
    {}

    optional(T&& v) 
    : is_valid{ true },
      value_holder{ .x=std::move(v) }
    {}

    optional(nullopt_t) 
    : optional()
    {}

    bool has_value() const { return is_valid; }
    T value() const 
    { 
        if(is_valid)
        {
            return value_holder.x; 
        }
        
        throw std::runtime_error("Empty optional dereferenced");
    }

private:
    bool is_valid{ false };
    ValueHolder<T> value_holder{ .placeholder=0 };
};

template<class T>
std::ostream& operator<<(std::ostream& os, const optional<T>& x)
{
    if(x.has_value())
    {
        os << x.value();
    }
    else
    {
        os << "nullopt";
    }

    return os;
}

template<>
double mempty<double>{};

template<>
struct mappend<double>
{
    static double apply(const double& lhs, const double& rhs)
    {
        return lhs + rhs;
    }
};

template<Monoid T>
optional<T> mempty<optional<T>>{ mempty<T> };

template<Monoid T>
struct mappend<optional<T>>
{
    static optional<T> apply(const optional<T>& lhs, const optional<T>& rhs)
    {
        if(lhs.has_value() && rhs.has_value())
        {
            return { mappend<T>::apply(lhs.value(), rhs.value()), true };
        }

        return nullopt;
    }
};

namespace partial
{
    auto compose(auto m2, auto m1)
    {
        return [m1, m2](auto x)
        {
            auto p1 = m1(x);
            if(!p1.has_value()) return decltype(m2(p1.value())){};
            auto p2 = m2(p1.value());

            return p2;
        };
    }
}

optional<double> safe_root(double x)
{
    return x >= 0  ? optional<double>{ sqrt(x) } : nullopt;
}

optional<double> safe_reciprocal(double x)
{
    return x != 0 ? optional<double>{ 1 / x } : nullopt;
}

optional<double> safe_root_reciprocal(double x)
{
    return partial::compose(safe_root, safe_reciprocal)(x);
}

#endif // PARTIAL_HXX