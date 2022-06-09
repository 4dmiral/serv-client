#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h> // Can be used for daemon()
#include <netinet/in.h>
#include <strings.h>
#include <fstream>
#include <sstream>

// Try using setsid (use manpaged.ubuntu.com to find out how) 

using namespace std;

int main() {
    string bufferString;
    int PORT = 1984;
    int opt = 1;
    fstream ofs;
    string out_file_str;
    string out_file_name = "out.txt";
    string out_file_path = "/" + out_file_name;
    string tempStr;
    sockaddr_in clientAddr;
    int count = 0;

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    cout << "Creating socket... ";

    // socket(domain, type, protocol)
    int serv_s = socket(AF_INET, SOCK_STREAM, 0); // Change to AF_INET for communication between different devices, check that last field is valid?
    // use setsockopt if getting “address already in use”

    cout << serv_s << endl;
    cout << "Binding... ";

    setsockopt(serv_s, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    // bind(socket, local address, address length)
    int serv_b = bind(serv_s, (struct sockaddr*)&serverAddr, sizeof(serverAddr)); // Change INADDR_ANY to addr struct for communication between different devices

    cout << serv_b << endl;
    cout << "Listening... ";

    // listen for client (listen(socket, queue length))
    int serv_l = listen(serv_s, 3);

    cout << serv_l << endl;
    cout << "Accepting... ";

    socklen_t sin_size=sizeof(struct sockaddr_in);
    int cli_s = accept(serv_s, (struct sockaddr *)&clientAddr, &sin_size); // Change INADDR_ANY to addr struct for communication between different devices
    
    cout << cli_s << endl;

    while (true) {
        count++;
        char buffer[500];
        bzero(buffer, 500);
        ofs.open(out_file_name, ios::out | ios::trunc);
        ofs.close();

        while (buffer[0] == 0)
        {
            read(cli_s, buffer, 500);
        }

        bufferString = buffer;
        cout << count << ": " << bufferString << endl;

        ifstream out_file_if(out_file_name);
        ostringstream out_file_ostr;
        out_file_ostr << out_file_if.rdbuf();
        out_file_str = out_file_ostr.str();

        send(cli_s, "Message has been recieved by server.", 36, 0);
        
    }
}



