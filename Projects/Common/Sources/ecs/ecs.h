#pragma once
#include <stdint.h>
typedef uint32_t uint;
#include "system_order.h"
#include "system_tag.h"
#include "ecs_event.h"
#include "ecs_tag.h"
#include "ecs_core.h"

#define SYSTEM(...)static inline void 
#define QUERY(...)
#define EVENT(...)static inline void 