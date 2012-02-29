#include "ActionTask.h"
#include <Filesystem/Filesystem.h>

namespace Tasks
{
  ActionTask::ActionTask(GameObjectBase* _object, ActionHandle* _action, TaskProfile* _profile)
    :Task(_profile)
  {
    object = _object;
    action = _action;
  }
  ActionTask::ActionTask(const std::string& _objectDotAction, TaskProfile* _profile)
    :Task(_profile)
  {
    object = Filesystem::global()->getNode("/dev/graphics");
    action = object->getType()->getActionHandle("bufferFlip");
  }

  ActionTask::~ActionTask()
  {
  }

  void ActionTask::virtualExecute()
  {
    action->execute(object);
  }
}
