#include <iostream>
#include <vector>
#include <cmath>
#include <string.h>
#include <pthread.h>
#include <time.h>

using namespace std;

const int THREAD_NUM = 5;
vector<int> primes;
static pthread_mutex_t mutexx = PTHREAD_MUTEX_INITIALIZER;

struct ThreadArgs
{
    int N;
    int threadId;
};

bool isPrime(int n)
{
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;

    return true;
}

void *parallel(void *args)
{
    ThreadArgs *targs = (ThreadArgs *)args;
    for (int i = 2 + targs->threadId; i <= targs->N; i += THREAD_NUM)
    {
        if (isPrime(i))
        {
            pthread_mutex_lock(&mutexx);
            primes.push_back(i);
            // cout << i << endl;
            pthread_mutex_unlock(&mutexx);
        }
    }
    pthread_exit(0);
}

int main(void)
{
    const int N = 10000000;
    pthread_t threads[THREAD_NUM];
    struct ThreadArgs threadArgs[THREAD_NUM];

    time_t begin, end;
    time(&begin);

    for (int i = 0; i < THREAD_NUM; i++)
    {
        threadArgs[i].N = N;
        threadArgs[i].threadId = i;
        pthread_create(&(threads[i]), NULL, parallel, &(threadArgs[i]));
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(threads[i], NULL);  
        // cout << i << " joined" << endl;
    }
    cout << primes.size() << endl;
    time(&end);
    cout << "parallel delta time:" << difftime(end, begin) << " seconds" << endl;
    
    return 0;
}