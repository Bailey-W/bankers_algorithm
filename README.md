#Banker's Algorithm
##Input File
The input file should be formatted as follows:
```
3 5  // The number of resources followed by the number of processes
0 1 0 7 5 3 // The first three numbers on each line are the allocated resources
2 0 0 3 2 2 // The next three numbers on each line are the maximum resources
3 0 2 9 0 2 // Do this for every process
2 1 1 2 2 2
0 0 2 4 3 3
3 3 2  //The final line is the available resources that the algorithm starts with
```

So the above input file would generate the following matrices:
```
Allocated:
P0  0 1 0
P1  2 0 0
P2  3 0 2
P3  2 1 1
P4  0 0 2
```
```
Max:
P0  7 5 3
P1  3 2 2
P2  9 0 2
P3  2 2 2
P4  4 3 3
```
```
Available:
3 3 2
```

The file **MUST** be named "input.txt" and be in the same directory as bankers

##Building and running
To build and run the program, run the following commands:
```
g++ bankers.c -o bankers
./bankers
```
