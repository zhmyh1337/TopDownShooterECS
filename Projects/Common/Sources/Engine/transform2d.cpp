#include "transform2d.h"
#include "ecs/ecs.h"

REG_TYPE(Transform2D)

mat4 Transform2D::get_matrix() const
{
  mat4 result = glm::mat4(1);
  result = glm::translate(result, glm::vec3(position, 0.0f));
  result = glm::rotate(result, rotation, glm::vec3(0.0f, 0.0f, 1.0f)); 
  result = glm::scale(result, glm::vec3(scale, 1.0f));
  return result;
}
