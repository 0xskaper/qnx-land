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
// int main(int argc, char **argv, char **envp) {
//   pid_t pid;
//   int child_status;
//
//   pid = fork();
//   if (pid == -1) {
//     perror("FORK()\n");
//     exit(EXIT_FAILURE);
//   } else if (pid > 0) {
//     printf("I AM CHILD AND NOW I'LL EXEC\n");
//     execl("/proc/boot/ls", "ls", "-l", "-a", NULL);
//   } else {
//     printf("I AM PARENT AND I'LL WAIT\n");
//     sleep(5);
//     pid = wait(&child_status);
//   }
// }
//
// 1.6
//
#define NUM_THREADS 5

long long factorial_results[NUM_THREADS];

pthread_mutex_t result_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
  int thread_id;
  int number;
} thread_data_t;

long long factorial(int n) {
  if (n <= 1)
    return 1;
  long long result = 1;
  for (int i = 2; i <= n; i++) {
    result *= i;
  }

  return result;
}

void *do_fact_thread(void *arg) {
  thread_data_t *data = (thread_data_t *)arg;

  printf("Thread: %d -> WORKING ON -> %d\n", data->thread_id, data->number);

  long long result = factorial(data->number);

  pthread_mutex_lock(&result_mutex);
  factorial_results[data->thread_id] = result;
  printf("THREAD %d: %d! = %lld\n", data->thread_id, data->number, result);
  pthread_mutex_unlock(&result_mutex);

  return NULL;
}

int main(int argc, char **argv, char **envp) {
  pthread_t threads[NUM_THREADS];
  thread_data_t thread_data[NUM_THREADS];

  for (int i = 0; i < NUM_THREADS; i++) {
    thread_data[i].thread_id = i;
    thread_data[i].number = i + 1;

    if (pthread_create(&threads[i], NULL, do_fact_thread, &thread_data[i]) !=
        0) {
      perror("pthread_create_failed");
      exit(1);
    }
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  printf("\nResult from shared Array\n");
  for (int i = 0; i < NUM_THREADS; i++) {
    printf("ARRAY %d: %d! = %lld\n", i, i + 1, factorial_results[i]);
  }

  pthread_mutex_destroy(&result_mutex);

  return 0;
}
