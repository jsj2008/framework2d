#include "Policy.h"

namespace Tasks
{
  Policy::Policy()
  {
  }
  Policy::~Policy()
  {
  }
  unsigned int Policy::numberOfWorkers()
  {
    return 4;
  }
  Policy::NoPrimaryDeadlineTasksBehaviour Policy::noPrimaryDeadlineTasks()
  {
    return eUseNextDeadline;
  }
  Policy::NoDeadlinesBehaviour Policy::noDeadlines()
  {
    return eWaitMoreDeadlines;
  }
}
