#include "TaskProfile.h"

namespace Tasks
{
  TaskProfile::TaskProfile(bool _executeNextFrame)
  {
    executeNextFrame = _executeNextFrame;
  }
  TaskProfile::~TaskProfile()
  {
  }
}
