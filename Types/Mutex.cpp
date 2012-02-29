#include "Mutex.h"

Mutex::Mutex(bool _locked)
{
  mutex = SDL_CreateMutex();
  if (_locked)
    lock();
}
Mutex::~Mutex()
{
  SDL_DestroyMutex(mutex);
}

void Mutex::lock()
{
  SDL_mutexP(mutex);
}

void Mutex::unlock()
{
  SDL_mutexV(mutex);
}
