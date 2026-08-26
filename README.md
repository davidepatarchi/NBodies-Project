# Simulation of an N-Body system   
Here are reported all the necessary steps to run a N-Bodies simulation:

## File selection
The first thing to do is to select a configuration of planets. All the configurations are placed in the `data/` directory. 
```bash
$ pwd
/home/davidepatarchi/programmazione_fisica/pf_progetto/NBodies-Project
$ cd data/
$ tree
.
├── 3bodychaos.txt
├── asteroids.txt
├── collision1.txt
├── dwarfdance.txt
├── figure8.txt
├── solarsystem.txt
├── triangle.txt
└── twinsuns.txt
```
Once the data file has been chosen, open the file `main.cpp` and, at line 20, write the name of the file inside the `read_file` function (here is an example using the data file `solarsystem.txt`):
```c++
...
  // READING FILE WITH PLANETS DATA
  planets.read_file("data/solarsystem.txt");
...
```

## Building process
To compile the project, go back to the terminal and run the following commands to build it correctly with `CMake`:
```bash
$ pwd
/home/davidepatarchi/programmazione_fisica/pf_progetto/NBodies-Project
$ cmake -S . -B build -G"Ninja Multi-Config"
$ cmake --build build --config Debug
$ cmake --build build --config Debug --target test
$ cmake --build build --config Release
$ cmake --build build --config Release --target test
```
The project is now compiled.

## Tests and running process
To check that all the tests passed correctly, both in `Debug` and in `Release`, proceed as follows:
```bash
$ pwd
/home/davidepatarchi/programmazione_fisica/pf_progetto/NBodies-Project
$ cd build/Debug
$ ./progetto.t
$ cd ../Release
$ ./progetto.t
```
If all the tests pass correctly, you can move on to the last step: running the project.
```bash
$ pwd
/home/davidepatarchi/programmazione_fisica/pf_progetto/NBodies-Project
$ cd build/Debug
$ ./progetto
$ cd ../../build/Release
$ ./progetto
```
Once the executables are running, you will be asked how many days the simulation should last (enter a value greater than 1). After that, a graphical window will open, showing the evolution of the planets. Once the simulation is finished, close the graphical window to print, in the terminal, the analysis of the conservation of energy, momentum, and angular momentum.
