# cpp-exercise
This repository contains the code for the Pinnacle Aerospace Technical Exercise.

## Description
This repo requires to be compiled under a Linux based OS. The exercise consists on two source files that use socket programming to communicate through port 8080 as client(program_a.cpp) and server(program_b.cpp). They have to be run and compiled separately since they are two different applications.
* program_a.cpp
   - This program acts as the client and sends a sorted array of 10 random numbers from [1-20] to the server.

* program_b.cpp
   - This program acts as the server and reads the data sent from the client, calcultes the factorial of each number in the array, and logs the resulting array.

## How to run
First we need to compile both files, for this we will open 2 terminals(both terminals must be open at this repo's folder) and execute the following code.
* Terminal #1
```
g++ program_a -o program_a
```
* Terminal #2
```
g++ program_b -o program_b
```

Now we run the server first because otherwise the client will log "Transmission failed", and we run the client afterwards.
* Terminal #2
```
./program_b <'logFileName'> <'-a' if we want to append or nothing if we want to overwrite>

EXAMPLES:
./program_b server.log 
./program_a client.log -a
```
* Terminal #1
```
./program_a <'logFileName'> <'-a' if we want to append or nothing if we want to overwrite>

EXAMPLES:
./program_a client.log
./program_a client.log -a
```

