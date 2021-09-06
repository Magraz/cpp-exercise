#include <iostream>
#include <fstream>
#include <random>
#include <bits/stdc++.h>
#include <sstream>
#include <vector>
#include <algorithm>

//Socket libraries
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

//*Constants
const int PORT = 8080;
const int MAX_ARR_SIZE = 10;

int main(int argc, char **argv){

    ////* ARGUMENTS CHECK *////

    //Check the number of arguments
    if (argc > 3){
        cerr << "Too many arguments!" << endl;
        return -1;
    }
    else if (argc == 1){
        cout << "Usage './program_a <'logFileName'> <'-a' to append or leave empty to overwrite>'" << endl;
        return 0;
    }

    ////* LOG FILE SETUP *////

    //Get log file path from parameters
    char *logFilePath{argc == 3 ? argv[argc - 2] : argv[argc - 1]};

    //Determine how to open logfile if in append or overwrite mode(this is the default mode)
    ofstream logFile;
    if(argc == 3){
        char *openMode = argv[argc - 1];
        if ((openMode[0] == '-') && (openMode[1] == 'a')) logFile.open(logFilePath, ios::app);
        else {
            cerr << "Invalid open mode!" << endl;
            return -1;
        };
        
    }
    else logFile.open(logFilePath, ios::trunc);

    cout << "Log file path: " << logFilePath << endl;

    ////* REQUEST GENERATION *////

    //Generate random number list
    random_device rd;                         // obtain a random number from hardware
    mt19937 gen(rd());                        // seed the generator
    uniform_int_distribution<> distr(1, 20); // define the range
    vector<int> randomNumberList{};

    for (int n = 0; n < MAX_ARR_SIZE; ++n) randomNumberList.push_back(distr(gen)); // generate numbers

    //Sort the numbers in ascending order
    sort(randomNumberList.begin(), randomNumberList.end());

    //Convert vector<int> to string
    stringstream ss;
    copy(randomNumberList.begin(), randomNumberList.end(), ostream_iterator<int>(ss, ",")); //copy int to string, and format as comma separated values
    string data_str = ss.str();
    data_str = data_str.substr(0, data_str.length() - 1); // get rid of the trailing space

    //Log and setup data to send
    cout << "Sending data: " << data_str << endl;

    ////* SOCKET CLIENT SETUP *////

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *data = &*data_str.begin(); //get pointer to first char in data_str
    char buffer[1024] = {0};

    //Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
        cout << "Invalid address/ Address not supported" << endl; 
        return -1;
    }

    //Perform connection
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        cout << "Transmission failed!" << endl;
        logFile << "Transmission failed!" << endl;
        
    } else {
        //Send data
        send(sock, data, strlen(data), 0);
        cout << "Data sent: " << data << endl;
        valread = read(sock, buffer, 1024);
        cout << "Transmission succeeded message from server: " << buffer << endl; //Should read "Transmisssion succeded message from server: XXXX" when connection succeeds
        logFile << "PROGRAM_A: " << "Transmission succeeded message from server: " << buffer << endl;
    }

    //Get exit key press and log it
    cout << "Enter any key to exit: " << endl;
    char exitKey = getchar();
    logFile << "PROGRAM_A: " << "Program finished" << endl;
    logFile << "PROGRAM_A: " << "Exit key: " << exitKey << endl;

    //Close log file
    logFile.close();

    return 0;
}
