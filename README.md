# 21Z-EADS-TASK2-Szachno-Jan

This project represents doubly linked ring

To build the project:
```bash
$ cmake -S . -B build

$ cmake --build build
```

Run the project:
```bash
$ ./build/21Z-EADS-TASK1-SZACHNO-JAN
```
or
```bash
$ ./run
```

Run tests:
```bash
$ (cd build && ctest)
```
or
```bash
$ ./test
```

Run memory leak test:
```bash
$ ./memcheck
```

> Note: For ```./run```, ```./test``` and ```./memcheck``` scripts to run you might have to run this command

```bash
$ chmod +x run test memcheck
```
