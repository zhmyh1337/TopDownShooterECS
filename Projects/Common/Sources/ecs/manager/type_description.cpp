#include "type_description.h"
#include "common.h"
namespace ecs
{
 
  FullTypeDescription::FullTypeDescription(const char *name, string_hash type_hash, string_hash hash):
  name(name),
  typeHash(type_hash),hash(hash)
  {
  }
  const TypeInfo &FullTypeDescription::get_type_info() const
  {
    auto it = TypeInfo::types().find(typeHash);
    assert(it != TypeInfo::types().end());
    return it->second;
  }
  TypeDescription::TypeDescription(string_hash name_hash, string_hash type_hash):
    typeNameHash(hash(name_hash, type_hash)){}

  TypeDescription::TypeDescription(uint type_name_hash):
  typeNameHash(type_name_hash){}


    
  uint TypeDescription::type_name_hash() const 
  {
    return typeNameHash;
  }  
  
  bool TypeDescription::operator==(const TypeDescription &other)
  {
    return typeNameHash == other.typeNameHash;
  }
}