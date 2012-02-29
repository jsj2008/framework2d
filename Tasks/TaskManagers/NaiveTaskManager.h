#ifndef _NAIVETASKMANAGER_H
#define _NAIVETASKMANAGER_H

#include <Tasks/Taskmanager.h>
struct SDL_Mutex;
#include <vector>
namespace Tasks
{
  class TaskProfile;
  class Task;
  class Worker;
  class PriorityGrouping;
  class Resource;
  class Deadline;
  class Analyser;
  class Policy;
  class NaiveTaskManager : public TaskManager
  {
  public:
    NaiveTaskManager();
    Naive~TaskManager();
    void addTask(Task* _task);
    void addResource(Resource* _resource);
    void idler(WorkerPool* _worker); /// Worker became available
    void run();
    static void main(void* _taskManager);
    static std::string name()
    {
      return "TaskManager";
    }
    static void registerActions(GameObjectType* _type);
  private:
    List<Deadline> deadlines;
    List<Resource> resources;
    WorkerPool* idleWorkers;
    List<WorkerPool> activeWorkers;
    TaskList tasks;
    //    List<PriorityGrouping> tasks;
    Task* findTask();
    Policy* policy;
    Analyser* analyser;
    SDL_Mutex* thread;
  };
}
#endif /* _NAIVETASKMANAGER_H */

