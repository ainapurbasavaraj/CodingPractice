// Odd_Even.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

int N = 1;
mutex _lock;
condition_variable cond;

void odd() {

    std::unique_lock<mutex> ul(_lock);
    while (N < 10) {
        cond.wait(ul, []() {
            return (N % 2 != 0);
            });
        cout << N << endl;
        N++;
        cond.notify_one();
    }
    cout << "odd thread ends" << endl;
}

void even() {
    std::unique_lock<mutex> ul(_lock);
    while (N <=10 ) {
        cond.wait(ul, []() {
            return (N % 2 == 0);
            });
    
        cout << N << endl;
        N++;
        cond.notify_one();
    }

    cout << "even thread ends" << endl;
}

int main()
{
    std::thread t1(odd);
    std::thread t2(even);

    t1.join();
    t2.join();

    cout << "main thread ends" << endl;
}

