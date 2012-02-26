#ifndef _DEADLINE_H
#define _DEADLINE_H

#include <Types/Tree.h>
#include <vector>

namespace Tasks
{
  class Task;
  class TaskManager;
  class Deadline: public ListNode<Deadline>
  {
  public:
    Deadline(TaskManager* _taskManager);
    ~Deadline();
    unsigned int timeEstimate();
    Task* getTask();
    void addTask(Task* _task);
  private:
    unsigned int timeLimit;
    List<Task> tasks;
    std::vector<Deadline*> prerequisites;
    TaskManager* taskManager;
  };
}
#endif /* _DEADLINE_H */

