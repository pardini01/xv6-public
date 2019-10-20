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
  //int retime;
  //int rutime;
  //int stime;

  int pids[3*n];
  int types[3*n];

  for(counter0 = 0; counter0 < 3 * n; counter0++) {
    index++;
    if(fork() == 0) {
      pid = getpid();
      type = getpid() % 3;
      printf(1, "index:%d, pid:%d\n", index, pid);

      pids[index] = pid;
      types[index] = type;

      switch(type) {
        case CPU_BOUND:
          for(counter1 = 0; counter1 < 100; counter1++) {
            for(counter2 = 0; counter2 < 1000000; counter2++) {;}
          }
          break;

        case S_BOUND:
          for(counter1 = 0; counter1 < 100; counter1++) {
            for(counter2 = 0; counter2 < 1000000; counter2++) {;}
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
    else {
      wait();
    }
  }
  
  for(counter0 = 0; counter0 < 3 * n; counter0++)
    printf(1, "pid:%d, type:%d\n", pids[counter0], types[counter0]);
}

int main(int argc, char* argv[]) {
  sanity(atoi(argv[1]));
  return 0;
}
