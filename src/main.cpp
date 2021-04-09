#include <cstddef>
#include <cstdio>
#include <bits/stdc++.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <climits>

#include "rapl-powercap.h"
#include "aes.h"
// #include "measure-no-unrolling.h"

using namespace std;

// Doesn't need a mutex since there will be only one thread that will modify it
bool proceed = true;

/*
    When compiling force loop enrolling
    Otherwise the for for the measurements loops will include other instructions as well

    Use this command to get an assembly file of the program:
        g++ main.cpp -fanalyzer -Wall -Wextra -S -O3 
            -Wall makes sure that all warnings during compilation are printed
            -Wetra enables extra warning flags

    Run as root
*/

void write_array_to_file(string& filename, long* measurements, size_t number_of_measurements);


// extern "C" void instruction_nop_100();
// extern "C" void instruction_nop_1000000();
// extern "C" void instruction_xor_100();
// extern "C" void instruction_xor_1000000();
// extern "C" void instruction_fscale_100();
// extern "C" void instruction_fscale_1000000();
// extern "C" void instruction_inc_100();
// extern "C" void instruction_inc_1000000();
// extern "C" void instruction_movl_100();
// extern "C" void instruction_movl_1000000();
// extern "C" void instruction_rdrand_100();
// extern "C" void instruction_rdrand_1000000();

void * thread_aes(void * arg)
{
    const string keyfile = "keys";
    const string outfile = "out.csv";
    analyse_AES(keyfile,outfile);
    proceed = false;
    return NULL;
}

void * thread_measure(void * arg) {
    fstream file_out;
    file_out.open("measurements.csv", ios::out);
    file_out.close();
    file_out<<"timestamp;measurement"<<endl;
    while(proceed) {
        fstream file_out;
        file_out.open("measurements.csv", ios::app);
        auto timestamp = std::chrono::high_resolution_clock::now();
        long measurement = get_energy_counter();
        file_out
            <<std::chrono::duration_cast<std::chrono::microseconds>(timestamp.time_since_epoch()).count()
            <<";"<<measurement<<endl;
        file_out.close();
    }
    return NULL;
}

int main() {
    // little check to remind me that I have to run the application as root
    auto me = getuid();
    auto myprivs = geteuid();
    if (getuid()) {
        cout<<"Run application as root in order to get access to the RAPL counter"<<endl;
        exit(1);
    }

    system("/bin/bash -c ./disable_dynamic_freq_scaling.sh");

    pthread_t threadId_aes;
    pthread_t threadId_measure;

    // somehow create shared variable between the 2 threads

    int err_aes = pthread_create(&threadId_aes, NULL, &thread_aes, NULL);
    int err_measure = pthread_create(&threadId_measure, NULL, &thread_measure, NULL);
    
    if (err_aes==-1){
        std::cout << "Thread (AES) creation failed : " << strerror(err_aes);
        exit(1);
    }
    if (err_measure==-1){
        std::cout << "Thread (measure) creation failed : " << strerror(err_measure);
        exit(1);
    }

    void* result_aes;
    err_aes = pthread_join(threadId_aes, &result_aes);
    cout<<"AES-thread was termineated"<<endl;
    void* result_measure;
    err_measure = pthread_join(threadId_measure, &result_measure);
    cout<<"measure-thread was terminated"<<endl;
    if (err_aes) {
        cout << "Failed to join Thread (AES) : " << strerror(err_aes) << endl;
        exit(1);
    }
    if (err_measure) {
        cout << "Failed to join Thread (AES) : " << strerror(err_measure) << endl;
        exit(1);
    }

    system("/bin/bash -c ./enable_dynamic_freq_scaling.sh");
    
    return 0;
}

void write_array_to_file(string& filename, long* measurements, size_t number_of_measurements) {
    fstream file_out;
    file_out.open(filename, std::ios_base::app);
    if (!file_out.is_open()) {
        cout << "failed to open " << filename << '\n';
    } else {
        file_out<<"Measurements"<<endl;
        for(size_t i=0;i<number_of_measurements;i++) {
            file_out<<measurements[i]<<endl;
        }
        file_out.close();
    }
}






