#include "types.h"
#include "stat.h"
#include "user.h"

#undef NULL
#define NULL ((void*)0)

#define PGSIZE (4096)

int ppid;
int global = 1;
lock_t lk;
int totalpass = 6;
int passcount = 0;
void bee(void * arg_ptr);
int bees = 4;
int 
main(int argc, char* argv[])
{
  ppid = getpid();
  lock_init(&lk);
  int i=0;
  int id[bees];
  int localbees = bees;
  for(i=0; i<localbees; i++){
    id[i] = i;
    int thread_pid = thread_create(bee, &id[i]);
    printf(1, "pid = %d\n", thread_pid);
  }
  for(i=0; i<localbees; i++){
    int join_pid = thread_join();
    printf(1, "pid = %d\n", join_pid);
  }
  printf(1, "test passed\n");
  exit();

}

void 
bee(void * arg_ptr){
  int id = *(int*)arg_ptr;
  printf(1, "child id:%d\n", id);
  while(passcount < totalpass){
    //printf(1, "count less than total\n");
    lock_acquire(&lk);
    //printf(1, "lock acquired\n");
    if (passcount < totalpass && passcount%bees==id){
      printf(1, "Pass numer no: %d, Thread %d is passing the token to thread %d\n", ++passcount, id, id+1);
    }
    //passcount++;
    lock_release(&lk);
    //printf(1, "lock released\n");
  }
  exit() ;
    
}
