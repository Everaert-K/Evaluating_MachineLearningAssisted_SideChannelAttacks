#include <iostream>
#include <fstream>
#include <chrono> 
#include <algorithm>

using namespace std;
using namespace std::chrono; 

long get_energy_counter();

void get_rapl_upate_rate() {
    int number_of_measurements = 30;
    int measurements[number_of_measurements];
    for(int i=0;i<number_of_measurements;i++) {
        long value1 = get_energy_counter();
        auto start = high_resolution_clock::now(); 
        long value2 = get_energy_counter();
        while(value2!=value1) {
            value2 = get_energy_counter();
        }
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<microseconds>(stop - start); 
        measurements[i]=duration.count(); 
    }
    sort(measurements,measurements+number_of_measurements);
    cout<<"Median update rate is: "<<measurements[15]<<" microseconds"<<endl; 
    int mean = 0;
    for(int i=0;i<number_of_measurements;i++) {
        mean += measurements[i];
    }
    mean /= number_of_measurements;
    cout<<"Mean update rate is: "<<mean<<" microseconds"<<endl; 
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