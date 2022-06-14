#include "server.hpp"

int main(int ac, char** av)
{
    if (ac != 2)
    {   
        std::cerr << "ac error" << std::endl;
        exit(1);
    }
    std::string str = av[1];
    server serv(str);
    return(0);
}