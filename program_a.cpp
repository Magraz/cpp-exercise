#include <iostream>
#include <fstream>
#include <random>
#include <bits/stdc++.h>
#include <sys/socket.h>

using namespace std;

int main(int argc, char **argv){
    //Get log file path from parameters
    char* logFilePath {argv[argc-1]};    
    cout << "Log File Path: "<< logFilePath << endl;

    //Open log file
    ofstream logFile;
    logFile.open(logFilePath);

    //Generate random number list
    random_device rd;                         // obtain a random number from hardware
    mt19937 gen(rd());                        // seed the generator
    uniform_int_distribution<> distr(1, 20); // define the range
    vector<int> randomNumberList{};

    for (int n = 0; n < 10; ++n) randomNumberList.push_back(distr(gen)); // generate numbers

    //Sort the numbers in ascending order
    sort(randomNumberList.begin(), randomNumberList.end());

    for(auto x : randomNumberList){
        logFile << x << endl;
    }

    //Close log file
    logFile.close();

    //Socket Server 
    //int server, new_socket, valread;
    //struct sockadd

    //logFile << data << endl;

}
