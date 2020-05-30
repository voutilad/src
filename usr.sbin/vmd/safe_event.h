int ev_add(pthread_mutex_t *, struct event *, struct timeval *tv);
int ev_del(pthread_mutex_t *, struct event *);
void timer_add(pthread_mutex_t *, struct event *, struct timeval *tv);
void timer_del(pthread_mutex_t *, struct event *);
int timer_pending(pthread_mutex_t *, struct event *, struct timeval *);
void *event_loop_thread(void *);
