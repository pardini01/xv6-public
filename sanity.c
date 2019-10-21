#include "types.h"
#include "user.h"

#define CPU_BOUND 0
#define S_BOUND 1
#define IO_BOUND 2

void sanity(int n) {
  int counter0;
  int counter1;
  int counter2;

  int pid;
  int type;
  int retime;
  int rutime;
  int stime;

  int statistics[3][3];
  for(counter0 = 0; counter0 < 3; counter0++)
    for(counter1 = 0; counter1 < 3; counter1++)
      statistics[counter0][counter1] = 0;

  for(counter0 = 0; counter0 < 3 * n; counter0++) {
    pid = fork();
    if(pid == 0) {
      type = (pid - 4) % 3;

      switch(type) {
        case CPU_BOUND:
          for(counter1 = 0; counter1 < 100; counter1++) {
            for(counter2 = 0; counter2 < 1000000; counter2++) {}
          }
          break;

        case S_BOUND:
          for(counter1 = 0; counter1 < 100; counter1++) {
            for(counter2 = 0; counter2 < 1000000; counter2++) {}
            //yield();
          }
          break;

        case IO_BOUND:
          for(counter1 = 0; counter1 < 100; counter1++) {
            sleep(1);
          }
          break;
      }
      exit();
    }
    continue;
  }

  for(counter0 = 0; counter0 < 3 * n; counter0++) {
    pid = wait2(&retime, &rutime, &stime);
    type = (pid - 4) % 3; // corresponds to types in the previous loop
    switch(type) {
      case CPU_BOUND:
        printf(1, "pid: %d, tipo: CPU_BOUND, tempo de espera: %d, tempo executando: %d, tempo de io: %d\n", pid, retime, rutime, stime);
        statistics[CPU_BOUND][0] += stime;
        statistics[CPU_BOUND][1] += retime;
        statistics[CPU_BOUND][2] += stime + retime + rutime;
        break;

      case S_BOUND:
        printf(1, "pid: %d, tipo: S_BOUND, tempo de espera: %d, tempo executando: %d, tempo de io: %d\n", pid, retime, rutime, stime);
        statistics[CPU_BOUND][0] += stime;
        statistics[CPU_BOUND][1] += retime;
        statistics[CPU_BOUND][2] += stime + retime + rutime;
        break;

      case IO_BOUND:
        printf(1, "pid: %d, tipo: IO_BOUND, tempo de espera: %d, tempo executando: %d, tempo de io: %d\n", pid, retime, rutime, stime);
        statistics[CPU_BOUND][0] += stime;
        statistics[CPU_BOUND][1] += retime;
        statistics[CPU_BOUND][2] += stime + retime + rutime;
        break;
    }
  }

  printf(1, "CPU_BOUND: Tempo medio SLEEPING: %d\n", (float)statistics[CPU_BOUND][0] / 3.0);
  printf(1, "CPU_BOUND: Tempo medio READY: %d\n", (float)statistics[CPU_BOUND][1] / 3.0);
  printf(1, "CPU_BOUND: Tempo medio turnaround: %d\n", (float)statistics[CPU_BOUND][2] / 3.0);
  printf(1, "S_BOUND: Tempo medio SLEEPING: %d\n", (float)statistics[S_BOUND][0] / 3.0);
  printf(1, "S_BOUND: Tempo medio READY: %d\n", (float)statistics[S_BOUND][1] / 3.0);
  printf(1, "S_BOUND: Tempo medio turnaround: %d\n", (float)statistics[S_BOUND][2] / 3.0);
  printf(1, "IO_BOUND: Tempo medio SLEEPING: %d\n", (float)statistics[IO_BOUND][0] / 3.0);
  printf(1, "IO_BOUND: Tempo medio READY: %d\n", (float)statistics[IO_BOUND][1] / 3.0);
  printf(1, "IO_BOUND: Tempo medio turnaround: %d\n", (float)statistics[IO_BOUND][2] / 3.0);
}

int main(int argc, char* argv[]) {
  sanity(atoi(argv[1]));
  return 0;
}
