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
// int main(int argc, char **argv, char **envp) {
//   pid_t pid;
//   pid = fork();
//
//   if (pid > 0) {
//     printf("I AM CHILD WITH ID: %d\n", getpid());
//   } else {
//     printf("I AM PARENT WITH ID: %d\n", getpid());
//   }
//
//   return 0;
// }
//
// 1.4
//

// #define MAX_LEN 16
//
// void *worker_threads(void *arg) {
//   while (1) {
//     char threadName[MAX_LEN];
//     pthread_setname_np(pthread_self(), "WORKER");
//     pthread_getname_np(pthread_self(), threadName, MAX_LEN);
//
//     printf("%s %s - THREAD WITH ID - %d\n", threadName, (char *)arg,
//            pthread_self());
//     sleep(1);
//   }
//
//   return NULL;
// }
// int main(int argc, char **argv, char **envp) {
//   pthread_t threadOne;
//   pthread_attr_t attr;
//   char threadName[MAX_LEN];
//
//   pthread_setname_np(pthread_self(), "MAIN");
//   pthread_getname_np(pthread_self(), threadName, MAX_LEN);
//   printf("%s - THREAD WITH ID - %d\n", threadName, pthread_self());
//   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
//   pthread_create(&threadOne, NULL, worker_threads, "ONE");
//
//   while (1) {
//     sleep(1);
//   }
//   return 0;
// }
//
// 1.5
//
int main(int argc, char **argv, char **envp) {
  pid_t pid;
  int child_status;

  pid = fork();
  if (pid == -1) {
    perror("FORK()\n");
    exit(EXIT_FAILURE);
  } else if (pid > 0) {
    printf("I AM CHILD AND NOW I'LL EXEC\n");
    execl("/proc/boot/ls", "ls", "-l", "-a", NULL);
  } else {
    printf("I AM PARENT AND I'LL WAIT\n");
    sleep(5);
    pid = wait(&child_status);
  }
}
