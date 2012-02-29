#ifndef _DEADLINE_H
#define _DEADLINE_H

#include <Types/Tree.h>
#include <vector>
#include <string>

namespace Tasks
{
  class Task;
  class TaskGroup;
  class TaskManager;
  class Deadline: public NamedListNode<Deadline>
  {
  public:
    Deadline(TaskManager* _taskManager, const std::string& _name);
    ~Deadline();
    unsigned int timeEstimate();
    unsigned int getTimeLimit(){return timeLimit;}
    Task* getNextFreeTask();
    Task* getTask(const std::string& _name);
    TaskGroup* getTaskGroup(const std::string& _name);
    void addTask(Task* _task);
    void addTaskGroup(TaskGroup* _group);
    void addPrerequisite(Deadline* _deadline);
  private:
    unsigned int timeLimit;
    List<Task> tasks;
    List<TaskGroup> groupedTasks;
    std::vector<Deadline*> prerequisites;
    TaskManager* taskManager;
  };
}
#endif /* _DEADLINE_H */

