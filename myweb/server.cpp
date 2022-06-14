#include "server.hpp"

void    server::error_handling(const std::string &message)
{
    std::cerr << message << std::endl;
    exit(1);
}

server::~server() {}

server::server (std::string portnumber) : _portNumber(portnumber)
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
       error_handling("socket() error");

}