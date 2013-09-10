#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>        
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <time.h>
#include "sync.h"


int main(int argc, char *argv[]){
  spawn_thread(argc, argv); //starts the wireless synchronization algorithm
  pthread_cond_wait(&c_var2, &count_mutex2);
  //time = get_time(); //var time now has local time
  return 0;
}
