#pragma once
#include <string>

namespace ecs
{
  struct OnSceneCreated
  {
    std::string scene_name;
    uint32_t tags;
  };
  struct OnEntityCreated
  {

  }; 
  struct OnEntityEdited
  {

  };
  struct OnEntityDestroyed
  {

  };
}