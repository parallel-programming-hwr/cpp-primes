#include <iostream>
#include <pthread.h>
#include <tuple>
#include <thread>

using namespace std;
using std::cout;

uint numThreads;

void *GetPrimes(void* start) {
    ulong num = (ulong) start;
    ulong incr = numThreads * 2;
    while (true) {
        bool  isPrime = true;
        if (num < 3 || num % 2 == 0) {
            num += incr;
            continue;
        }
        for (int i = 3; i < num/2; i += 2) {
            if (num % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            cout << num << "\n";
        }
        num += incr;
    }
}

int main() {
    numThreads = thread::hardware_concurrency();
    pthread_t threads[numThreads];
    long start = 1;
    int rc;
    for (int i = 0; i < numThreads; i++) {
        rc = pthread_create(&threads[i], NULL, GetPrimes, (void *)(start + (2*i)));
        if (rc) {
            cout << "Error";
            exit(-1);
        }
    }
    pthread_exit(NULL);
}

