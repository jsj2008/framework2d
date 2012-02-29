#include "Task.h"

namespace Tasks
{
  Task::Task(Profile* _profile)
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
}

