#pragma once

namespace ecs
{
  class Singleton
  {

  };
  template<typename T>
  struct is_singleton
  {
    static constexpr bool value = std::is_base_of<Singleton, T>::value;
  };

  template<typename T>
  T &get_singleton()
  {
    static_assert(is_singleton<T>::value);//allow only ecs singleton
    static T instance;
    return instance;
  }
  typedef void *(*GetSingleton)();
}