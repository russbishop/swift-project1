/*
 * fakelib/pthread.c
 *
 * Created by Simon Evans on 02/04/2016.
 * Copyright © 2016 Simon Evans. All rights reserved.
 *
 * pthread functions used by Swift Stdlib
 *
 */

#include "klibc.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

/*
 * pthread
 */

typedef struct pthread_mutex pthread_mutex_t;
typedef struct pthread_mutexattr pthread_mutexattr_t;
typedef struct pthread_cond pthread_cond_t;
typedef struct pthread_condattr pthread_condattr_t;
typedef struct pthread_rw_lock pthread_rwlock_t;
typedef struct pthread_rwlockattr pthread_rwlockattr_t;
typedef int pthread_once_t;
typedef unsigned int pthread_key_t;
typedef unsigned long int pthread_t;


__thread void* _ZSt15__once_callable;
__thread void (*_ZSt11__once_call)();


int
pthread_mutex_init(pthread_mutex_t *restrict mutex,
                   const pthread_mutexattr_t *restrict attr)
{
        debugf("pthread_mutex_init(%p,%p)\n", mutex, attr);
        return 0;
}

int
pthread_mutex_destroy(pthread_mutex_t *mutex)
{
        debugf("pthread_mutex_destroy(%p)\n", mutex);
        return 0;
}


int
pthread_mutex_lock(pthread_mutex_t *mutex)
{
        debugf("pthread_mutex_lock(%p)\n", mutex);
        return 0;
}

int
pthread_mutex_trylock (pthread_mutex_t *mutex)
{
        debugf("pthread_mutex_trylock(%p)\n", mutex);
        return 0;
}


int
pthread_mutex_unlock(pthread_mutex_t *mutex)
{
        debugf("pthread_mutex_unlock(%p)\n", mutex);
        return 0;
}


int
pthread_mutexattr_init(pthread_mutexattr_t *attr)
{
        debugf("pthread_mutexattr_init(%p)\n", attr);
        return 0;
}


int
pthread_mutexattr_settype (pthread_mutexattr_t *attr, int kind)
{
        debugf("pthread_mutexattr_settype(%p, %d)\n", attr, kind);
        return 0;
}


int
pthread_mutexattr_destroy(pthread_mutexattr_t *attr)
{
        debugf("pthread_mutexattr_destroy(%p)\n", attr);
        return 0;
}


int
pthread_cond_init(pthread_cond_t *restrict cond,
                  const pthread_condattr_t *restrict cond_attr)
{
        debugf("pthread_cond_init(%p,%p)\n", cond, condattr);
        return 0;
}


int
pthread_cond_destroy(pthread_cond_t *restrict cond)
{
        debugf("pthread_cond_destroy(%p)\n", cond);
        return 0;
}


int
pthread_cond_signal(pthread_cond_t *restrict cond)
{
        debugf("pthread_cond_signal(%p)\n", cond);
        return 0;
}


int
pthread_cond_broadcast(pthread_cond_t *restrict cond)
{
        debugf("pthread_cond_broadcast(%p)\n", cond);
        return 0;
}


int
pthread_cond_wait(pthread_cond_t *restrict cond,
                   pthread_mutex_t *restrict mutex)
{
        debugf("pthread_cond_wait(%p, %p)\n", cond, mutex);
        return 0;
}


int
pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,
                    const pthread_rwlockattr_t *restrict attr)
{
        debugf("pthread_rwlock_init(%p, %p)\n", rwlock, attr);
        return 0;
}


int
pthread_rwlock_destroy(pthread_rwlock_t *rwlock)
{
        debugf("pthread_rwlock_destroy(%p)\n", rwlock);
        return 0;
}


int
pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock)
{
        debugf("pthread_rwlock_tryrdlock(%p)\n", rwlock);
        return 0;
}


int
pthread_rwlock_rdlock(pthread_rwlock_t *rwlock)
{
        debugf("pthread_rwlock_rdlock(%p)\n", rwlock);
        return 0;
}


int
pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock)
{
        debugf("pthread_tryrwlock_wrlock(%p)\n", rwlock);
        return 0;
}


int
pthread_rwlock_wrlock(pthread_rwlock_t *rwlock)
{
        debugf("pthread_rwlock_wrlock(%p)\n", rwlock);
        return 0;
}


int
pthread_rwlock_unlock(pthread_rwlock_t *rwlock)
{
        debugf("pthread_rwlock_unlock(%p)\n", rwlock);
        return 0;
}


int
pthread_once(pthread_once_t *once_control, void (*init_routine)(void))
{
        debugf("pthread_once(%p, %d, %p)\n", once_control, *once_control, init_routine);

        if (*once_control == 0) {
                //debugf("running %p ... ", init_routine);
                init_routine();

                (*once_control)++;
        }
        return 0;
}


int
__pthread_key_create (pthread_key_t *key,
                          void (*destructor) (void *))
{
        debugf("pthread_key_create(%p,%p)\n", key, destructor);
        koops("unimplemented");
}


pthread_t
pthread_self()
{
        debugf("pthread_self()\n");
        return 1;
}


void __once_proxy()
{
        debugf("__once_proxy_func() __once_call=%p\n", _ZSt11__once_call);
        if (_ZSt11__once_call) {
                _ZSt11__once_call();
        }
}
