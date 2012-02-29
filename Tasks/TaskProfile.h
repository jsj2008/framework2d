#ifndef _TASKPROFILE_H
#define _TASKPROFILE_H

namespace Tasks
{
  class Dependency;
  class TaskProfile
  {
  public:
    TaskProfile(bool _executeNextFrame);
    ~TaskProfile();
    
  private:

    Dependency* dependencies;
  };
}
#endif /* _TASKPROFILE_H */

