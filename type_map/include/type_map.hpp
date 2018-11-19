/* Map of types.
 * @file
 * @date 2018-08-25
 * @author Anonymous
 */

#ifndef __TYPE_MAP_HPP__
#define __TYPE_MAP_HPP__

#include <array>
#include <tuple>

namespace detail
{
    template<class T, class Tuple>
    struct type_to_index;

    template<class T, class... Ts>
    struct type_to_index<T, std::tuple<T, Ts...>>
    {
        constexpr static size_t v = 0;
    };

    template<class T, class U, class... Ts>
    struct type_to_index<T, std::tuple<U, Ts...>>
    {
        constexpr static size_t v = 1 + type_to_index<T, std::tuple<Ts...>>::v;
    };
}

//? What is wrong with ``*this[i]``?
//{
template<class U, class... Us>
class type_map: public std::array<U, sizeof...(Us)>
{
public:
    using types = std::tuple<Us...>;

    template<class T>
    U& as()
    {
        return (*this)[detail::type_to_index<T, types>().v];
    }
};
//}

namespace std
{
    template<typename T, class TypeMap>
    auto& get(TypeMap& tm)
    {
        //{ How to call ``as``?
        return tm.template as<T>();
        //}
    }
}

#endif // __TYPE_MAP_HPP__
