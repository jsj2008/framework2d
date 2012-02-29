#include "Thread.h"

Thread::Thread(int threadMain(void*), void* _data)
{
  thread = SDL_CreateThread(threadMain, _data);
}
Thread::~Thread()
{
}

