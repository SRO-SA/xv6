#include "types.h"
#include "stat.h"
#include "user.h"


int main(void)
{
  printf(1, "My first xv6 program: %d, %d, %d\n", info(1), info(2), info(3));
  exit();
}
