#pragma once
#include <unordered_map>
#include <vector>
#include "component_container.h"
namespace ecs
{
  struct TemplateInfo;
  class Archetype
  {
  public: 
    std::unordered_map<uint, ComponentContainer> components;
    int count, capacity;
    std::vector<FullTypeDescription*> fullTypeDescriptions;
    string synonim;

    //after this constructor need to feel components and fullTypeDescriptions correctly
    Archetype(int count, const string &synonim, int type_count);
    Archetype(const vector<string_hash> &type_hashes, int count, const string &synonim);
    bool in_archetype(const vector<string_hash> &type_hashes) const;

    ComponentContainer *get_container(const TypeDescription &type);
    template<typename T>
    ComponentContainer *get_container(const char *name);
    vector<void*> get_entity_data(const vector<string_hash> &type_hashes);
    void add_entity(const vector<const TemplateInfo*> &list);
    void destroy_entity(int index, bool with_swap);
    ~Archetype() = default;
    
  };
}