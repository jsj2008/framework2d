#ifndef _TASKGROUP_H
#define _TASKGROUP_H

#include <Tasks/Task.h>

namespace Tasks
{
  class TaskGroup : public Task
  {
  public:
    TaskGroup();
    ~TaskGroup();
    void virtualExecute();
    void addTask(Task* _task);
  private:
    List<Task> tasks;
  };
}
#endif /* _TASKGROUP_H */

