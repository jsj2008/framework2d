#include "TaskManager.h"
#include <Tasks/Resource.h>
#include <Tasks/Policy.h>
#include <Tasks/Worker.h>
#include <Tasks/WorkerPool.h>
#include <Tasks/Deadline.h>
#include <Tasks/Analyser.h>
#include <Tasks/TaskProfile.h>
#include <Tasks/ActionTask.h>
#include <Tasks/TaskGroup.h>
#include <Filesystem/Filesystem.h>

namespace Tasks
{
  TaskManager::TaskManager()
  {
    idleWorkers = nullptr;

    /// Hard coded TaskManager initialiser
    Deadline* graphicsFrame = new Deadline(this, "graphicsFrame");
    {
      TaskGroup* renderObjects = new TaskGroup;
      graphicsFrame->addTask(renderObjects);
      TaskProfile* renderEveryFrameProfile = new TaskProfile(true);
      std::vector<std::string> renderTasks =
	{
	  "/game/level.render",
	  "/dev/graphics.bufferFlip",
	};
      for (unsigned int i = 0; i != renderTasks.size(); i++)
	renderObjects->addTask(new ActionTask(renderTasks[i], renderEveryFrameProfile));	 
    }
    Deadline* physicsFrame = new Deadline(this, "physicsFrame");
    {
      TaskProfile* physicsUpdateEveryFrameProfile = new TaskProfile(true);
      Task* updateTask = new ActionTask("/game/level.update", physicsUpdateEveryFrameProfile);
      physicsFrame->addTask(updateTask);
    }
    graphicsFrame->addPrerequisite(physicsFrame);
    deadlines.attachChild(graphicsFrame);
  }
  TaskManager::~TaskManager()
  {
  }

  void TaskManager::run()
  {
    WorkerPool* pool = new WorkerPool(this);
    unsigned int workers = policy->numberOfWorkers();
    while (workers != 0)
      {
	pool->attachChild(new Worker);
	workers--;
      }
    idler(pool);
	/*	
    bool running = true;
    while (running)
      {
	Worker* idleWorker = idleWorkers.front();
	if (idleWorker)
	  {
	    if (findWork(idleWorker))
	      {
		idles.pop_front();
	      }
	    else
	      {
		tuner->idling(idleWorker);
	      }		
	  }
	else
	  {
	    Deadline* deadline = deadlines.front();
	    if (deadline)
	      {
	      }
	  }
	
	  }*/
  }
  void TaskManager::addTaskToFrameDeadline(Task* _task, unsigned int _offset)
  {
    assert(_offset == 0); /// FIXME need to properly implement this
    deadlines.front()->addTask(_task);
  }
  Task* TaskManager::findTask()
  {
    Deadline* deadline = deadlines.front();
    if (deadline)
      {
	Task* task = deadline->getNextFreeTask();
	if (task)
	  {
	    return task;
	  }
	analyser->noPrimaryDeadlineTasks();
	switch (policy->noPrimaryDeadlineTasks())
	  {
	  case Policy::eUseNextDeadline:
	    {
	      for (deadline = deadline->getNextObject(); deadline; deadline = deadline->getNextObject())
		{
		  Task* task = deadline->getNextFreeTask();
		  if (task)
		    return task;
		}
	      analyser->noTasks();
	      return nullptr;
	      break;
	    }
	  case Policy::eWaitMoreTasks:
	    {
	      return nullptr;
	    }
	  default:
	    assert(false);
	  }
      }
    switch (policy->noDeadlines())
      {
      case Policy::eWaitMoreDeadlines:
	  {
	return nullptr;
	  }
      default:
	assert(false);
      }
    assert(false);
    /*analyser->haveAmpleWork(false);
    switch (policy->noDeadlines())
    {*/
  }
  void TaskManager::idler(WorkerPool* _pool)
  {
    WorkerPool* pool = _pool;
    do
    {
      Task* task = findTask();
      if (task)
	{
	  pool = pool->execute(task);
	}
      else
	{
	  if (idleWorkers)
	    {
	      idleWorkers->append(pool);
	      delete _pool;
	      pool = nullptr;
	    }
	  else
	    {
	      idleWorkers = pool;
	    }
	  break;
	}
    }
    while (pool);
  }
    
  /*  void TaskManager::addTask(Task* _task)
  {
    if (idleWorkers)
      {
	idleWorkers = idleWorkers->execute(_task);
	return;
      }
    unsigned int priority = _task->getPriority();
    unsigned int lastPriority = 0;
    for (auto list: tasks)
      {
	assert(list->getPriority() > lastPriority);
	lastPriority = list->getPriority();
	if (lastPriority == priority)
	  {
	    list->attachChild(_task);
	    return;
	  }
	else if (lastPriority < priority || list.next() == tasks.end()))
	  {
	    list->insertAfter(new TaskList(_task));
	    return;
	  }
      }
    assert(tasks.begin() == nullptr);
    tasks.setChildren(new TaskList(_task));
  }*/
  void TaskManager::addResource(Resource* _resource)
  {
    resources.attachChild(_resource); /// FIXME make only Tree store parent pointer
  }
  void TaskManager::registerActions(GameObjectType* _type)
  {
  }
}
