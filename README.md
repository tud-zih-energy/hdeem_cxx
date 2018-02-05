# hdeem_cxx

hdeem_cxx is an header only c++ abstraction for the hdeem c api.
For details about the hdeem c api please have a look at:

[https://doc.zih.tu-dresden.de/hpc-wiki/bin/view/Compendium/EnergyMeasurement](https://doc.zih.tu-dresden.de/hpc-wiki/bin/view/Compendium/EnergyMeasurement)

[https://tu-dresden.de/zih/forschung/projekte/hdeem](https://tu-dresden.de/zih/forschung/projekte/hdeem)

For citing HDEEM please use [[DOI: 10.1109/E2SC.2014.13](dx.doi.org/10.1109/E2SC.2014.13)]

## Using hdeem_cxx

```c++
 #include "hdeem_cxx.hpp"
int main(int argc, char** argv) {

hdeem::connection hdeem;
/**
 * Be sure to init HDEEM before any other code, especially before you 
 * fork processes, threads, or allocate a huge amount of memory. 
 **/

//some other init code

hdeem.start();

// something to measure

hdeem.stop();

auto stats = hdeem.get_stats();
std::cout << "Blade energy: " << stats.energy(hdeem::sensor_id::blade(0)) << "\n";
std::cout << "Blade power: " << stats.average(hdeem::sensor_id::blade(0)) << "\n";
}

```

## Build

You need to link freeipmi and rt additionaly to the originonal hdeem module.

```
g++ test.cpp -std=c++14 -o test -I./hdeem_cxx/include/ -lhdeem -lfreeipmi -lrt
```

## Contact
If you like to have more details about HDEEM, or how to use the measurement hdeem_cxx please write to:

thomas.ilsche@tu-dresden.de

mario.bielert@tu-dresden.de

andreas.gocht@tu-dresden.de
