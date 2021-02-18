#include <stdio.h>
#include "rapl-powercap.h"

using namespace std;

/*
    Behavior is not as expected: when compiling the code and analysing the assembly file
    it is clear that the assembly instruction "instr" is executed in a for loop.
    This causes that the power-measurement includes jmp and incr instructions as well.
    In order to get reliable measurements this can't happen. Therefore I tried to make the 
    compiler unroll the for loops. This however didn't actually have the wanted behaviour.
    To deal with this another approach was taken: writing the methods fully in assembly.
*/

void measure_energy_of_mv(long* measurements, size_t number_of_measurements);
void measure_energy_of_fscale();
void measure_energy_of_xor(long* measurements, size_t number_of_measurements);
void measure_energy_of_inc(long* measurements, size_t number_of_measurements);
void measure_energy_of_rdrand(long* measurements, size_t number_of_measurements);
void measure_energy_of_nop(long* measurements, size_t number_of_measurements);

__attribute__((optimize("unroll-loops")))
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

__attribute__((optimize("unroll-loops")))
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


__attribute__((optimize("unroll-loops")))
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


__attribute__((optimize("unroll-loops")))
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


__attribute__((optimize("unroll-loops")))
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

__attribute__((optimize("unroll-loops")))
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