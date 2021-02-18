#include <iostream>
#include <fstream>

using namespace std;

long get_energy_counter();

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