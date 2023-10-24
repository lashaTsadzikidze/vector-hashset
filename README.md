# Assignment 2

Building:
```
mkdir build && cd build
cmake ..
make
```

Compiled programms will be put in the build directory.

Building and running vector tests (inside the build directory):
```
make vectortest
./vectortest
```

Checking vector for memory leaks:
```
make vectortest
valgrind --leak-check=yes ./vectortest
```

Compiling and running hashset tests (inside the build directory):
```
make hashsettest
./hashsettest
```
Checking hashset for memory leaks:
```
make hashsettest
valgrind --leak-check=yes ./hashsettest
```

Extra tests - lookup words from thesaurus.txt:
```
make thesaurus-lookup
./thesaurus-lookup
```