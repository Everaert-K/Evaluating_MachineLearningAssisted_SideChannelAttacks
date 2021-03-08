#include <cstddef>
#include <cstdio>
#include <bits/stdc++.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <fstream>

#include <climits>

#include "rapl-powercap.h"
#include "aes.h"
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

// 1 int consists out of 32 bits
std::string int_to_hex(const int* integers) {
  std::stringstream stream;
  for(int i=0;i<4;i++) {
    stream << std::setfill ('0') << std::setw(sizeof(int)*2) 
        << std::hex << integers[i];
  }
  return stream.str();
}

void generate_keys(const int amount_of_keys, const string& output_filename) {
    // let's just generate 10 different keys for now
    ofstream myfile;
    myfile.open (output_filename, std::ofstream::out | std::ios_base::app);

    for(int i=0;i<amount_of_keys;i++) {
        int* integers = new int[4];
        for(int j=0;j<4;j++) {
            integers[j] = rand();
        }
        string hex = int_to_hex(integers);
        delete []integers;
        std::stringstream ss;
        ss << hex[0]<<hex[1];
        for (int i = 2; i < hex.size(); i+=2) {
            ss << ' ' << s[i] << s[i+1];
        }
        myfile<<ss.str()<<endl;
    }
    myfile.close();
}

void measure_energy_AES_with_key(const string& key, const string& output_filename) {
    ofstream myfile;
    myfile.open (output_filename, std::ofstream::out | std::ios_base::app);
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0;i<160;i++) { // has to be 16M??
        AES_encryption(key);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    myfile<<key<<";"
        <<std::chrono::duration_cast<std::chrono::microseconds>(start.time_since_epoch()).count()<<";"
        <<std::chrono::duration_cast<std::chrono::microseconds>(stop.time_since_epoch()).count()<<endl;     
}

void analyse_AES(const string& key_file, const string& output_filename) {
    //somehow get a bunch of keys
    // run over all this keys
    // ! write header to the csv file !!
}

int main() {
    /*
    const string key1 = "01 04 02 03 01 03 04 0A 09 0B 07 0F 0F 06 03 00";
    const string key2 = "01 04 02 07 A1 03 04 8A 09 0B 07 0F 0F 06 03 10";
    // AES_encryption(key);
    measure_energy_AES_with_key(key1);
    measure_energy_AES_with_key(key2);
    */

    // there are 32 bits in an integer
    const string keys = "keys";
    generate_keys(10, keys);

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




    /*
    system("/bin/bash -c ./disable_dynamic_freq_scaling.sh");

    int number_of_measurements = 10000;
    long measurements[number_of_measurements];
    for(int i=0;i<number_of_measurements;i++) {
        // filling up the pipeline
        instruction_movl_100();
        long start = get_energy_counter();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        instruction_movl_1000000();
        long stop = get_energy_counter();
        measurements[i] = (stop-start);
    }

    string filename = "movl.csv";
    write_array_to_file(filename, measurements, (size_t)number_of_measurements);

    system("/bin/bash -c ./enable_dynamic_freq_scaling.sh");

    */



















