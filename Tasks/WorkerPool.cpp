#include "WorkerPool.h"

namespace Tasks
{
  WorkerPool::WorkerPool(TaskManager* _manager)
  {
    manager = _manager;
  }
  WorkerPool::~WorkerPool()
  {
  }
  WorkerPool* WorkerPool::execute(Task* _task)
  {
    /// FIXME put in splitting
    front()->run(_task);
    detachChild(front());
    if (front() == nullptr)
      {
	delete this;
	return nullptr;
      }
    else
      {
	return this;
      }
  }
}

