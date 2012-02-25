#ifndef _POLICY_H
#define _POLICY_H

namespace Tasks
{
  class Policy
  {
  public:
    Policy();
    ~Policy();
    unsigned int numberOfWorkers();
    enum NoPrimaryDeadlineTasksBehaviour
      {
	eUseNextDeadline,
	eWaitMoreTasks,
	eNoPrimaryDeadlineTasksBehaviourMax,
      };
    NoPrimaryDeadlineTasksBehaviour noPrimaryDeadlineTasks();
    enum NoDeadlinesBehaviour
      {
	eWaitMoreDeadlines,
	eNoDeadlinesBehaviourMax,
      };
    NoDeadlinesBehaviour noDeadlines();
  private:
  };
}
#endif /* _POLICY_H */

