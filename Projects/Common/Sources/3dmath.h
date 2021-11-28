#pragma once
#define GLM_FORCE_LEFT_HANDED
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/vector_angle.hpp>
using namespace glm;

constexpr float PI = 3.1415926535897932384626433832795f;
constexpr float PIHALF = PI * 0.5f;
constexpr float PITWO = PI * 2.0f;
constexpr float DegToRad = PI / 180.f;
constexpr float RadToDeg = 1.f / DegToRad;

inline int rand_int(int max_val = RAND_MAX)
{
  return abs(rand()) % max_val;
}

inline float rand_float(float from = -1.f, float to = 1.f)
{
  return from + ((float)rand() / RAND_MAX) * (to - from);
}

inline vec2 rand_vec2(float from = -1.f, float to = 1.f)
{
  return vec2(rand_float(from, to), rand_float(from, to));
}

inline vec3 rand_vec3(float from = -1.f, float to = 1.f)
{
  return vec3(rand_float(from, to), rand_float(from, to), rand_float(from, to));
}

inline vec4 rand_vec4(float from = 0.f, float to = 1.f)
{
  return vec4(rand_float(from, to), rand_float(from, to), rand_float(from, to), rand_float(from, to));
}
