#include "library.h"

int main() {

    /*
     * kernel allocates memory :
     * TCP control block
     * send/receive buffers
     * file descriptor entry
     */
    int serverSocketFD = createTCPIpv4Socket();

    if (serverSocketFD < 0) {
        perror("server socket failed");
        exit(EXIT_FAILURE);
    }


    /* " " binds to:
    All local interfaces
    127.0.0.1
    Ethernet IP
    WiFi IP */
    struct sockaddr_in *serverAddress = createIPv4Address("", 2000);



    /*
     * associate socket with local port (2000)
     * reserves port
     * marks socket as passive
     * if another process already uses that port it returns errno = EADDRINUSE
     */
    int result = bind(serverSocketFD, (struct sockaddr *) serverAddress, sizeof(struct sockaddr_in));

    if (result == 0) {
        printf("bind successful\n");
    }


    /* the number 10 is backlog size : maximum pending connections queue
     connection states for TCP is SYN_RECV queue and ESTABLISHED queue */
    int listenResult = listen(serverSocketFD, 10);

    struct sockaddr_in clientAddress;

    socklen_t clientAddressSize = sizeof(clientAddress);

    char buffer[1024];

    // --- Outer Loop: Keep server alive forever ---
    while (1) {
        printf("Waiting for new connection...\n");

        int client_socket_FD = accept(serverSocketFD, (struct sockaddr *) &clientAddress, &clientAddressSize);

        if (client_socket_FD < 0) {
            perror("accept failed");
            continue; // Don't kill server, just try again
        }

        printf("Client connected!\n");

        // --- Inner Loop: Handle this specific client ---
        while (1) {
            // Clear buffer to avoid old data artifacts
            memset(buffer, 0, sizeof(buffer));

            ssize_t amountReceived = recv(client_socket_FD, buffer, sizeof(buffer) - 1, 0);

            if (amountReceived > 0) {
                // Null-terminate explicitly (safe practice)
                buffer[amountReceived] = 0;
                printf("Received: %s\n", buffer);

                // Optional: Send confirmation back?
                // send(client_socket_FD, "Ack\n", 4, 0);

            } else if (amountReceived == 0) {
                printf("Client disconnected cleanly.\n");
                break; // Break INNER loop to close this client
            } else {
                perror("recv failed");
                break; // Break INNER loop on error
            }
        }

        // CRITICAL: Close the socket when done with this client
        close(client_socket_FD);
        printf("Connection closed. Ready for next client.\n\n");
    }

    free(serverAddress);
    close(serverSocketFD);
    shutdown(serverSocketFD, SHUT_RDWR);

    return 0;

}
