#ifndef __TPOOL_H__
#define __TPOOL_H__

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

//REF: https://nachtimwald.com/2019/04/12/thread-pool-in-c/

typedef void (*thread_func_t)(void *args);

typedef struct tpool_work
{
    thread_func_t function;
    void *args;
    struct tpool_work *next_job;
}tpool_work_t;

typedef struct treadpool
{
    pthread_t *threads;
    tpool_work_t *first_work;
    tpool_work_t *last_work;
    pthread_mutex_t work_lock;
    pthread_cond_t work_to_complete;
    pthread_cond_t no_threads_processing;
    size_t work_count;
    size_t thread_count;
    size_t working_threads_count;
    bool shutdown;
}threadpool_t;

/**
 * @brief Test the given functions/value return values to equal, prints error message on failue
 *
 * @param check_this the function or value to complete due to critical operations
 * @param error_msg message to display before returning value
 * @param value is the value to test for
 *
 *
 * @return: function return operation on sucess, -1 on failue
*/
int check_functionality(int check_this, char * error_msg, int value);

/**
 * @brief Creates a Threadpool work object to be places in the threadpool queue
 *
 * @param func function to execute
 * @param arg arguments of the function
 *
 * @return Treadpool work or NULL if function is empty
 */
static tpool_work_t * tpool_work_create(thread_func_t func, void *arg);

/**
 * @brief Destroys a Job object and Clears the memory of the job
 *
 * @param work Job to destroy
 * @return None
 */
static int tpool_work_destroy(tpool_work_t *work);

/**
 * @brief Retrives a job from the threadpool job linked list and handles the list
 *
 * @param pool threadpool with jobs
 * @return job to be completed or NULL on failue
 */
static tpool_work_t *tpool_get_work(threadpool_t *pool);

/**
 * @brief Main threadpool function, handles the jobs to be completed.
 * Waits for work and processes it when present.
 *
 * @param pool threadpool to be porcessed
 * @return NULL on end of the pool
 */
static void * tpool_worker(void *args);

/**
 * @brief Creates a threadpool of with a specified number of threads
 *
 * @param num of threads to create for the pool
 * @return threadpool to work with, NULL if number not specified
 */
threadpool_t *tpool_create(size_t num);

/**
 * @brief Destroys the threadpool once all of the processses are finished
 *
 * @param pool to destroy
 * @return NULL if failed
 */
int tpool_destroy(threadpool_t *pool);

/**
 * @brief Adding work to the linked list of work to complete, notifies threads of work
 *
 * @param pool to add work to
 * @param func to complete
 * @param args of the function
 *
 * @return ture on success, false on failue
 */
bool tpool_add_work(threadpool_t *pool, thread_func_t func, void *args);

/**
 * @brief Function to wait for work to enter and will only return when their is work
 *
 * @param pool to wait until work is added
 *
 * @return NULL of failure
 */
void tpool_wait(threadpool_t *pool);

#endif