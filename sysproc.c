#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  myproc()->syscallnum = myproc()->syscallnum+1;
  return fork();
}

int
sys_exit(void)
{
  myproc()->syscallnum = myproc()->syscallnum+1;
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  myproc()->syscallnum = myproc()->syscallnum+1;
  return wait();
}

int
sys_kill(void)
{ 
  myproc()->syscallnum = myproc()->syscallnum+1;
  int pid;
  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  myproc()->syscallnum = myproc()->syscallnum+1;
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;
  myproc()->syscallnum = myproc()->syscallnum+1;
  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  myproc()->syscallnum = myproc()->syscallnum+1;
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  myproc()->syscallnum = myproc()->syscallnum+1;
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int 
sys_info(void)
{
  int what;
  myproc()->syscallnum = myproc()->syscallnum+1;
  if(argint(0, &what) < 0) return -1;
  switch(what){
    case 1:
      return numthreads();
    case 2:
      return myproc()->syscallnum;   
    case 3:
      return myproc()->sz;
    default:
      return -1;
  }
}
