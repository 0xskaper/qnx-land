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
// void *thread_do_work(void *arg) {
//   while (1) { // Finite loop
//     printf("THREAD - %s WORKING WITH ID: %lu\n", (char *)arg,
//     pthread_self()); sleep(1);
//   }
//   return NULL;
// }
//
// int main(int argc, char **argv, char **envp) {
//   pthread_t threadOne;
//
//   pthread_create(&threadOne, NULL, thread_do_work, "ONE"); // Default
//   joinable pthread_join(threadOne, NULL);                           // Now
//   this works
//
//   return 0;
// }
//
// 1.3
//
int main(int argc, char **argv, char **envp) {
  pid_t pid;
  pid = fork();

  if (pid > 0) {
    printf("I AM CHILD WITH ID: %d\n", getpid());
  } else {
    printf("I AM PARENT WITH ID: %d\n", getpid());
  }

  return 0;
}
