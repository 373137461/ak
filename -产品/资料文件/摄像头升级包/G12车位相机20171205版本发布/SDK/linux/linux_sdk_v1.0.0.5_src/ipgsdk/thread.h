#ifndef _THREAD__H_
#define _THREAD__H_

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <unistd.h>
#include <pthread.h>
#endif

#ifdef _WIN32
#define usleep(interval) Sleep(interval / 1000)

#define pthread_mutex_t HANDLE
#define CREATE_MUTEX(mutex) mutex = CreateMutex(NULL, FALSE, NULL)
#define DESTROY_MUTEX(mutex) CloseHandle(mutex)
#define MUTEX_LOCK(mutex) WaitForSingleObject(mutex, INFINITE)
#define MUTEX_UNLOCK(mutex) ReleaseMutex(mutex)

#define pthread_t HANDLE
#define THREAD_TYPE DWORD WINAPI
#define CREATE_THREAD(thread, proc, param) thread = CreateThread(NULL, 0, proc, param, 0, NULL)
#define DESTROY_THREAD(thread) WaitForSingleObject(thread, INFINITE);CloseHandle(thread)
#else
#define CREATE_MUTEX(mutex) pthread_mutex_init(&mutex, NULL)
#define DESTROY_MUTEX(mutex) pthread_mutex_destroy(&mutex)
#define MUTEX_LOCK(mutex) pthread_mutex_lock(&mutex)
#define MUTEX_UNLOCK(mutex) pthread_mutex_unlock(&mutex)

#define THREAD_TYPE void*
#define CREATE_THREAD(thread, proc, param) pthread_create(&thread, NULL, proc, param)
#define DESTROY_THREAD(thread) pthread_join(thread, NULL);
#endif

#endif