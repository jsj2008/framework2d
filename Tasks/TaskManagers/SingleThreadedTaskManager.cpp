#include "SingleThreadedTaskManager.h"
#include <Tasks/Task.h>

namespace Tasks
{
  SingleThreadedTaskManager::SingleThreadedTaskManager()
  {
  }
  SingleThreadedTaskManager::~SingleThreadedTaskManager()
  {
  }
  void SingleThreadedTaskManager::addTask(Task* _task)
  {
    _task->execute();
  }
}

