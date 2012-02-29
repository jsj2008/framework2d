#ifndef _FIFOTASKMANAGER_H
#define _FIFOTASKMANAGER_H

#include <Tasks/TaskManager.h>
namespace Tasks
{
  class FifoTaskManager
  {
  public:
    FifoTaskManager();
    ~FifoTaskManager();
  
  private:
    List<Task> availableTasks;
    List<Resource> resources;
  };
}

#endif /* _FIFOTASKMANAGER_H */

