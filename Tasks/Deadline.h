#ifndef _DEADLINE_H
#define _DEADLINE_H

#include <Types/Tree.h>
#include <vector>

namespace Tasks
{
  class Task;
  class Deadline: public ListNode<Deadline>
  {
  public:
    Deadline();
    ~Deadline();
    unsigned int timeEstimate();
    Task* getTask();
  private:
    unsigned int timeLimit;
    List<Task> tasks;
    std::vector<Deadline*> prerequisites;
  };
}
#endif /* _DEADLINE_H */

