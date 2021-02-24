#include <cstddef>
#include <cstdio>
#include <bits/stdc++.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "rapl-powercap.h"
// #include "measure-no-unrolling.h"

using namespace std;

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


extern "C" void instruction_nop_100();
extern "C" void instruction_nop_1000000();

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


int main() {

    system("/bin/bash -c ./disable_dynamic_freq_scaling.sh");

    int number_of_measurements = 10000;
    long measurements[number_of_measurements];
    for(int i=0;i<number_of_measurements;i++) {
        // filling up the pipeline
        instruction_nop_100();
        long start = get_energy_counter();
        instruction_nop_1000000();
        long stop = get_energy_counter();
        measurements[i] = (stop-start);
    }

    string filename = "nop.csv";
    write_array_to_file(filename, measurements, (size_t)number_of_measurements);

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
























