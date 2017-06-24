#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>
#include <time.h>

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

void *concurrent(void *args)
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

    time_t begin, end;
    time(&begin);

    for (int i = 0; i < THREAD_NUM; i++)
    {
        threadArgs[i].N = N;
        threadArgs[i].threadId = i;
        // pthread_create(&(threads[i]), NULL, parallel, &(threadArgs[i]));
        threads[i] = CreateThread(NULL, 0,
                                  concurrent,
                                  &(threadArgs[i]),
                                  0, NULL)
    }

    vector<int> primes;

    for (int i = 0; i < THREAD_NUM; i++)
    {
        // pthread_join(threads[i], NULL);
        WaitForSingleObject(thread[i],INFINITE);
        primes.insert(primes.end(), threadArgs[i].primes.begin(), threadArgs[i].primes.end());
        // cout << i << " joined" << endl;
    }
    time(&end);
    cout << primes.size() << endl;
    cout << "parallel delta time:" << difftime(end, begin)<< " seconds" << endl;

    return 0;
}