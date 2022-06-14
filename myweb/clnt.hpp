#include <iostream>

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class client
{
public:
    client(std::string ip, std::string portnumber);
    ~client();

private:
    std::string _portNumber;
    int _servSock;
    int _clntSock;

}