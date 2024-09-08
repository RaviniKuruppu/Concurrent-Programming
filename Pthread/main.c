#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "serial.h"
#include "mutex.h"
#include "rw_lock.h"

void calculateStats(double *cpu_time_list, int num_of_runs, double *mean, double *std_dev)
{
    double sum = 0.0;
    double sum_of_squared_diff = 0.0;

    // Calculate the sum of all elements
    for (int i = 0; i < num_of_runs; i++)
    {
        sum += cpu_time_list[i];
    }

    // Calculate the mean (average)
    *mean = sum / num_of_runs;

    // Calculate the sum of squared differences from the mean
    for (int i = 0; i < num_of_runs; i++)
    {
        sum_of_squared_diff += pow(cpu_time_list[i] - *mean, 2);
    }

    // Calculate the standard deviation
    *std_dev = sqrt(sum_of_squared_diff / num_of_runs);
}

int main(){
    unsigned long serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime, mut_t8_runtime, rw_t1_runtime,  rw_t2_runtime, rw_t4_runtime, rw_t8_runtime;

    // Number of samples
    const int N = 4;

    // Number of operations
    int m = 10000;

    // Fractions for each case
    int member_frac;
    int insert_frac;
    int delete_frac;

    double mean = 0.0;
    double std_dev = 0.0;

    double cpu_time_list[N];

    // Use current time as seed for random generator
    srand(time(0));

    FILE *file;

    // Iterate for the 3 cases
    for (int i = 0; i < 3; i++) {
        switch (i) {
            case 0:
                file = fopen("output/Case_1.csv","w+");
                fprintf(file,"Serial, Mutex_t1, Mutex_t2, Mutex_t4, Mutex_t8, ReadWrite_t1, ReadWrite_t2, ReadWrite_t4, ReadWrite_t8\n");
                member_frac = lround(m * 0.99);
                insert_frac = lround(m * 0.005);
                delete_frac = lround(m * 0.005);
                break;

            case 1:
                file = fopen("output/Case_2.csv","w+");
                fprintf(file,"Serial, Mutex_t1, Mutex_t2, Mutex_t4, Mutex_t8, ReadWrite_t1, ReadWrite_t2, ReadWrite_t4, ReadWrite_t8\n");
                member_frac = lround(m * 0.9);
                insert_frac = lround(m * 0.05);
                delete_frac = lround(m * 0.05);
                break;

            case 2:
                file = fopen("output/Case_3.csv","w+");
                fprintf(file,"Serial, Mutex_t1, Mutex_t2, Mutex_t4, Mutex_t8, ReadWrite_t1, ReadWrite_t2, ReadWrite_t4, ReadWrite_t8\n");
                member_frac = lround(m * 0.5);
                insert_frac = lround(m * 0.25);
                delete_frac = lround(m * 0.25);
                break;

            default:
                break;
        }

        for (int j = 0; j < N; j++)
        {
            serial_runtime = serialExecution(m, member_frac, insert_frac, delete_frac);
            mut_t1_runtime = mutexExecution(m, member_frac, insert_frac, delete_frac, 1);
            mut_t2_runtime = mutexExecution(m, member_frac, insert_frac, delete_frac, 2);
            mut_t4_runtime = mutexExecution(m, member_frac, insert_frac, delete_frac, 4);
            mut_t8_runtime = mutexExecution(m, member_frac, insert_frac, delete_frac, 8);
            rw_t1_runtime = readWriteExecution(m, member_frac, insert_frac, delete_frac, 1);
            rw_t2_runtime = readWriteExecution(m, member_frac, insert_frac, delete_frac, 2);
            rw_t4_runtime = readWriteExecution(m, member_frac, insert_frac, delete_frac, 4);
            rw_t8_runtime = readWriteExecution(m, member_frac, insert_frac, delete_frac, 8);
            cpu_time_list[j]=serial_runtime;

            fprintf(file,"%lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu\n",serial_runtime, mut_t1_runtime, mut_t2_runtime, mut_t4_runtime, mut_t8_runtime, rw_t1_runtime,  rw_t2_runtime, rw_t4_runtime, rw_t8_runtime);
        }
        printf("----------------------------- Case %d completed -----------------------------", i);
        // Calculate mean and standard deviation
        calculateStats(cpu_time_list, N, &mean, &std_dev);
        // Print the results
        printf("Mean (Average): %f\n", mean);
        printf("Standard Deviation: %f\n", std_dev);
        fclose(file);
    }
    return 0;
}