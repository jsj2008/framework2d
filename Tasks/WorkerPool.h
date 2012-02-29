#ifndef _WORKERPOOL_H
#define _WORKERPOOL_H

#include <Types/Tree.h>
#include <Tasks/Worker.h>

namespace Tasks
{
  class WorkerPool : public List<Worker>
  {
  public:
    WorkerPool(TaskManager* _manager);
    ~WorkerPool();
    WorkerPool* execute(Task* _task);
  private:
    TaskManager* manager;
  };
}
#endif /* _WORKERPOOL_H */

