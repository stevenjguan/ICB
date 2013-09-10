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

#define MAXCOUNT 10000
#define lambda 0.8
#define delta 25
#define half MAXCOUNT/2

bool x;

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER, count_mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_var = PTHREAD_COND_INITIALIZER, c_var2 = PTHREAD_COND_INITIALIZER;

struct info{
  std::string IP;
  int port;
};

struct timespec tim = {0, 1*100*1000};

int seconds = 0, minutes = 0, hours = 0, count = 0;
int i = 0;

int spawn_thread(int argc, char *argv[]){
  // <IP> <Port#1> <Port#2>
  if (argc !=2) {
    printf("syntax: <port_number> \n");
    exit(-1);
  }
  info* a = new info;
  a->port = (atoi(argv[1]));
  info* b = new info;
  b->port = (atoi(argv[1]));
  pthread_t t1, t2, t3;
  long* t;
  pthread_cond_init (&c_var, NULL);
  pthread_mutex_init(&count_mutex, NULL);
  pthread_create(&t1, NULL, UDP_send, a);
  pthread_create(&t2, NULL, UDP_rec, b);
  pthread_create(&t3, NULL, counter, t);
  return 0;
}

void *counter(void *args){
  struct tm *current;
  struct timeval detail_time;
  time_t now;
  bool overflow = false;
  // struct timespec tv_start, tv_end;
  // clockid_t clockid;
  // int rv = clock_getcpuclockid(0, &clockid);
  
  // if (rv) {
  //   perror("clock_getcpuclockid");
  //   exit(0);
  // }
  sleep(1);
  // clock_gettime(clockid, &tv_start);
  while(1){
    while((x == false) && (overflow == false)){
      for(int x=0;x<10228;x++)
	;  
      i++;
      if(i >= MAXCOUNT)
	overflow = true;
    }
    
    if(x == true){
      //printf("counter: %i\n", i);
      if(i <delta)
	;
      else if(i < half){
	i = (i - (i*lambda));
	
      }
      else{
	i = i+(lambda*(MAXCOUNT-i));
	
      }
      x = false;
      
    }
    if(overflow == true){
      pthread_cond_signal(&c_var);
      count++;
      seconds = count % 60;
      minutes = seconds % 60;
      hours = minutes % 60;
      i = 0;
      overflow = false;
      if(seconds > 10){
	// clock_gettime(clockid, &tv_end);
	// long long diff = (long long)(tv_end.tv_sec - tv_start.tv_sec);
	// long long diff2 = (tv_end.tv_nsec - tv_start.tv_nsec);
	// printf("system time: %lld.%lld ns\n", diff, diff2);
	pthread_cond_signal(&c_var2);
      }
    }
  }
}


void *UDP_rec(void *ptr){
  struct info *c = (struct info *) ptr;
  sockaddr_in si_me, si_other;
  int s;
  s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  int port=6000;
  int broadcast=1;
  char buf[40];

  memset(&si_me, 0, sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(c->port);
  si_me.sin_addr.s_addr = INADDR_ANY;
  
  bind(s, (sockaddr *)&si_me, sizeof(sockaddr));
  setsockopt(s, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof broadcast);
  int sel = 0;
  fd_set readfds;
  struct timeval tv;
  struct tm *current;
  struct timeval detail_time;
  time_t now;
  unsigned int slen = sizeof(struct sockaddr_in);
  FD_ZERO(&readfds);
  FD_SET(s, &readfds);
  while(1){
    tv.tv_sec = 3;
    sel = select(s+1, &readfds, NULL, NULL, &tv);
    if (sel == 1){
      recvfrom(s, buf, sizeof(buf)-1, 0, (sockaddr *)&si_other, &slen);
      
      x = true;
    }
  }
}

void *UDP_send(void *ptr){
  struct info *c = (struct info *) ptr;
  std::string str;
  int datalen;
  const char *databuf;
  datalen = 1;
  str = "r";
  databuf = str.c_str();
  time_t now;
  struct tm *current;
  struct timeval detail_time;
  
  int sock;                        
   struct sockaddr_in broadcastAddr; 
   char *broadcastIP;                
   unsigned short broadcastPort;     
   char *sendString;                 
   int broadcastPermission;         
   int sendStringLen;                





   if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0){
       fprintf(stderr, "socket error");
        exit(1);
   }
   
   char loopch=0;

   if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP,
               (char *)&loopch, sizeof(loopch)) < 0) {
     perror("setting IP_MULTICAST_LOOP:");
     close(sock);
     exit(1);
   }

   broadcastPermission = 1;
   if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission,sizeof(broadcastPermission)) < 0){
       fprintf(stderr, "setsockopt error");
       exit(1);
   }

   /* Construct local address structure */
   memset(&broadcastAddr, 0, sizeof(broadcastAddr));   
   broadcastAddr.sin_family = AF_INET;                 
   broadcastAddr.sin_addr.s_addr = inet_addr("10.42.43.255");
   broadcastAddr.sin_port = htons(c->port);     

  while(1){
    pthread_cond_wait(&c_var, &count_mutex);
    sendto(sock, databuf, 1, 0, (struct sockaddr *)&broadcastAddr, sizeof(broadcastAddr));
    now = time(0);
    current = localtime(&now);
    gettimeofday(&detail_time,NULL); 
    printf("sent packet at %i.%06lu seconds\n",current->tm_sec, 
detail_time.tv_usec);
  }
}

float get_time(){
  float decimal = i;
  float time = seconds;
  decimal = decimal / 10000;
  time = time + decimal;
  return time;
}
