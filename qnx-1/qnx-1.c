#include <errno.h>
#include <pthread.h>
#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 1.1
// int main(int argc, char **argv, char **envp) {
//   pid_t pid;
//   int ret, child_status;
//
//   char *child_argv[3] = {"ls", "-l", NULL};
//   ret = posix_spawn(&pid, "/proc/boot/ls", NULL, NULL, child_argv, envp);
//   if (ret != EOK) {
//     perror("posix_spawn() failed");
//     exit(EXIT_FAILURE);
//   }
//
//   pid = wait(&child_status);
//   if (pid == -1) {
//     perror("Wait");
//     exit(EXIT_FAILURE);
//   }
//
//   sleep(30);
//   return 0;
// }
//
// 1.2
//
void *thread_do_work(void *argc) {
  while (1) {
    printf("THREAD - %s WORKING WITH ID: %ul", (char *)argc, pthread_self());
  }
}

int main(int argc, char **argv, char **envp) {
  pthread_t threadOne;
  pthread_attr_t attr;

  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  pthread_create(&threadOne, &attr, thread_do_work, "ONE");
  pthread_join(threadOne, NULL);

  return 0;
}
