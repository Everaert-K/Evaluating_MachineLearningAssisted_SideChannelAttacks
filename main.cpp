#include <cstddef>
#include <cstdio>
#include <bits/stdc++.h> 
#include <unistd.h>

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

extern void instruction_nop_100();
int main() {


    instruction_nop_100();

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
























