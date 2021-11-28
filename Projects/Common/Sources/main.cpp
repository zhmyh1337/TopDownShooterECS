#include "Application/application_data.h"

int main(int, char**)
{
  std::filesystem::path currentPath = std::filesystem::current_path();
  std::filesystem::path root(currentPath.parent_path().parent_path());
  string project = currentPath.stem().string();
  root.concat("/Projects/" + project);

  Application application(project, root.string());
  application.start();
  application.main_loop();
  application.exit();
  
  return 0;
}