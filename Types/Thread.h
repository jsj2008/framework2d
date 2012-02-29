#ifndef _THREAD_H
#define _THREAD_H

#include <SDL/SDL_thread.h>
class Thread
{
 public:
  Thread(int threadMain(void*), void* _data);
  ~Thread();
 private:
  SDL_Thread* thread;
};

#endif /* _THREAD_H */

