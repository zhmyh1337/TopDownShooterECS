#pragma once

namespace ecs
{
  typedef void *(*Constructor)(void*);
  typedef void *(*CopyConstructor)(const void*, void*);
  typedef void (*Destructor)(void*);
  typedef bool (*ComponentEdition)(void*, bool);
  typedef size_t (*Serializer)(std::ostream&, const void*);
  typedef size_t (*Deserializer)(std::istream&, void*);
}