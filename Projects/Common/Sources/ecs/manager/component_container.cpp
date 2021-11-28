#include "component_container.h"
#include "core_interface.h"
#include <stdlib.h>
namespace ecs
{

  ComponentContainer::ComponentContainer():
  data(), typeHash(-1), count(0)
  {  }
  ComponentContainer::ComponentContainer(string_hash type_hash, string_hash type_name_hash, int capacity, int sizeOf):
  data((capacity + binSize - 1) / binSize), typeHash(type_hash), typeNameHash(type_name_hash), count(0), capacity(data.size() * binSize), sizeOf(sizeOf)
  { 
    for (uint i = 0; i < data.size(); ++i)
      data[i] = malloc(binSize * type_sizeof(typeHash));
  }
  ComponentContainer::~ComponentContainer()
  {
    Destructor destructor = type_destructor(typeHash);
    uint sizeOf = type_sizeof(typeHash);
    for (int i = 0, j = 0; i * binSize + j < count;)
    {
      void *removed = (char*)data[i] + sizeOf * j;
      destructor(removed);
      j++;
      if (j >= binSize)
      {
        j = 0;
        i++;
      }
    }
    for (uint i = 0; i < data.size(); ++i)
      free(data[i]);
  }

  void ComponentContainer::add_component(void *component_data)
  {
    void *dst = add_component();
    CopyConstructor copyConstructor = type_copy_constructor(typeHash);
    Constructor constructor = copy_constructor(typeHash);
    constructor(dst);
    copyConstructor(component_data, dst);
  }
  void* ComponentContainer::add_component()
  {
    if (count == capacity)
    {
      data.push_back(malloc(binSize * type_sizeof(typeHash)));
      capacity += binSize;
    }
    int j = count / binSize;
    int i = count % binSize;
    void *dst = (char*)data[j] + type_sizeof(typeHash) * i;
    count++;
    return dst;
  }
  void ComponentContainer::destroy_component(int i, bool with_swap)
  {
    count--;
    CopyConstructor copyConstructor = type_copy_constructor(typeHash);
    Destructor destructor = type_destructor(typeHash);
    int j = count;
    void *removed = (char*)data[i / binSize] + type_sizeof(typeHash) * (i % binSize);
    destructor(removed);
    if (with_swap && j != i)
    {
      void *copied = (char*)data[j / binSize] + type_sizeof(typeHash) * (j % binSize);
      copyConstructor(copied, removed);
    }
  }
  
  void ComponentContainer::copy_components(const ComponentContainer &other)
  {
    assert(count == 0 && "Need empty container to copy to");
    while (other.count >= capacity)
    {
      data.push_back(malloc(binSize * type_sizeof(typeHash)));
      capacity += binSize;
    }
    CopyConstructor copyConstructor = type_copy_constructor(typeHash);
    Constructor constructor = copy_constructor(typeHash);

    for (;count < other.count; ++count)
    {
      int j = count / binSize;
      int i = count % binSize;
      const void *scr = (char*)other.data[j] + type_sizeof(typeHash) * i;
            void *dst = (char*)      data[j] + type_sizeof(typeHash) * i;
      constructor(dst);
      copyConstructor(scr, dst);
    }
  }
}