/**
 * Challenge: Download a collection of images
 */
#include <thread>
#include <cstring>
#include <future>
#include <iostream>
using namespace std;
 /* declarations for download_image helper function */
int download_image(int image_num);
size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp);

/* sequential implementation of image downloader */
size_t sequential_image_downloader(int num_images) {
    size_t total_bytes = 0;
    for (int i = 1; i <= num_images; i++) {
        total_bytes += download_image(i);
    }

    cout << "Totol bytes downloaded : " << total_bytes << endl;
    return total_bytes;
}

/* parallel implementation of image downloader */
size_t parallel_image_downloader(int num_images) {
    size_t total_bytes = 0;
    /***********************
     * YOUR CODE GOES HERE *
     ***********************/

    std::vector<std::future<int>> t;

    for (int i = 0; i < num_images; i++) {
        t.push_back(std::async(std::launch::async, download_image, i));
    }

    for (int i = 0; i < t.size(); i++) {
        total_bytes += t[i].get();
    }

    cout << "Totol bytes downloaded : " << total_bytes << endl;
    return total_bytes;
}

/* helper function to download a single image and return size in bytes */
int download_image(int image_num) {
    
    std::cout << "Counting started by thread : " << std::this_thread::get_id() << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return (image_num%5);
}

/* support function for the download_image helper function */
size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
    return size * nmemb;
}

int main() {
    const int NUM_EVAL_RUNS = 3;
    const int NUM_IMAGES = 10;

    printf("Evaluating Sequential Implementation...\n");
    std::chrono::duration<double> sequential_time(0);
    size_t sequential_result = sequential_image_downloader(NUM_IMAGES); // "warm up"
    for (int i = 0; i < NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        sequential_image_downloader(NUM_IMAGES);
        sequential_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    sequential_time /= NUM_EVAL_RUNS;

    printf("Evaluating Parallel Implementation...\n");
    std::chrono::duration<double> parallel_time(0);
    size_t parallel_result = parallel_image_downloader(NUM_IMAGES); // "warm up"
    for (int i = 0; i < NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        parallel_image_downloader(NUM_IMAGES);
        parallel_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    parallel_time /= NUM_EVAL_RUNS;

    // display sequential and parallel results for comparison
    if (sequential_result != parallel_result) {
        printf("ERROR: Result mismatch!\n  Sequential Result = %zd\n  Parallel Result = %zd\n", sequential_result, parallel_result);
    }
    printf("Average Sequential Time: %.2f ms\n", sequential_time.count() * 1000);
    printf("  Average Parallel Time: %.2f ms\n", parallel_time.count() * 1000);
    printf("Speedup: %.2f\n", sequential_time / parallel_time);
    printf("Efficiency %.2f%%\n", 100 * (sequential_time / parallel_time) / std::thread::hardware_concurrency());
}