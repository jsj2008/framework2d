#include <Game.h>
#include <Filesystem/Filesystem.h>
#include <Tasks/TaskManager.h>
#include <Tasks/Task.h>
#include <iostream>
class TestTask : public Tasks::Task
{
public:
  TestTask()
    :Task(nullptr)
  {
  }
  void virtualExecute()
  {
    std::cout << "Executing" << std::endl;
  }
};
int main(int argv, char* argc[])
{
  Tasks::TaskManager* manager = new Tasks::TaskManager;
  manager->run();
  manager->addTaskToThisFrame(new TestTask());
  //    g_Game.init();
  //   g_Game.run();
  //    Filesystem::global()->shutdown();
    return 0;
}
