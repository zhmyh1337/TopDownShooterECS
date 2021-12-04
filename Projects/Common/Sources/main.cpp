#include "Application/application_data.h"

int main(int, char**)
{
  Application application("TopDownShooterECS");
  application.start();
  application.main_loop();
  application.exit();
  
  return 0;
}