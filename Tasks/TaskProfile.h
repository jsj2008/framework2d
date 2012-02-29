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
    bool isExecutedNextFrame(){return executeNextFrame;}
  private:
    bool executeNextFrame;
    Dependency* dependencies;
  };
}
#endif /* _TASKPROFILE_H */

