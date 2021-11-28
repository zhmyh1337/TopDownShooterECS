#pragma once
#include <array>
#include <string_view>
#include "is_vector.h"

#include "glm/glm.hpp"
#include "../base_types.h"
#include "entity_id.h"
#include <type_traits>

template <std::string_view const&... Strs>
struct join
{
    // Join all strings into a single std::array of chars
    static constexpr auto impl() noexcept
    {
        constexpr std::size_t len = (Strs.size() + ... + 0);
        std::array<char, len + 1> arr{};
        auto append = [i = 0, &arr](auto const& s) mutable {
            for (auto c : s) arr[i++] = c;
        };
        (append(Strs), ...);
        arr[len] = 0;
        return arr;
    }
    // Give the joined string static storage
    static constexpr auto arr = impl();
    // View as a std::string_view
    static constexpr std::string_view value {arr.data(), arr.size() - 1};
};
// Helper to get the value out
template <std::string_view const&... Strs>
static constexpr auto join_v = join<Strs...>::value;


template <typename T>
struct nameOf;

template <typename T>
static constexpr std::enable_if_t<!is_vector<T>::value, std::string_view> dirty_impl() noexcept
{
  const char *f = __PRETTY_FUNCTION__;
  while(*f && *f != '[')
    ++f;
  const char *str = f + 5;
  while(*f && *f != ']')
    ++f;
  size_t n = f - str;
  return std::string_view(str, n);
}

template <typename T>
struct dirtyNameOf
{
  static constexpr std::string_view value = dirty_impl<T>();
};

static inline constexpr std::string_view _word_end = "";
template <typename T>
static constexpr std::enable_if_t<!is_vector<T>::value, std::string_view> impl() noexcept
{
  return join_v<dirtyNameOf<T>::value, _word_end>;
}

static inline constexpr std::string_view _vec_begin = "vector<";
static inline constexpr std::string_view _vec_end = ">";
template <typename T>
static constexpr std::enable_if_t<is_vector<T>::value, std::string_view> impl() noexcept
{
  return join_v<_vec_begin, nameOf<typename T::value_type>::value, _vec_end>;
}

#define MACRO(NAME, T) \
template<> constexpr std::string_view impl<T>() noexcept\
{ return std::string_view(#NAME); }


BASE_TYPES

#undef MACRO


template <typename T>
struct nameOf
{
  static constexpr std::string_view value = impl<T>();
};
