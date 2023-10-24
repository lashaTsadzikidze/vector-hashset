[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/WxRlzYnw)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-718a45dd9cf7e7f842a935f5ebbe5719a5e09af4491e668f4dbf3b35d5cca122.svg)](https://classroom.github.com/online_ide?assignment_repo_id=12254327&assignment_repo_type=AssignmentRepo)
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