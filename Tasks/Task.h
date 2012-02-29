#ifndef _TASK_H
#define _TASK_H

#include <Types/Tree.h>
namespace Tasks
{
  class Profile;
  class Priority;
  class TaskManager;
  class Task : public ListNode<Task>
  {
  public:
    Task(Profile* _profile);
    ~Task();
    void execute();
    bool lock();
    unsigned int timeEstimate();
    unsigned int* getVariables();
    const Profile* getProfile(){return profile;}
    Priority* getPriority(TaskManager* _manager);
  private:
    virtual void virtualExecute()=0;
    Profile* profile;
  };
}
#endif /* _TASK_H */

