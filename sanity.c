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
          set_prio(1);
          for(counter1 = 0; counter1 < 100; counter1++) {
            for(counter2 = 0; counter2 < 1000000; counter2++) {}
          }
          break;

        case S_BOUND:
          set_prio(2);
          for(counter1 = 0; counter1 < 100; counter1++) {
            for(counter2 = 0; counter2 < 1000000; counter2++) {}
          }
          break;

        case IO_BOUND:
          set_prio(3);
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
    type = (pid - 4) % 3;
    switch(type) {
      case CPU_BOUND:
        printf(1, "pid: %d, tipo: CPU_BOUND, tempo de espera: %d, tempo executando: %d, tempo de io: %d\n, tempo de turnarround: %d\n", pid, retime, rutime, stime, retime + rutime + stime);
        statistics[CPU_BOUND][0] += retime;
        statistics[CPU_BOUND][1] += rutime;
        statistics[CPU_BOUND][2] += stime;
        break;

      case S_BOUND:
        printf(1, "pid: %d, tipo: S_BOUND, tempo de espera: %d, tempo executando: %d, tempo de io: %d\n, tempo de turnarround: %d\n", pid, retime, rutime, stime, retime + rutime + stime);
        statistics[S_BOUND][0] += retime;
        statistics[S_BOUND][1] += rutime;
        statistics[S_BOUND][2] += stime;
        break;

      case IO_BOUND:
        printf(1, "pid: %d, tipo: IO_BOUND, tempo de espera: %d, tempo executando: %d, tempo de io: %d\n, tempo de turnarround: %d\n", pid, retime, rutime, stime, retime + rutime + stime);
        statistics[IO_BOUND][0] += retime;
        statistics[IO_BOUND][1] += rutime;
        statistics[IO_BOUND][2] += stime;
        break;
    }
  }

  for (counter0 = 0; counter0 < 3; counter0++)
    for (counter1 = 0; counter1 < 3; counter1++)
      statistics[counter0][counter1] /= n;

  printf(1, "\n\nCPU bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", statistics[0][0], statistics[0][1], statistics[0][2], statistics[0][0] + statistics[0][1] + statistics[0][2]);
  printf(1, "CPU-S bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", statistics[1][0], statistics[1][1], statistics[1][2], statistics[1][0] + statistics[1][1] + statistics[1][2]);
  printf(1, "I/O bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", statistics[2][0], statistics[2][1], statistics[2][2], statistics[2][0] + statistics[2][1] + statistics[2][2]);
  exit();

}

int main(int argc, char* argv[]) {
  sanity(atoi(argv[1]));
  return 0;
}
