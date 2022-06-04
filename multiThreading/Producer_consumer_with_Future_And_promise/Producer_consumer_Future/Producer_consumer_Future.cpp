// Producer_consumer_Future.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <deque>
#include <future>
#include <mutex>
using namespace std;


class prod_consumer {

public:
    int produce(std::promise<bool>& pr) {
        pr.set_value(true);
        while (1) {
            for (int i = 0; i < 200; i++) {
                pipeline.push_back(i);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        return 1;
    }

    void process(int data) {
        if (data == 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        cout << std::this_thread::get_id << " is consuming... " << data << endl;
    }

    int consume(std::shared_future<bool>& fu) {
        /*auto is_set = fu.wait_for(std::chrono::milliseconds(10));
        if (future_status::ready != is_set) {
            cout << "producer is not producing " << endl;
            return;
        }*/

        bool result = false;
        try {
            result = fu.get();
        }
        catch (exception e) {
            cout << " Producer didnt keep promise!" << e.what() << endl;
            return -1;
        }
        
        if (result) {
            while (1) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                int data = 0;
                std::lock_guard<mutex> lock(_lock);
                {
                    if (!pipeline.empty()) {
                        data = pipeline.front();
                        pipeline.pop_front();
                    }
                }
                process(data);
            }
        }

        return 1;
    }

private:
    deque<int> pipeline;
    mutex _lock;
};
int main()
{
    prod_consumer obj;
    std::promise<bool> pr;
    std::future<bool> fu = pr.get_future();
    std::shared_future<bool> sf = fu.share();
    //std::thread t1(&(prod_consumer::produce),&obj, std::ref(pr));
    //std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    //std::thread t3(&(prod_consumer::consume),&obj, std::move(fu));

    auto resut1 = std::async(std::launch::async, &(prod_consumer::produce), &obj, std::ref(pr));

    

    auto result2 = std::async(std::launch::async, &(prod_consumer::consume), &obj, std::ref(sf));
    auto result3 = std::async(std::launch::async, &(prod_consumer::consume), &obj, std::ref(sf));
    auto result4 = std::async(std::launch::async, &(prod_consumer::consume), &obj, std::ref(sf));
    auto result5 = std::async(std::launch::async, &(prod_consumer::consume), &obj, std::ref(sf));
    auto result6 = std::async(std::launch::async, &(prod_consumer::consume), &obj, std::ref(sf));

    //result2.wait();
    //resut1.wait_for(std::chrono::milliseconds(100));
    
    //t1.join();
    //t3.join();
}
