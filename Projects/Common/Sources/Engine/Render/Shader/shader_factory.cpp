#include "common.h"
#include "shader.h"
#include "shader_gen.h"
#include "Application/application_data.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <map>
#include <vector>

namespace fs = filesystem;
void process_codegen_shaders();


void read_directories(const fs::path &folder_path)
{
  if (!fs::exists(folder_path))
  {
    debug_error("Didn't exists %s", folder_path.string().c_str());
    return;
  }
  for (const auto &entry : fs::recursive_directory_iterator(folder_path, fs::directory_options::follow_directory_symlink))
  {
    if (entry.is_regular_file() && entry.path().extension() == ".glsl")
    {
      update_file(entry.path());
    }
  }
}

void compile_shaders()
{
  read_directories(Application::instance().projectShaderPath);
  process_codegen_shaders();
  debug_log("finish shader compilation");
}