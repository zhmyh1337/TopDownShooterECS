#pragma once

namespace ecs
{
  namespace SystemOrder
  {
    constexpr uint32_t
    NO_ORDER = 0,
    LOGIC = 1000,
    RENDER = 2000,
    UI = 3000,
    UIMENU = 4000;
  }
}