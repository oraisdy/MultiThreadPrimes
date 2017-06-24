#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>

using namespace std;

bool isPrime(int n)
{
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0)
            return false;

    return true;
}

vector<int> serial(int N)
{
    vector<int> primes;
    for (int i = 2; i <= N; i++)
    {
        if (isPrime(i))
        {
            primes.push_back(i);
            // cout << i << endl;
        }
    }
    return primes;
}

int main(void)
{
    int N = 10000000;
    time_t begin, end;
    time(&begin);

    cout <<  serial(N).size() << endl;

    time(&end);
    cout << "serial delta time:" << difftime(end, begin) << " seconds" << endl;
    return 0;
}