#include "types.h"
#include "user.h"

#define CPU_BOUND 0
#define S_BOUND 1
#define IO_BOUND 2

typedef struct procStatistics procStatistics;

struct procStatistics {
  int pid;
  int type;
  int retime;
  int rutime;
  int stime;
};

void sanity(int n) {
  int counter0;
  int counter1;
  int counter2;

  int index = -1;

  int pid;
  int type;
  int retime;
  int rutime;
  int stime;

  for(counter0 = 0; counter0 < 3 * n; counter0++) {
    index++;
    pid = fork();
    type = pid % 3;

    if(pid == 0) {
      printf(1, "index:%d, pid:%d\n", index, pid);

      type = (pid - 4) % 3;

      switch(type) {
        case CPU_BOUND:
          for(counter1 = 0; counter1 < 100; counter1++) {
            for(counter2 = 0; counter2 < 1000000; counter2++) {}
          }
          set_prio(1);
          break;

        case S_BOUND:
          for(counter1 = 0; counter1 < 100; counter1++) {
            for(counter2 = 0; counter2 < 1000000; counter2++) {}
            //yield();
          }
          set_prio(2);
          break;

        case IO_BOUND:
          for(counter1 = 0; counter1 < 100; counter1++) {
            sleep(1);
          }
          set_prio(3);
          break;
      }
      exit();
    }
    continue;
  }

  for(counter0 = 0; counter0 < 3 * n; counter0++) {
      pid = wait2(&retime, &rutime, &stime);
      int modulus = (pid - 4) % 3; // corresponds to types in the previous loop
      switch(res) {
        case CPU_BOUND:
          printf(1, "CPU-bound, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d\n", pid, retime, rutime, stime, retime + rutime + stime);
          //sums[0][0] += retime;
          //sums[0][1] += rutime;
          //sums[0][2] += stime;
          break;
        case S_BOUND:
          printf(1, "CPU-S bound, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d\n", pid, retime, rutime, stime, retime + rutime + stime);
          //sums[1][0] += retime;
          //sums[1][1] += rutime;
          //sums[1][2] += stime;
          break;
        case IO_BOUND:
          printf(1, "I/O bound, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d\n", pid, retime, rutime, stime, retime + rutime + stime);
          //sums[2][0] += retime;
          //sums[2][1] += rutime;
          //sums[2][2] += stime;
          break;
      }
  }

  /*
    for (i = 0; i < 3; i++)
          for (j = 0; j < 3; j++)
                  sums[i][j] /= n;
      printf(1, "\n\nCPU bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sums[0][0], sums[0][1], sums[0][2], sums[0][0] + sums[0][1] + sums[0][2]);
        printf(1, "CPU-S bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sums[1][0], sums[1][1], sums[1][2], sums[1][0] + sums[1][1] + sums[1][2]);
          printf(1, "I/O bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sums[2][0], sums[2][1], sums[2][2], sums[2][0] + sums[2][1] + sums[2][2]);
            exit();
                  
} */

}

int main(int argc, char* argv[]) {
  sanity(atoi(argv[1]));
  return 0;
}
