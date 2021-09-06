# cpp-exercise
This repository contains the code for the Pinnacle Aerospace Technical Exercise.

## Description
The exercise consists on two source files that use socket programming to communicate through port 8080 as client(program_a.cpp) and server(program_b.cpp). They have to be run and compiled separately since they are two different applications. 
* program_a.cpp
   This program acts as the client and sends a sorted array of 10 random numbers from [1-20] to the server.

* program_b.cpp
   This program acts as the server and reads the data sent from the client, calcultes the factorial of each number in the array, and logs the resulting array.
