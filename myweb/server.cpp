#include "server.hpp"

void    server::error_handling(const std::string &message)
{
    std::cerr << message << std::endl;
    exit(1);
}

server::~server() {}

server::server (std::string portnumber) : _portNumber(portnumber)
{
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    this->_servSock = socket(PF_INET, SOCK_STREAM, 0);
    if (this->_servSock == -1)
       error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(portnumber.c_str()));

    if (bind(this->_servSock,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");
    
    if (listen(this->_servSock, 5) == -1)
        error_handling("listen() error");
    
    std::cout << "Server Open Port : " << portnumber << std::endl;
    
    //epoll for multi clnt
    // while(1)
    // {
    //     clnt_addr_size = sizeof(clnt_addr);
    //     this->_clntSock = accept(_servSock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    //     if (this->_clntSock == -1)
    //         error_handling("accept() error");
    // }
}