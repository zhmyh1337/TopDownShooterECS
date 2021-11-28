#pragma once
#include <type_traits>
#include <vector>
template<typename T>
struct is_vector
{
    static constexpr bool value = false;
};

template<template<typename...> class C, typename U>
struct is_vector<C<U>>
{
  static constexpr bool value = std::is_same<C<U>,std::vector<U>>::value;
};