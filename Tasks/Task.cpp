#include "Task.h"

namespace Tasks
{
  Task::Task(TaskProfile* _profile)
  {
    profile = _profile;
  }
  Task::~Task()
  {
  }
  void Task::execute()
  {
    unsigned int estimate = timeEstimate();
    virtualExecute();
  }
  unsigned int Task::timeEstimate()
  {
  }
  bool Task::lock()
  {
    return true;
  }
  void Task::unlock()
  {
  }
}

