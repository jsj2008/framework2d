#ifndef _TASKMANAGER_H
#define _TASKMANAGER_H

#include <GameObject.h>
#include <Types/Tree.h>
struct SDL_Mutex;
#include <string>
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
  class WorkerPool;
  class TaskManager : public GameObject<TaskManager>
  {
  public:
    TaskManager();
    ~TaskManager();
    TaskProfile* getProfile(const std::string& _name);
    //    virtual void addTask(Task* _task);
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
        //    List<PriorityGrouping> tasks;
    Task* findTask();
    Policy* policy;
    Analyser* analyser;
    SDL_Mutex* thread;
  };
}
#endif /* _TASKMANAGER_H */

