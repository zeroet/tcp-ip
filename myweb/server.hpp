#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>

class server
{
public:
    server(std::string portnumber);
    //server(const server& src);
    ~server();

    void error_handling(const std::string &message);

private:
    std::string _portNumber;

};