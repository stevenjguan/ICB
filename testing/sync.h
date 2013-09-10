extern pthread_mutex_t count_mutex, count_mutex2; 
extern pthread_cond_t c_var, c_var2;

void *UDP_send(void *ptr);
void *UDP_rec(void *ptr);
int spawn_thread(int argc, char *argv[]);
float get_time();
void *counter(void *args);
