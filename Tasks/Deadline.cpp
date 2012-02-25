#include "Deadline.h"
#include <Tasks/Task.h>

namespace Tasks
{
  Deadline::Deadline()
  {
  }
  Deadline::~Deadline()
  {
  }
  Task* Deadline::getTask()
  {
    for (Deadline* deadline: prerequisites)
      {
	Task* task = deadline->getTask();
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
}
