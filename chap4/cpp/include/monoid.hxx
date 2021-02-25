#ifndef MONOID_HXX
#define MONOID_HXX

// Helper
template<class T>
T not_defined(T);

// Monoid concept
template<class T>
T mempty = not_defined(mempty<T>);

template<class T>
struct mappend
{
    static T apply(const T&, const T&) = delete;
};

template<class M>
concept Monoid = requires(M m)
{
    mempty<M>;
    mappend<M>::apply(m, m);
};

#endif // MONOID_HXX
