#include "TaskGroup.h"

namespace Tasks
{
  TaskGroup::TaskGroup(TaskProfile* _profile)
    :Task(_profile)
  {
  }
  TaskGroup::~TaskGroup()
  {
  }
  void TaskGroup::addTask(Task* _task)
  {
    unfinishedTasks.attachChild(_task);
  }
  void TaskGroup::virtualExecute()
  {
    for (Task* task = unfinishedTasks.front(); task;)
      {
	if (task->lock())
	  {
	    task->execute();
	    Task* next = task->getNextObject();
	    finishedTasks.attachChild(task);
	    task = next;
	    task->unlock();
	  }
	else
	  {
	    task = task->getNextObject();
	  }
      }
  }
}

