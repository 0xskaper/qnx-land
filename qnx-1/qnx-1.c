#include <errno.h>
#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp) {
  pid_t pid;
  int ret, child_status;

  char *child_argv[3] = {"ls", "-l", NULL};
  ret = posix_spawn(&pid, "/proc/boot/ls", NULL, NULL, child_argv, envp);
  if (ret != EOK) {
    perror("posix_spawn() failed");
    exit(EXIT_FAILURE);
  }

  pid = wait(&child_status);
  if (pid == -1) {
    perror("Wait");
    exit(EXIT_FAILURE);
  }

  sleep(30);
  return 0;
}
