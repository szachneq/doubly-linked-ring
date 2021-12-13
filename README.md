# Doubly Linked Ring

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
$ ./run.sh
```

Run tests:
```bash
$ (cd build && ctest)
```
or
```bash
$ ./test.sh
```

Run memory leak test:
```bash
$ ./memcheck.sh
```

> Note: For ```./run.sh```, ```./test.sh``` and ```./memcheck.sh``` scripts to run you might have to run this command

```bash
$ chmod +x run test memcheck
```
