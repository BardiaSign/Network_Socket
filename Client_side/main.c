/*
* 1 - Creates a TCP socket
* 2 - Builds an IPv4 address structure
* 3 - Establishes a TCP connection using connect()
* 4 - Reads user input from stdin
* 5 - Sends data to the server using send()
* 6 - Terminates when "exit" is entered
 */

#include "library.h"

int main() {

    int socketFD = createTCPIpv4Socket();

    if (socketFD < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // here sockaddr_in reserve 16 bits but we just need
    struct sockaddr_in *address = createIPv4Address("127.0.0.1", 2000);

    // Establish TCP Connection
    const int result = connect(socketFD, (struct sockaddr *)address, sizeof(struct sockaddr_in));

    if (result == 0) {
        printf("connected to server\n");
    }else if (result < 0) {
        perror("connect failed");
        close(socketFD);
        exit(EXIT_FAILURE);
    }

    // Input Buffer Setup
    char *line = NULL;
    size_t line_size = 0;
    printf("Waiting for connection...\n");

    while (1) {
        // 1. Clearer prompt with flush ensures it appears immediately
        printf("Your message (or 'exit'): ");
        // tells the computer: "Do not wait. Take whatever is currently in the buffer and send it to the screen right now."
        fflush(stdout);

        // 2. Read input. better then scanf() and get()
        //['e', 'x', 'i', 't', '\n', '\0']
        ssize_t charCount = getline(&line, &line_size, stdin);

        // 3. Handle End-Of-File (Ctrl+D) or Error
        if (charCount == -1) {
            if (feof(stdin)) {
                // User pressed Ctrl+D.
                printf("User signaled exit. Goodbye!\n");
            }
            else if (ferror(stdin)) {
                // Something went wrong with the system/OS.
                fprintf(stderr, "Critical error reading from stdin!\n");
                perror("System Error Details");
            }
            break;
        }

        // 4. Strip the newline character for cleaner processing
        // This changes "exit\n" to "exit"
        if (charCount > 0 && line[charCount - 1] == '\n') {
            line[charCount - 1] = '\0';
            charCount--; // Decrease count since we removed a char
        }

        // 5. Check for exit command
        if (strcmp(line, "exit") == 0) {
            printf("Closing connection.\n");
            break;
        }

        // 6. Send data (restore newline if the server expects it, or send as is)
        // Note: If your server expects a newline, you might want to send 'charCount + 1'
        // and skip step 4, or manually append it back.

        // For this example, we assume we send exactly what is typed (without newline)
        ssize_t amountSent = send(socketFD, line, charCount, 0);

        if (amountSent < 0) {
            perror("send failed");
            break; // Usually fatal for the connection
        }
    }
    free(line);


    return 0;
}