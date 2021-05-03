#include "types.h"
#include "stat.h"
#include "user.h"
#include "rand.h"


int main(void)
{
  printf(1, "My first xv6 program: %d, %d, %d\n", info(1), info(2), info(3));
  ticket(30);
  int i,k;
  int start, end;
  const int loop=86000;
  start = info(4);
  for(i=0; i<loop; i++){
    asm("nop");
    for(k=0; k<loop; k++) asm("nop");
  }
  end = info(4);
  printf(1, "start: %d, end: %d, total time: %d, percent: %d\n",start, end, end-start, (end-start)*100/end);
  exit();
}
