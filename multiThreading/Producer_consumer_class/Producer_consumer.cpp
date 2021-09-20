// Producer_consumer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <future>
#include <deque>
#include <mutex>
#include <condition_variable>
using namespace std;


class prod_consume {

public:
    void produce() {
        while (1) {
            std::unique_lock<mutex> lock(_lock);
            _cond.wait(lock, [&]() {
                return shared_queue.empty();
                });
            static int num_times_produce = 0;
            for (int i = 0; i < 200; i++) {
                shared_queue.push_back(i);
            }

            cout << "I am done producing " << endl;
            num_times_produce++;

            if (num_times_produce >= 3) {
                _cond.notify_one();
                break;
            }
            _cond.notify_one();
        }
    }

    void consume() {
        while (1) {
            std::unique_lock<mutex> lock(_lock);
            auto now = std::chrono::system_clock::now();
            auto status = _cond.wait_until(lock, now+100ms, [&]() {
                return (!shared_queue.empty()); });
            if (!status) {
                cout << " Nothing more to consume and finished waiting. Good Bye!! " << endl;
                break;
            }
            {
                int data = shared_queue.front();
                cout << "Consumed : " << data << endl;
                shared_queue.pop_front();

                if (shared_queue.empty()) {
                    cout << "I am done consuming" << endl;
                    
                    _cond.notify_one();
                }                
            }
        }
    }

private:
    deque<int> shared_queue;
    mutex _lock;
    condition_variable _cond;
};



int main()
{
    prod_consume obj;
    std::thread prod(&(prod_consume::produce), &obj);
    std::thread consume(&(prod_consume::consume), &obj);

    prod.join();
    consume.join();

}