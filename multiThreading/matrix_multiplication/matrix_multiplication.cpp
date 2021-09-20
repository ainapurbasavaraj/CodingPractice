// matrix_multiplication.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <cmath>
using namespace std;


void sequential_matrix_multiply(long** A, size_t num_rows_a, size_t num_cols_a,
    long** B, size_t num_rows_b, size_t num_cols_b,
    long** C)
{
    for (size_t i = 0; i < num_rows_a; i++) {
        for (size_t j = 0; j < num_cols_b; j++) {
            C[i][j] = 0;
            for (int k = 0; k < num_cols_a; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void parallel_matrix_multiply_helper(long** A, size_t num_rows_a, size_t num_cols_a,
    long** B, size_t num_rows_b, size_t num_cols_b, long** C, size_t start_row_c, size_t end_row_c) {

    for (size_t i = start_row_c; i < end_row_c; i++) {
        for (size_t j = 0; j < num_cols_b; j++) {
            C[i][j] = 0;
            for (int k = 0; k < num_cols_a; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/* parallel implementation of matrix multiply */
void parallel_matrix_multiply(long** A, size_t num_rows_a, size_t num_cols_a,
    long** B, size_t num_rows_b, size_t num_cols_b,
    long** C) {

    const size_t num_workers = std::thread::hardware_concurrency();
    size_t chunk_size = ceil((float)num_rows_a / num_workers);

    std::thread workers[3];
    for (size_t i = 0; i < num_workers; i++) {
        size_t start_row_c = std::min(i * chunk_size, num_rows_a);
        size_t end_row_c = std::min((i + 1) * chunk_size, num_rows_a);
        workers[i] = std::thread(parallel_matrix_multiply_helper, A, num_rows_a, num_cols_a,
            B, num_rows_b, num_cols_b,
            C, start_row_c, end_row_c);
    }
    for (auto& w : workers) {
        w.join();
    }
}

int main()
{
    const int NUM_EVAL_RUNS = 3;
    const size_t NUM_ROWS_A = 1000;
    const size_t NUM_COLS_A = 1000;
    const size_t NUM_ROWS_B = NUM_COLS_A;
    const size_t NUM_COLS_B = 1000;

    // intialize A with values in range 1 to 100    
    long** A = (long**)malloc(NUM_ROWS_A * sizeof(long*));
    if (A == NULL) {
        exit(2);
    }
    for (size_t i = 0; i < NUM_ROWS_A; i++) {
        A[i] = (long*)malloc(NUM_COLS_A * sizeof(long));
        if (A[i] == NULL) {
            exit(2);
        }
        for (size_t j = 0; j < NUM_COLS_A; j++) {
            A[i][j] = rand() % 100 + 1;
        }
    }

    // intialize B with values in range 1 to 100   
    long** B = (long**)malloc(NUM_ROWS_B * sizeof(long*));
    if (B == NULL) {
        exit(2);
    }
    for (size_t i = 0; i < NUM_ROWS_B; i++) {
        B[i] = (long*)malloc(NUM_COLS_B * sizeof(long));
        if (B[i] == NULL) {
            exit(2);
        }
        for (size_t j = 0; j < NUM_COLS_B; j++) {
            B[i][j] = rand() % 100 + 1;
        }
    }

    // allocate arrays for sequential and parallel results
    long** sequential_result = (long**)malloc(NUM_ROWS_A * sizeof(long*));
    long** parallel_result = (long**)malloc(NUM_ROWS_A * sizeof(long*));
    if ((sequential_result == NULL) || (parallel_result == NULL)) {
        exit(2);
    }
    for (size_t i = 0; i < NUM_ROWS_A; i++) {
        sequential_result[i] = (long*)malloc(NUM_COLS_B * sizeof(long));
        parallel_result[i] = (long*)malloc(NUM_COLS_B * sizeof(long));
        if ((sequential_result[i] == NULL) || (parallel_result[i] == NULL)) {
            exit(2);
        }
    }

    printf("Evaluating Sequential Implementation...\n");
    std::chrono::duration<double> sequential_time(0);
    sequential_matrix_multiply(A, NUM_ROWS_A, NUM_COLS_A, B, NUM_ROWS_B, NUM_COLS_B, sequential_result); // "warm up"

   
    for (int i = 0; i < NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        sequential_matrix_multiply(A, NUM_ROWS_A, NUM_COLS_A, B, NUM_ROWS_B, NUM_COLS_B, sequential_result);
        sequential_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    sequential_time /= NUM_EVAL_RUNS;

    printf("Evaluating Parallel Implementation...\n");
    std::chrono::duration<double> parallel_time(0);
    parallel_matrix_multiply(A, NUM_ROWS_A, NUM_COLS_A, B, NUM_ROWS_B, NUM_COLS_B, parallel_result); // "warm up"
    for (int i = 0; i < NUM_EVAL_RUNS; i++) {
        auto startTime = std::chrono::high_resolution_clock::now();
        parallel_matrix_multiply(A, NUM_ROWS_A, NUM_COLS_A, B, NUM_ROWS_B, NUM_COLS_B, parallel_result);
        parallel_time += std::chrono::high_resolution_clock::now() - startTime;
    }
    parallel_time /= NUM_EVAL_RUNS;

    // verify sequential and parallel results
    for (size_t i = 0; i < NUM_ROWS_A; i++) {
        for (size_t j = 0; j < NUM_COLS_B; j++) {
            if (sequential_result[i][j] != parallel_result[i][j]) {
                printf("ERROR: Result mismatch at row %ld, col %ld!\n", i, j);
            }
        }
    }
    printf("Average Sequential Time: %.2f ms\n", sequential_time.count() * 1000);
    printf("  Average Parallel Time: %.2f ms\n", parallel_time.count() * 1000);
    printf("Speedup: %.2f\n", sequential_time / parallel_time);
    printf("Efficiency %.2f%%\n", 100 * (sequential_time / parallel_time) / std::thread::hardware_concurrency());
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
