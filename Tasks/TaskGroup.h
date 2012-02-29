#ifndef _TASKGROUP_H
#define _TASKGROUP_H

#include <Tasks/Task.h>

namespace Tasks
{
  class TaskProfile;
  class TaskGroup : public Task
  {
  public:
    TaskGroup(TaskProfile* _profile);
    ~TaskGroup();
    void virtualExecute();
    void addTask(Task* _task);
  private:
    List<Task> finishedTasks;
    List<Task> unfinishedTasks;
  };
}
#endif /* _TASKGROUP_H */

