#include <event.h>
#include <pthread.h>

#include "proc.h"
#include "safe_event.h"

int
ev_add(pthread_mutex_t *mutex, struct event *ev, struct timeval *tv)
{
	int ret;
	pthread_mutex_lock(mutex);
	ret = event_add(ev, tv);
	pthread_mutex_unlock(mutex);
	return ret;
}

int
ev_del(pthread_mutex_t *mutex,struct event *ev)
{
	int ret;
	pthread_mutex_lock(mutex);
	ret = event_del(ev);
	pthread_mutex_unlock(mutex);
	return ret;
}

void
timer_add(pthread_mutex_t *mutex, struct event *ev, struct timeval *tv)
{
	pthread_mutex_lock(mutex);
	evtimer_add(ev, tv);
	pthread_mutex_unlock(mutex);
}

void
timer_del(pthread_mutex_t *mutex, struct event *ev)
{
	pthread_mutex_lock(mutex);
	evtimer_del(ev);
	pthread_mutex_unlock(mutex);
}

int
timer_pending(pthread_mutex_t *mutex, struct event *ev, struct timeval *tv)
{
	int ret;
	pthread_mutex_lock(mutex);
	ret = evtimer_pending(ev, tv);
	pthread_mutex_unlock(mutex);
	return ret;
}

void *
event_loop_thread(void *arg)
{
	struct event_base *evbase;
	intptr_t ret;
	int r;

	evbase = arg;

	r = event_base_dispatch(evbase);
	ret = r;

	log_info("%s: event loop for evbase %p exiting (r=%d)",
	    __func__, evbase, r);
	return (void *)ret;
}
