#pragma once

#include <tuple>
#include <type_traits>

template<typename... Ts>
class TypeVector
{
private:
  template<size_t, size_t, typename...>
  struct atImpl
  {
    using type = void;
  };

  template<size_t Current, size_t I, typename U, typename... Us>
  struct atImpl<Current, I, U, Us...>
  {
    using type = std::conditional_t
    <
      (Current == I),
      U,
      typename atImpl<(Current+1), I, Us...>::type
    >;
  };

public:
  struct empty
  {
    static constexpr bool value = sizeof...(Ts) == 0;
  };

  template<size_t I>
  struct at
  {
    static_assert(I < sizeof...(Ts), "Tried to access element out of bounds.");

    using type = typename atImpl<0, I, Ts...>::type;
  };

  struct front
  {
    static_assert(empty::value, "Tried to access element in empty TypeVector.");

    using type = typename atImpl<0, 0, Ts...>::type;
  };

  struct back
  {
    static_assert(empty::value, "Tried to access element in empty TypeVector.");

    using type = typename atImpl<0, sizeof...(Ts), Ts...>::type;
  };
};
