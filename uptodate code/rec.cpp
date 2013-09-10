//Steven Guan, 7/25/13. Wireless synchronization in application layer via UDP protocol.
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

#define MAXCOUNT 10000 //Counter counts up to this value.
#define lambda 0.8 //Must be between 0-1. Closer to 1 means greater synchronization.
#define delta 50 //Refractory period for the counter.
#define half MAXCOUNT/2

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c_var = PTHREAD_COND_INITIALIZER;

//void *UDP_send(void *ptr);
void *UDP_rec(void *ptr);

bool receiver;

struct info{
  std::string IP;
  int port;
};

int main(int argc, char *argv[]){
  //Checks if user specified a port number
  if (argc !=2) {
    printf("syntax: <port_number> \n");
    exit(-1);
  }
  //Initialize receiving and sending thread
  info* a = new info;
  a->port = (atoi(argv[1]));
  info* b = new info;
  b->port = (atoi(argv[1]));
  pthread_t t1, t2;
  pthread_cond_init (&c_var, NULL);
  pthread_mutex_init(&count_mutex, NULL);
  //pthread_create(&t1, NULL, UDP_send, a);
  pthread_create(&t2, NULL, UDP_rec, b);
  //initialize main thread
  while(1){
    ;
  }
  struct tm *current;
  struct timeval detail_time;
  time_t now;
  bool overflow = false;
  int i = 0;
  struct timeval tv;
  tv.tv_sec = 0;
  while(1){
    while((receiver == false) && (i < MAXCOUNT)){
      for(int x=0;x<10248;x++){
      }  
      i++;
    }
    //Broke out of while loop, check if received packet.
    if(receiver == true){
      printf("counter: %i\n", i);
      //If counter is in refractory period, do nothing.
      if(i < delta)
	;
      //Else, do synchronization algorithm stuff.
      else if(i < half){
	i = (i - (i*lambda));
      }
      else{
	i = i+(lambda*(MAXCOUNT-i));
      }
      receiver = false;
    }
    //If did not receive packet, counter overflowed; must send packet.
    else{
      pthread_cond_signal(&c_var);
      i = 0;
    }
  }
}

//UDP_rec blocks until there is a packet to receive. When it receives a packet, tell main thread.
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
    tv.tv_sec = 10;
    sel = select(s+1, &readfds, NULL, NULL, &tv);
    if (sel == 1){
      recvfrom(s, buf, sizeof(buf)-1, 0, (sockaddr *)&si_other, &slen);
      now = time(0);
      current = localtime(&now);
      gettimeofday(&detail_time,NULL); 
      printf("sent packet at %i.%06lu\n",current->tm_sec,detail_time.tv_usec);
    }
  }
}
/*
//UDP_send blocks until main thread gives it permission to send a broadcast packet to the adhoc subnet.
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
    printf("sent packet at %i.%06lu\n",current->tm_sec, 
detail_time.tv_usec);
  }
}
*/
