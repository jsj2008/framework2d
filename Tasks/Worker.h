#ifndef _WORKER_H
#define _WORKER_H

#include <Types/Tree.h>
class Thread;
class Mutex;
namespace Tasks
{
  class TaskManager;
  class Task;
  class Worker : public ListNode<Worker>
  {
  public:
    Worker();
    ~Worker();
    void run(Task* _task);
    static int main(void* _worker);
  private:
    void loop(); 
    TaskManager* manager;
    Task* task;
    Thread* thread;
    Mutex* mutex;
  };
}
#endif /* _WORKER_H */

