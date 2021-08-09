#include "threadpool.h"

static tpool_work_t * tpool_work_create(thread_func_t func, void *arg)
{
    tpool_work_t *work;

    if(func == NULL)
    {
        return NULL;
    }

    work = malloc(sizeof(*work));
    work->function = func;
    work->args = arg;
    work->next_job = NULL;

    return work;
}

static void tpool_work_destroy(tpool_work_t *work)
{
    if (work == NULL)
    {
        return;
    }

    free(work);
    work = NULL;
}

static tpool_work_t *tpool_get_work(threadpool_t *pool)
{
    tpool_work_t *work_to_complete;

    //Checks if the pool has jobs to complete
    if(pool == NULL)
    {
        return NULL;
    }

    work_to_complete = pool->first_work;

    //Check if the first job is not empty
    if(work_to_complete == NULL)
    {
        return NULL;
    }

    //Assigns the next job to be the first node again or NULL if no jobs present
    if(work_to_complete->next_job == NULL)
    {
        pool->first_work = NULL;
        pool->last_work = NULL;
    }
    else
    {
        pool->first_work = work_to_complete->next_job;
    }

    return work_to_complete;
}

static void * tpool_worker(void *args)
{
    threadpool_t * pool = args;
    tpool_work_t * work;

    while (1)
    {
        pthread_mutex_lock(&(pool->work_lock));

        while (pool->first_work == NULL && !pool->shutdown)
        {
            pthread_cond_wait(&(pool->work_to_complete), &(pool->work_lock));
        }

        if(pool->shutdown)
        {
            break;
        }

        work = tpool_get_work(pool);
        pool->work_count++;
        pthread_mutex_unlock(&(pool->work_lock));

        if(work != NULL)
        {
            work->function(work->args);
            tpool_work_destroy(work);
        }

        pthread_mutex_lock(&(pool->work_lock));
        pool->work_count--;

        if(!pool->shutdown && pool->work_count == 0 && pool->first_work == NULL)
        {
            pthread_cond_signal(&(pool->no_threads_processing));
        }
        pthread_mutex_unlock(&(pool->work_lock));
    }

    pool->thread_count--;
    pthread_cond_signal(&(pool->no_threads_processing));
    pthread_mutex_unlock(&(pool->work_lock));

    return NULL;
}

threadpool_t *tpool_create(size_t num)
{
    threadpool_t *pool;
    pthread_t thread;

    if(num == 0)
    {
        return NULL;
    }

    pool = calloc(1, sizeof(*pool));
    pool->thread_count = num;

    pool->threads = calloc(num, sizeof(pthread_t));

    pthread_mutex_init(&(pool->work_lock), NULL);
    pthread_cond_init(&(pool->work_to_complete), NULL);
    pthread_cond_init(&(pool->no_threads_processing), NULL);

    pool->first_work = NULL;
    pool->last_work = NULL;
    pool->work_count = 0;

    for(size_t index = 0; index < num; index++)
    {
        pthread_create(&(pool->threads[index]), NULL, tpool_worker, pool);
    }

    return pool;
}

void tpool_destroy(threadpool_t *pool)
{
    tpool_work_t *work;
    tpool_work_t *temp_work;

    if(pool ==  NULL)
    {
        return NULL;
    }

    pthread_mutex_lock(&(pool->work_lock));

    work = pool->first_work;

    while(work != NULL)
    {
        temp_work = work->next_job;
        tpool_work_destroy(work);
        work = temp_work;
    }

    pool->shutdown = true;
    pthread_cond_broadcast(&(pool->work_lock));
    pthread_mutex_unlock(&(pool->work_lock));

    tpool_wait(pool);

    for(size_t index = 0; index < pool->thread_count; index++)
    {
        pthread_join(pool->threads[index], NULL);
    }

    if(pool->threads)
    {
        free(pool->threads);

        pthread_mutex_destroy(&(pool->work_lock));
        pthread_cond_destroy(&(pool->work_to_complete));
        pthread_cond_destroy(&(pool->no_threads_processing));
    }
    free(pool);
}

bool tpool_add_work(threadpool_t *pool, thread_func_t func, void *args)
{
    tpool_work_t *work;

    if(pool == NULL)
    {
        return false;
    }

    work = tpool_work_create(func, args);
    if(work == NULL)
    {
        return false;
    }

    pthread_mutex_lock(&(pool->work_lock));

    if(pool->first_work == NULL)
    {
        pool->first_work = work;
        pool->last_work = pool->first_work;
    }
    else
    {
        pool->last_work->next_job = work;
        pool->last_work = work;
    }

    pthread_cond_broadcast(&(pool->work_to_complete));
    pthread_cond_unlock(&(pool->work_lock));

    return true;
}

void tpool_wait(threadpool_t *pool)
{
    if(pool == NULL)
    {
        return NULL;
    }

    pthread_mutex_lock(&(pool->work_lock));

    while (1)
    {
        if((!pool->shutdown && pool->work_count != 0) ||
            pool->shutdown && pool->thread_count != 0)
            {
                pthread_cond_wait(&(pool->no_threads_processing), &(pool->work_lock));
            }
            else
            {
                break;
            }
    }
    pthread_mutex_unlock(&(pool->work_lock));
}






