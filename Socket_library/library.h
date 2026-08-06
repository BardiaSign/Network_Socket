#ifndef SOCKET_LIBRARY_LIBRARY_H
#define SOCKET_LIBRARY_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

void do_work(int socketFD);
int createTCPIpv4Socket();
struct sockaddr_in *createIPv4Address(char *ip, int port);

#endif // SOCKET_LIBRARY_LIBRARY_H