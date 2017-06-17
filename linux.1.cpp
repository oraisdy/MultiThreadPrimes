#include <iostream>
#include <vector>
#include <cmath>
#include <string.h>
#include <pthread.h>

using namespace std;

const int THREAD_NUM = 5;

struct ThreadArgs
{
    int N;
    int threadId;
    vector<int> primes;
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
            targs->primes.push_back(i);
        }
    }
    pthread_exit(0);
}

int main(void)
{
    const int N = 10000000;
    pthread_t threads[THREAD_NUM];
    struct ThreadArgs threadArgs[THREAD_NUM];

    clock_t begin, end;
    begin = clock();

    for (int i = 0; i < THREAD_NUM; i++)
    {
        threadArgs[i].N = N;
        threadArgs[i].threadId = i;
        pthread_create(&(threads[i]), NULL, parallel, &(threadArgs[i]));
    }

    vector<int> primes;

    for (int i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(threads[i], NULL);
        primes.insert(primes.end(), threadArgs[i].primes.begin(), threadArgs[i].primes.end());
        // cout << i << " joined" << endl;
    }
    end = clock();
    cout << primes.size() << endl;
    cout << "parallel delta time:" << end - begin << endl;

    return 0;
}