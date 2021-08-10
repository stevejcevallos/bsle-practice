#include "threadpool.h"

int check_functionality(int check_this, char * error_msg, int value)
{
    if(check_this != value)
    {
        perror(error_msg);
        return value;
    }
    return check_this;
}

static tpool_work_t * tpool_work_create(thread_func_t func, void *arg)
{
    tpool_work_t *work;

    if(func == NULL)
    {
        return NULL;
    }

    work = malloc(sizeof(*work));

    if(work == NULL)
    {
        perror("Failed to Malloc Work");
        exit(EXIT_FAILURE);
    }

    work->function = func;
    work->args = arg;
    work->next_job = NULL;

    return work;
}

static int tpool_work_destroy(tpool_work_t *work)
{
    if (work == NULL)
    {
        return -1;
    }

    free(work);
    work = NULL;
    return 0;
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
        check_functionality(pthread_mutex_lock(&(pool->work_lock)),
            "Failed to Lock the Mutex", 0);

        while (pool->first_work == NULL && !pool->shutdown)
        {
            check_functionality(pthread_cond_wait(&(pool->work_to_complete), &(pool->work_lock)),
                "Failed to make it wait", 0);
        }

        if(pool->shutdown)
        {
            break;
        }

        work = tpool_get_work(pool);
        pool->work_count++;
        check_functionality(pthread_mutex_unlock(&(pool->work_lock)),
                "Failed to Unlock Mutex", 0);

        if(work != NULL)
        {
            work->function(work->args);
            check_functionality(tpool_work_destroy(work),
                "Failed to Destroy Work", 0);
        }

        check_functionality(pthread_mutex_lock(&(pool->work_lock)),
            "Failed to Lock the Mutex", 0);
        pool->work_count--;

        if(!pool->shutdown && pool->work_count == 0 && pool->first_work == NULL)
        {
            check_functionality(pthread_cond_signal(&(pool->no_threads_processing)),
            "Failed to Signal no threads processing", 0);
        }

        check_functionality(pthread_mutex_unlock(&(pool->work_lock)),
                "Failed to Unlock Mutex", 0);
    }

    pool->thread_count--;
    check_functionality(pthread_cond_signal(&(pool->no_threads_processing)),
            "Failed to Signal no threads processing", 0);

    check_functionality(pthread_mutex_unlock(&(pool->work_lock)),
                "Failed to Unlock Mutex", 0);

    return NULL;
}

threadpool_t *tpool_create(size_t num)
{
    threadpool_t *pool;

    if(num == 0)
    {
        return NULL;
    }

    pool = calloc(1, sizeof(*pool));
    if(pool == NULL)
    {
        perror("Failed to Calloc Pool");
        exit(EXIT_FAILURE);
    }

    pool->thread_count = num;
    pool->threads = calloc(num, sizeof(pthread_t));
    if(pool->threads == NULL)
    {
        perror("Failed to Calloc Pool");
        exit(EXIT_FAILURE);
    }

    check_functionality(pthread_mutex_init(&(pool->work_lock), NULL),
        "Failed to Init the Mutex", 0);

    check_functionality(pthread_cond_init(&(pool->work_to_complete), NULL),
        "Failed to Init the Work to Complete Condition", 0);

    check_functionality(pthread_cond_init(&(pool->no_threads_processing), NULL),
        "Failed to Init the No Threads Processing Condition", 0);

    pool->first_work = NULL;
    pool->last_work = NULL;
    pool->work_count = 0;

    for(size_t index = 0; index < num; index++)
    {
        check_functionality(pthread_create(&(pool->threads[index]), NULL, tpool_worker, pool),
            "Failed to Create Threads Goodbye", 0);
    }

    return pool;
}

int tpool_destroy(threadpool_t *pool)
{
    tpool_work_t *work;
    tpool_work_t *temp_work;

    if(pool ==  NULL)
    {
        return -1;
    }

    check_functionality(pthread_mutex_lock(&(pool->work_lock)),
            "Failed to Lock the Mutex", 0);

    work = pool->first_work;

    while(work != NULL)
    {
        temp_work = work->next_job;
        check_functionality(tpool_work_destroy(work),
                "Failed to Destroy Work", 0);
        work = temp_work;
    }

    pool->shutdown = true;
    check_functionality(pthread_cond_broadcast(&(pool->work_to_complete)),
        "Failed to Broadcast the Condition", 0);

    check_functionality(pthread_mutex_unlock(&(pool->work_lock)),
                "Failed to Unlock Mutex", 0);

    tpool_wait(pool);

    for(size_t index = 0; index < pool->thread_count; index++)
    {
        check_functionality(pthread_join(pool->threads[index], NULL),
            "Failed to Join Threads", 0);
    }

    if(pool->threads)
    {
        free(pool->threads);

        check_functionality(pthread_mutex_destroy(&(pool->work_lock)),
            "Failed to destroy the mutex", 0);
        check_functionality(pthread_cond_destroy(&(pool->work_to_complete)),
            "Failed to destroy the work to complete", 0);
        check_functionality(pthread_cond_destroy(&(pool->no_threads_processing)),
            "Failed to destroy the no threads", 0);
    }

    free(pool);
    return 0;
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

    check_functionality(pthread_mutex_lock(&(pool->work_lock)),
            "Failed to Lock the Mutex", 0);

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

    check_functionality(pthread_cond_broadcast(&(pool->work_to_complete)),
        "Failed to Broadcast the Condition", 0);

    check_functionality(pthread_mutex_unlock(&(pool->work_lock)),
                "Failed to Unlock Mutex", 0);

    return true;
}

void tpool_wait(threadpool_t *pool)
{
    if(pool == NULL)
    {
        return;
    }

    check_functionality(pthread_mutex_lock(&(pool->work_lock)),
            "Failed to Lock the Mutex", 0);

    while (1)
    {
        if((!pool->shutdown && pool->work_count != 0) ||
            (pool->shutdown && pool->thread_count != 0))
            {
                check_functionality(pthread_cond_wait(&(pool->no_threads_processing), &(pool->work_lock)),
                "Failed to make it wait", 0);
            }
            else
            {
                break;
            }
    }
    check_functionality(pthread_mutex_unlock(&(pool->work_lock)),
            "Failed to Lock the Mutex", 0);
}
