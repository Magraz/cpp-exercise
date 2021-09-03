#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

uint64_t factorial(uint64_t num){
    if(num == 1) return 1;
    else return num * factorial(num-1);
}

int main(int argc, char **argv)
{
    //Get log file path from parameters
    char *logFilePath{argv[argc - 1]};
    cout << "Log File Path: " << logFilePath << endl;

    //Open log file
    ofstream logFile;
    logFile.open(logFilePath);

    ifstream inputFile;
    inputFile.open("holi.dat");

    char data[10] {0};
    cout << "Reading from the file" << endl;

    vector<uint64_t> data_arr {};

    logFile << "Received data: " << endl;
    if(inputFile.is_open()){
        string data;
        while(getline(inputFile, data)){
            logFile << data << endl; //log received data
            
            //Convert string to int
            stringstream data_str(data);
            uint64_t data_int{};
            data_str >> data_int;

            //Add processed integers to array
            uint64_t data_fact {factorial(data_int)}; //calculate factorial
            if (data_fact < 100000000000) data_arr.push_back(data_fact);
        }
    }

    logFile << "Processed data: " << endl;
    for(auto x : data_arr) logFile << x << endl;

    logFile.close();
    inputFile.close();
    //Socket Server
    //int server, new_socket, valread;
    //struct sockadd

    //logFile << data << endl;
}
