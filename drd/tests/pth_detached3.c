/* Invoke pthread_detach() with an invalid thread ID. */

#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>

#if defined(VGO_dragonfly)
#include <sys/types.h>
#endif

static void* thread_func(void* arg)
{
  return 0;
}

int main(int argc, char** argv)
{
  pthread_t thread;

  pthread_create(&thread, NULL, thread_func, NULL);
  pthread_join(thread, NULL);

  /* Invoke pthread_detach() with the thread ID of a joined thread. */
  pthread_detach(thread);

  /* Invoke pthread_detach() with an invalid thread ID. */
#ifdef VGO_dragonfly
  pthread_detach((pthread_t)12345);
#else
  pthread_detach(thread + 8);
#endif

  fprintf(stderr, "Finished.\n");

  return 0;
}
