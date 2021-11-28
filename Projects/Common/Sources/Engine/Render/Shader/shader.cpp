#include "shader.h"
#include <iostream>
#include <map>
#include "shader_gen.h"

struct ShaderInfo
{
  GLuint program;
};

static std::vector<std::pair<std::string, ShaderInfo>> shaderList;
static Shader badShader(-1);


Shader::Shader(const std::string &shader_name, GLuint shader_program)
{
  if (shader_program == BAD_PROGRAM)
    return;
  for (shaderIdx = 0; shaderIdx < (int)shaderList.size() && shaderList[shaderIdx].first != shader_name; ++shaderIdx);

  if (shaderIdx >= (int)shaderList.size())
  {
    shaderList.emplace_back(shader_name, ShaderInfo{shader_program});
  }
  else
  {
    shaderList[shaderIdx] = make_pair(shader_name, ShaderInfo{shader_program});
  }
}
GLuint Shader::get_shader_program() const
{
  return shaderIdx < 0 ? BAD_PROGRAM : shaderList[shaderIdx].second.program;
}

const string& Shader::get_name() const
{
  static string dummy = "";
  return shaderIdx < 0 ? dummy : shaderList[shaderIdx].first;
}

int get_shader_index(const std::string &shader_name)
{
  auto shader_iter = std::find_if(shaderList.begin(), shaderList.end(), [&](const auto &p){return p.first == shader_name;});
  return shader_iter != shaderList.end() ? shader_iter - shaderList.begin() : -1;
}
Shader get_shader(const std::string &shader_name)
{
  int shaderIdx = get_shader_index(shader_name);
	if (shaderIdx >= 0)
  {
    return Shader(shaderIdx);
  }
  else
  {
    debug_error("Can't find shader %s", shader_name.c_str());
    return badShader;
  }
}
void Shader::use() const
{
  glUseProgram(get_shader_program());
}