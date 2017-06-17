#include <iostream>
#include <vector>
#include <cmath>

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
    clock_t begin, end;
    begin = clock();

    cout <<  serial(N).size() << endl;

    end = clock();
    cout << "serial delta time:" << end - begin << endl;
    return 0;
}