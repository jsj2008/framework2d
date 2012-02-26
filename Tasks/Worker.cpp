#include "Worker.h"
#include <Tasks/Task.h>
#include <Types/Thread.h>
#include <Types/Mutex.h>
namespace Tasks
{
  Worker::Worker()
  {
    mutex = new Mutex(true);
    task = nullptr;
    thread = new Thread(&Worker::main, this);
  }
  Worker::~Worker()
  {
    delete thread;
    delete mutex;
  }
  void Worker::run(Task* _task)
  {
    assert(task == nullptr);
    task = _task;
    mutex->unlock();
  }
  int Worker::main(void* _worker)
  {
    Worker* worker = static_cast<Worker*>(_worker);
    worker->loop();
    return 0;
  }
  void Worker::loop()
  {
    while (true)
      {
	mutex->lock();
	task->execute();
	task = nullptr;
      }
  }
}

