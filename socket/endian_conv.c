#include <stdio.h>
#include <arpa/inet.h>

int main(int ac, char **av)
{
	unsigned short host_port = 0x1234;
	unsigned short net_port;
	unsigned long  host_addr = 0x12345678;
	unsigned long  net_addr;

	net_port = htons(host_port);
	net_addr = htonl(host_addr);

	printf("Host order port %#x\n", host_port);
	printf("Network order port %#x\n", net_port);
	printf("Host order address %#lx\n", host_addr);
	printf("Network order port %#lx\n", net_addr);
	return (0);
}

