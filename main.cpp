#include <cstddef>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h> 
#include <unistd.h>

using namespace std;

/*
    When compiling force loop enrolling
    Otherwise the for for the measurements loops will include other instructions as well

    Use this command to get an assembly file of the program:
        g++ main.cpp -fanalyzer -Wall -Wextra -S -O3 

    Run as root
*/

long get_energy_counter();

void measure_energy_of_mv(long* measurements, size_t number_of_measurements);
void measure_energy_of_fscale();
void measure_energy_of_xor(long* measurements, size_t number_of_measurements);
void measure_energy_of_inc(long* measurements, size_t number_of_measurements);
void measure_energy_of_rdrand(long* measurements, size_t number_of_measurements);
void measure_energy_of_nop(long* measurements, size_t number_of_measurements);

void write_array_to_file(string& filename, long* measurements, size_t number_of_measurements);

int main() {

    long measurements[10000];
    measure_energy_of_nop(measurements,10000);
    string filename = "nop.csv";
    write_array_to_file(filename,measurements,10000);

	return 0;
}

long get_energy_counter() {
    // "Returns the current energy counter in micro joules"
    std::fstream my_file;
	my_file.open("/sys/devices/virtual/powercap/intel-rapl/intel-rapl:0/energy_uj", ios::in);
    if(my_file.is_open()) {
        string line;
        getline(my_file,line);
        my_file.close();
        long value = stol(line);
        return value;
    }
    else {
        cout<<"Run as root, can't open the file"<<endl;
        return 0;
    }
}

void measure_energy_of_mv(long* measurements, size_t number_of_measurements) {
    // return in picojoule
    for(size_t i=0;i<number_of_measurements;i++) {
        for(int j=0;j<100;j++) {
            /* 
            Goal of this for loop is to clean the pipeline of any other instructions 
            and get better measurements
            */
            __asm__ ("movl $20, %eax;");
        }
        long start = get_energy_counter();
        for(int z=0;z<1000000;z++) {
            __asm__("movl $20, %eax;");
        }
        long end = get_energy_counter();
        long difference = end-start;
        measurements[i] = difference;
    }
}

void measure_energy_of_fscale(long* measurements, size_t number_of_measurements) {
    // return in picojoule
    for(size_t i=0;i<number_of_measurements;i++) {
        for(int j=0;j<100;j++) {
            /* 
            Goal of this for loop is to clean the pipeline of any other instructions 
            and get better measurements
            */
            __asm__ ("fscale;");
        }
        long start = get_energy_counter();
        for(int z=0;z<1000000;z++) {
            __asm__("fscale");
        }
        long end = get_energy_counter();
        long difference = end-start;
        measurements[i] = difference;
    }
}

void measure_energy_of_xor(long* measurements, size_t number_of_measurements) {
    // return in picojoule
    for(size_t i=0;i<number_of_measurements;i++) {
        for(int j=0;j<100;j++) {
            /* 
            Goal of this for loop is to clean the pipeline of any other instructions 
            and get better measurements
            */
            __asm__ ("xor %eax, %eax;");
        }
        long start = get_energy_counter();
        for(int z=0;z<1000000;z++) {
            __asm__("xor %eax, %eax;");
        }
        long end = get_energy_counter();
        long difference = end-start;
        measurements[i] = difference;
    }
}

void measure_energy_of_inc(long* measurements, size_t number_of_measurements) {
    // return in picojoule
    for(size_t i=0;i<number_of_measurements;i++) {
        for(int j=0;j<100;j++) {
            /* 
            Goal of this for loop is to clean the pipeline of any other instructions 
            and get better measurements
            */
            __asm__ ("inc %eax;");
        }
        long start = get_energy_counter();
        for(int z=0;z<1000000;z++) {
            __asm__("inc %eax;");
        }
        long end = get_energy_counter();
        long difference = end-start;
        measurements[i] = difference;
    }
}

void measure_energy_of_rdrand(long* measurements, size_t number_of_measurements) {
    // return in picojoule
    for(size_t i=0;i<number_of_measurements;i++) {
        for(int j=0;j<100;j++) {
            /* 
            Goal of this for loop is to clean the pipeline of any other instructions 
            and get better measurements
            */
            __asm__ ("rdrand %eax;");
        }
        long start = get_energy_counter();
        for(int z=0;z<1000000;z++) {
            __asm__("rdrand %eax;");
        }
        long end = get_energy_counter();
        long difference = end-start;
        measurements[i] = difference;
    }
}

void measure_energy_of_nop(long* measurements, size_t number_of_measurements) {
    // return in picojoule
    for(size_t i=0;i<number_of_measurements;i++) {
        for(int j=0;j<100;j++) {
            /* 
            Goal of this for loop is to clean the pipeline of any other instructions 
            and get better measurements
            */
            __asm__ ("nop;");
        }
        long start = get_energy_counter();
        for(int z=0;z<1000000;z++) {
            __asm__("nop;");
        }
        long end = get_energy_counter();
        long difference = end-start;
        measurements[i] = difference;
    }
}

/*
int get_energy_of_instruction(string& instruction) {
    
    //Returns the energy used by an assembly instruction in micro joules
    //In order to mitigate the problem of noise the instruction will be executed 10000 times and the median value will be returned
    //In order to clear the pipelines from other instructions before every measurement the instruction will be executed 100 times

    //!! No cleaner way since __asm__ requires a literal as input !!

    int res = -1;
    if(instruction == "nop") {
        res =  get_energy_of_nop();
    }
    return res;
}
*/


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