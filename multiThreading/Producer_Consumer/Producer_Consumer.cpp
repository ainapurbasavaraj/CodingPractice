// Producer_Consumer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

class soup {

public:
    void produce_soup(int i) {
        std::unique_lock<mutex> uLock(lock);
        soup_queue.push(i);
        uLock.unlock();
        soup_served.notify_one();
    }

    int consume_soup() {

        std::unique_lock<mutex> uLock(lock);
        int consumed = 0;
        while (soup_queue.empty()) {
            soup_served.wait(uLock);
        }
        consumed = soup_queue.front();

        soup_queue.pop();
        return consumed;
    }

private:
    queue<int> soup_queue;
    mutex lock;
    condition_variable soup_served;
};

soup s;

void producer() {
    for (int i = 0; i < 10000; i++)
    {
        s.produce_soup(1);
    }
    s.produce_soup(-1);
    cout << "produced soup done\n " << endl;
}

void consumer() {
    int count = 0;
    while (1) {
        
        int consumed = s.consume_soup();
        if (consumed == -1) {
            cout << "consumed soup by thread : " << std::this_thread::get_id << " is : " << count << endl;
            s.produce_soup(-1);
            return;
        }
        else {
            count++;
        }
    }
}


int main()
{
    std::thread Basavaraj(producer);
    std::thread shweta(producer);
    std::thread pankaj(consumer);
    std::thread rahul(consumer);
    std::thread chetan(consumer);
    std::thread ankith(consumer);

    Basavaraj.join();
    shweta.join();
    pankaj.join();
    rahul.join();
    chetan.join();
    ankith.join();
    return 0;
}

