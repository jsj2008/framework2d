#ifndef _SINGLETHREADEDTASKMANAGER_H
#define _SINGLETHREADEDTASKMANAGER_H

#include <Tasks/TaskManager.h>
namespace Tasks
{
  class SingleThreadedTaskManager: public TaskManager
  {
  public:
    SingleThreadedTaskManager();
    ~SingleThreadedTaskManager();
    void addTask(Task* _task);
  private:
  };
}

#endif /* _SINGLETHREADEDTASKMANAGER_H */

