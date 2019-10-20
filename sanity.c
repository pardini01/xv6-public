#include "types.h"
#include "user.h"

#define CPU_BOUND 0
#define S_BOUND 1
#define IO_BOUND 2

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

  int index = 0;

  int pid;
  int type;
  int retime;
  int rutime;
  int stime;

  struct procStatistics pStatistics[3 * n];

  for(counter0 = 0; counter0 < 3 * n; counter0++) {
    if(fork() == 0) {
      pid = getpid();
      type = pid % 3;

      pStatistics[index].pid = pid;
      pStatistics[index].type = type;

      switch(type) {
        case CPU_BOUND:
          for(counter1 = 0; counter1 < 100; counter1++) {
            for(counter2 = 0; counter2 < 1000000; counter2++) {;}
          }
          exit();
          break;

        case S_BOUND:
          for(counter1 = 0; counter1 < 100; counter1++) {
            for(counter2 = 0; counter2 < 1000000; counter2++) {;}
          }
          exit();
          break;

        case IO_BOUND:
          for(counter1 = 0; counter1 < 100; counter1++) {
            sleep(1);
          }
          exit();
          break;
      }
    }

    else {
      wait2(&retime, &rutime, &stime);

      pStatistics[index].retime = retime;
      pStatistics[index].rutime = rutime;
      pStatistics[index].stime = stime;
    }

    index++;
  }
  
  for(counter0 = 0; counter0 < 3 * n; counter0++)
    printf(1, "pid:%d, type:%d, retime:%d\n", pStatistics[counter0].pid, pStatistics[counter0].type, pStatistics[counter0].retime);
}

int myAtoi(char* str) { 
  int res = 0;

  for (int i = 0; str[i] != '\0'; ++i) 
    res = res * 10 + str[i] - '0'; 

  return res; 
}

int main(int argc, char* argv[]) {
  sanity(myAtoi(argv[1]));
  return 0;
}
