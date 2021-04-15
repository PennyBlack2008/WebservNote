#include <stdio.h>
#include <netinet/in.h>

int main(int argc, char* argv[])
{
	unsigned short int host_port = 0x1234; // 2 byte 저장
	unsigned short int net_port;
	unsigned int host_addr = 0x12345678; // 8 byte 저장
	unsigned int net_addr;

	net_port = htons(host_port);
	net_addr = htonl(host_addr);

	printf("Host ordered port: %#x\n", host_port);
	printf("Network ordered port: %#x\n", net_port);
	printf("Host ordered address: %#x\n", host_addr);
	printf("Network ordered address: %#x\n", net_addr);

	printf("unsigned short int : %lu\n", sizeof(unsigned short int)); // 2 bytes
	printf("unsigned int : %lu\n", sizeof(unsigned int)); // 8 bytes

	// printf("unsigned short int : %lu\n", sizeof(unsigned short int)); // 2 bytes
	// printf("unsigned long int : %lu\n", sizeof(unsigned long int)); // 8 bytes
	return (0);
}