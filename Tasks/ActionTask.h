#ifndef _ACTIONTASK_H
#define _ACTIONTASK_H

#include <Tasks/Task.h>
#include <GameObject.h>

namespace Tasks
{
  class ActionTask : public Task
  {
  public:
    ActionTask(GameObjectBase* _object, ActionHandle* _action, TaskProfile* _profile);
    ActionTask(const std::string& _objectDotAction, TaskProfile* _profile); 
    ~ActionTask();
    void virtualExecute();
  private:
    GameObjectBase* object;
    ActionHandle* action;
  };
}
#endif /* _ACTIONTASK_H */

