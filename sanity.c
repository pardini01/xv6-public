#include "types.h"
#include "user.h"

void sanity(int n) {
  int counter0;
  int counter1;
  int counter2;
  int pid;
  for(counter0 = 0; counter0 < 3 * n; counter0++) {
    if(fork() == 0) {
      pid = getpid();
      switch((pid - 4) % 3) {
        case 0:
          for(counter1 = 0; counter1 < 100; counter1++) {
            for(counter2 = 0; counter2 < 1000000; counter2++) {;}
          }
          exit();
          break;

        case 1:
          for(counter1 = 0; counter1 < 100; counter1++) {
            for(counter2 = 0; counter2 < 1000000; counter2++) {;}
          }
          exit();
          break;

        case 2:
          for(counter1 = 0; counter1 < 100; counter1++) {
            sleep(1);
          }
          exit();
          break;
      }
    }
    else {
      wait();
    }
  }
}

int main(int argc, char* argv[]) {
  sanity(1);
  return 0;
}
