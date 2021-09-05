#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

using namespace std;

//*Constants
const uint64_t FACTORIAL_LIMIT = 100000000000;
const int PORT = 8080;

//*Functions
uint64_t factorial(uint64_t num){
    if(num == 1) return 1;
    else return num * factorial(num-1);
}
vector<int> split(const string &s, char delimiter){
    vector<int> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)){
        tokens.push_back(stoi(token));
    }
    return tokens;
}

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
    if (argc == 3){
        char *openMode = argv[argc - 1];
        if ((openMode[0] == '-') && (openMode[1] == 'a'))
            logFile.open(logFilePath, ios::app);
        
        else{
            cerr << "Invalid open mode!" << endl;
            return -1;
        };
    }
    else logFile.open(logFilePath, ios::trunc);

    cout << "Log file path: " << logFilePath << endl;

    ////* SOCKET SERVER SETUP *////

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *response = "DONE!";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        cerr << "Socket failed";
        return -1;
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        cerr << "Set socket failed";
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0){
        cerr << "Bind failed";
        return -1;
    }
    if (listen(server_fd, 3) < 0){
        cerr << "Listening failed";
        return -1;
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0){
        cerr << "Connection not accepted";
        return -1;
    }

    //Read incoming request from client
    valread = read(new_socket, buffer, 1024);
    cout << "Request received: " << buffer << endl;
    logFile << "Request received: " << buffer << endl;

    //Send response to client
    send(new_socket, response, strlen(response), 0);
    cout << "Response sent: " << response << endl;
    
    ////* PROCESS RECEIVED DATA *////
    
    //Convert received data to string, and to vector afterwards
    string data_str(buffer); 
    vector<int> data_vect {split(data_str, ',')}; //input vector
    vector<uint64_t> result{}; //output vector

    //Run every element of the vector through the factorial function
    for(int n = 0; n < data_vect.size(); n++){
        uint64_t data_fact{factorial(data_vect[n])}; //calculate factorial
        if (data_fact < FACTORIAL_LIMIT) result.push_back(data_fact); //If factorial is less than 100 000 000 000 add it to the result vector 
    }
    
    //Log output
    logFile << "Processed data: " << endl;
    for(auto x : result) logFile << x << endl;

    //Get exit key press and log it
    cout << "Enter any key to exit" << endl;
    char exitKey = getchar();
    logFile << "Program finished." << endl << "Exit key: " << exitKey;
    
    //Close log file
    logFile.close();

    return 0;
}
