#include <iostream>
#include <vector>
#include <cmath>
#include <string.h>
#include <time.h>
#include <omp.h>

using namespace std;

const int THREAD_NUM = 5;
vector<int> primes;

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

int main(void)
{
    const int N = 10000000;

    time_t begin, end;
    time(&begin);
   
    #pragma omp parallel num_threads(THREAD_NUM)
    {
	    for (int i = 2 + omp_get_thread_num(); i <= N; i += THREAD_NUM)
	    {
	        if (isPrime(i))
	        {
	        	#pragma omp critical
	            primes.push_back(i);
	        }
	    }
    }  
    
    cout << primes.size() << endl;
    time(&end);
    cout << "concurrent delta time:" << difftime(end, begin) << " seconds" << endl;
    
    return 0;
}