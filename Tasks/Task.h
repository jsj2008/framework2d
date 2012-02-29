#ifndef _TASK_H
#define _TASK_H

#include <Types/Tree.h>
namespace Tasks
{
  class TaskProfile;
  class Priority;
  class TaskManager;
  class Task : public ListNode<Task>
  {
  public:
    Task(TaskProfile* _profile);
    ~Task();
    void execute();
    bool lock();
    void unlock();
    unsigned int timeEstimate();
    unsigned int* getVariables();
    const TaskProfile* getTaskProfile(){return profile;}
    Priority* getPriority(TaskManager* _manager);
  private:
    virtual void virtualExecute()=0;
    TaskProfile* profile;
  };
}
#endif /* _TASK_H */

