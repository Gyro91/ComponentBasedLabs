#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dl_syscalls.h"

int main(int argc, char *argv[])
{
  struct sched_attr attr;
  pid_t pid;
  int res;

  if (argc < 4) {
    fprintf(stderr, "Usage: %s <pid> <Qs> <Ts> [flags]\n", argv[0]);

    return -1;
  }
  pid = atoi(argv[1]);

  memset(&attr, 0, sizeof(struct sched_attr));
  attr.size = sizeof(struct sched_attr);
  attr.sched_flags    = 0;
  if (argc > 4) {
    attr.sched_flags    = atoi(argv[4]);
  }
  attr.sched_policy   = SCHED_DEADLINE;
  attr.sched_runtime  = atoi(argv[2]) * 1000;
  attr.sched_period   = atoi(argv[3]) * 1000;
  attr.sched_deadline = atoi(argv[3]) * 1000;
  res = sched_setattr(pid, &attr, 0);
  if (res < 0) {
    perror("Sched Setattr");

    return -2;
  }

  return 0;
}
