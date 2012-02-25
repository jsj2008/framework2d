#ifndef _MUTEX_H
#define _MUTEX_H

#include <SDL/SDL_thread.h>

class Mutex
{
 public:
  Mutex(bool _locked);
  ~Mutex();
  void lock();
  void unlock();
 private:
  SDL_mutex* mutex;
};

#endif /* _MUTEX_H */

