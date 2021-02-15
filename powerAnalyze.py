def get_energy_counter():
    "Returns the current energy counter in micro joules"
    f = open("/sys/devices/virtual/powercap/intel-rapl/intel-rapl:0/energy_uj")
    value = f.read() 
    value = value.replace(" ", "")  
    value = value.replace("\n", "")  
    f.close()
    return value

def reset_energy_counter():
    "Sets the energy counter of the system to 0"
    "Cant write to this file"
    f = open("/sys/devices/virtual/powercap/intel-rapl/intel-rapl:0/energy_uj","w")
    f.write("0\n")
    f.close()

def main():
    print(get_energy_counter())
    

main()




























