#include<string>

template<class T>
T not_defined(T);

template<class T>
T mempty = not_defined(mempty<T>);

template<class T>
T mappend(const T&, const T&) = delete;

template<class M>
concept Monoid = requires(M m)
{
    mempty<M>;
    mappend(m, m);
};

template<>
std::string mempty<std::string> = std::string{};

template<>
std::string mappend<std::string>(const std::string& lhs, const std::string& rhs)
{
    return lhs + rhs;
}

int main()
{
    return 0;
}