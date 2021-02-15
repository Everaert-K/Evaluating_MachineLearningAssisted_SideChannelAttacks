#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h> 
#include <unistd.h>

using namespace std;

long get_energy_counter() {
    // "Returns the current energy counter in micro joules"
    fstream my_file;
	my_file.open("/sys/devices/virtual/powercap/intel-rapl/intel-rapl:0/energy_uj", ios::in);
    if(my_file.is_open()) {
        string line;
        getline(my_file,line);
        my_file.close();
        long value = stol(line);
        return value;
    }
    return 0;
}

/////////////////////////////////////////////////////////////
vector<long> measure_energy_of_nop() {
    int number_of_measurements = 10000;
    vector<long> measurements(number_of_measurements);
    for(int i=0;i<number_of_measurements;i++) {
        for(int j=0;j<100;j++) {
            __asm__ ("nop;");
        }
        long start = get_energy_counter();
        for(int z=0;z<1000;z++) {
            __asm__("nop;");
        }
        long end = get_energy_counter();
        cout<<(int)(end-start)/1000<<endl;
        measurements.push_back((int)(end-start)/1000);
    }
    sort(measurements.begin(), measurements.end()); 

    return measurements;
}
////////////////////////////////////////////////////////////////

vector<long> measure_energy_of_mv() {
    // return in picojoule
    int number_of_measurements = 10000;
    vector<long> measurements(number_of_measurements);
    for(int i=0;i<number_of_measurements;i++) {
        for(int j=0;j<100;j++) {
            __asm__ ("movl $20, %eax;");
        }
        long start = get_energy_counter();
        for(int z=0;z<1000000;z++) {
            __asm__("movl $20, %eax;");
        }
        long end = get_energy_counter();
        long difference = end-start;
        measurements.push_back(difference);
    }
    // sort(measurements.begin(), measurements.end()); 
    return measurements;
}

vector<long> measure_energy_of_fscale() {
    // return in picojoule
    int number_of_measurements = 10000;
    vector<long> measurements(number_of_measurements);
    for(int i=0;i<number_of_measurements;i++) {
        for(int j=0;j<100;j++) {
            __asm__ ("fscale;");
        }
        long start = get_energy_counter();
        for(int z=0;z<1000000;z++) {
            __asm__("fscale");
        }
        long end = get_energy_counter();
        long difference = end-start;
        measurements.push_back(difference);
    }
    // sort(measurements.begin(), measurements.end()); 
    return measurements;
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

void write_vector_to_file(string& filename, vector<long> measurements) {
    fstream file_out;

    file_out.open(filename, std::ios_base::app);
    if (!file_out.is_open()) {
        cout << "failed to open " << filename << '\n';
    } else {
        file_out<<"Measurements"<<endl;
        for(int i=0;i<measurements.size();i++) {
            file_out<<measurements.at(i)<<endl;
        }
        file_out.close();
    }
}

int main() {

    // vector<long> mov = measure_energy_of_mv();
    // string filename = "mov.csv";
    // write_vector_to_file(filename,mov);

    vector<long> fscale = measure_energy_of_fscale();
    string filename = "fscale.csv";
    write_vector_to_file(filename,fscale);


	return 0;
}