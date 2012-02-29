#include "Deadline.h"
#include <Tasks/Task.h>

namespace Tasks
{
  Deadline::Deadline(TaskManager* _taskManager, const std::string& _name)
    :NamedListNode(_name)
  {
    taskManager = _taskManager;
  }
  Deadline::~Deadline()
  {
  }
  Task* Deadline::getNextFreeTask()
  {
    for (Deadline* deadline: prerequisites)
      {
	Task* task = deadline->getNextFreeTask();
	if (task)
	  {
	    return task;
	  }
      }
    for (Task* task = tasks.front(); task; task = task->getNextObject())
      {
	if (task->lock())
	  return task;
      }
    return nullptr;
  }
  void Deadline::addTask(Task* _task)
  {
    tasks.attachChild(_task);
  }
}
