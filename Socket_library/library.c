#include "library.h"


void do_work(int socketFD) {
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    if (setsockopt(socketFD, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        perror("setsockopt failed");
    }
}



/* It asks the kernel(core of OS) to allocate a new communication endpoint*/
int createTCPIpv4Socket() {

    /*
     * AF_INET : IPv4, AF_INET6 : IPv6, AF_unix : local IPC
     * SOCK_STREAM : TCP, SOCK_DGRAM : UDP
     * Chose default protocol(0)
     */
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //check for error
    if (sock < 0) {

        // explaining the error
        perror("socket creation failed");
        return -1;
    }
    return sock;
}

/* create structure for details about ip address
 * sockaddr_in : structure describing an internet socket address
 */
struct sockaddr_in *createIPv4Address(char *ip, int port) {

    // allocate 16 bits memory on the heap
    struct sockaddr_in *address = malloc(sizeof(struct sockaddr_in));

    // it have to be same to the domain in socket otherwise connect() will fail
    address->sin_family = AF_INET;

    /*
    * Host TO Network Short. it converts a 16-bit number from your computer's byte order to network byte order
    * htons() : host -> network, 16-bit (short)
    * htonl() : host -> network, 32-bit (long)
    * ntohs() : network -> host, 16-bit
    * ntohl() : network -> host, 32-bit
    */
    address->sin_port = htons(port);

    //convert IP format to binary format
    inet_pton(AF_INET, ip, &address->sin_addr.s_addr);

    return address;
}

