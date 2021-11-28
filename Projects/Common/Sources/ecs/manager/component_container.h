#pragma once
#include <sys/types.h>
#include <unordered_map>
#include <assert.h>
#include "type_description.h"
#include <algorithm>
namespace ecs
{
  constexpr int binSize = 8;
  class ComponentContainer
  {
    std::vector<void*> data;
  public:
    string_hash typeHash, typeNameHash;
    int count, capacity, sizeOf;
    ComponentContainer();
    ComponentContainer(string_hash type_hash, string_hash type_name_hash, int capacity, int sizeOf);
    template<typename T>
    T* get_component(int i)
    {
      if (0 <= i && i < count)
      {
        int j = i / binSize;
        i %= binSize;
        return (T*)((char*)data[j] + i * sizeOf);
      }
      return nullptr;
    }
    template<typename T>
    const T* get_component(int i) const
    {
      if (0 <= i && i < count)
      {
        int j = i / binSize;
        i %= binSize;
        return (T*)((char*)data[j] + i * sizeOf);
      }
      return nullptr;
    }
    void destroy_component(int i, bool without_copy);
    void add_component(void *component_data);
    void* add_component();
    void copy_components(const ComponentContainer &other);
    ~ComponentContainer();
  };
}