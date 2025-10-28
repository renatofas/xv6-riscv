#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void)
{
  int n = 10;
  for (int i = 0; i < n; i++) {
    int pid = fork();
    if (pid == 0) {
      int t = 50 * (i + 1);   // 50, 100, 150, ...
      settickets(t);
      volatile unsigned long long s = 0;
      for (unsigned long long j = 0; j < 150000000ULL; j++) s += j; // carga CPU
      printf("child pid=%d done (tickets=%d)\n", getpid(), t);
      exit(0);
    }
  }
  for (int i = 0; i < n; i++) wait(0);
  exit(0);
}
