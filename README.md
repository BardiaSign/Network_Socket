# TCP Socket Communication Project

A learning project demonstrating **client-server communication** using TCP/IPv4 sockets in C. This project covers fundamental network programming concepts including socket creation, connection establishment, data transmission, and proper resource management.

## 📋 Overview

This project implements a simple but complete TCP client-server architecture:
- **Server** (`main__1_.c`): Listens for incoming connections and receives messages from clients
- **Client** (`main.c`): Connects to the server and sends user input
- **Shared Library** (`library.c`, `library.h`): Utility functions for socket operations

### What It Demonstrates

- TCP/IPv4 socket creation and configuration
- Server-side operations: `bind()`, `listen()`, `accept()`
- Client-side operations: `connect()`, `send()`, `recv()`
- Input/output handling with `getline()`
- Error handling and resource cleanup
- Socket timeouts and non-blocking I/O concepts

## 🔧 Building the Project

### Prerequisites

- GCC compiler or compatible C compiler
- Linux/Unix system (uses POSIX socket API)
- Standard C library headers

### Compilation

Compile the **server**:
```bash
gcc -o server library.c main__1_.c
```

Compile the **client**:
```bash
gcc -o client library.c main.c
```

## 🚀 Running the Project

### Terminal 1 - Start the Server
```bash
./server
```

Expected output:
```
bind successful
Waiting for new connection...
```

The server will wait for incoming client connections on `localhost:2000`.

### Terminal 2 - Start the Client
```bash
./client
```

Expected output:
```
connected to server
Waiting for connection...
Your message (or 'exit'): 
```

### Sending Messages

Type any message and press **Enter** to send it to the server:

```
Your message (or 'exit'): Hello, Server!
Your message (or 'exit'): This is a test message
Your message (or 'exit'): exit
Closing connection.
```

The server will display all received messages:
```
Client connected!
Received: Hello, Server!
Received: This is a test message
Client disconnected cleanly.
Ready for next client.
```

## 📁 Project Structure

```
.
├── library.h              # Function declarations
├── library.c              # Socket utility implementations
├── main.c                 # TCP Client implementation
└── main__1_.c             # TCP Server implementation
```

### File Descriptions

#### `library.h` / `library.c`
Core socket utility functions:

- **`createTCPIpv4Socket()`**: Creates a new TCP/IPv4 socket
  - Uses `AF_INET` for IPv4 and `SOCK_STREAM` for TCP
  - Returns file descriptor or -1 on error

- **`createIPv4Address(char *ip, int port)`**: Builds address structure
  - Allocates `sockaddr_in` structure on heap
  - Handles byte order conversion with `htons()` and `inet_pton()`
  - Supports binding to all interfaces with `""`

- **`do_work(int socketFD)`**: Configures socket timeout
  - Sets receive timeout to 5 seconds using `setsockopt()`

#### `main.c` - TCP Client
**Workflow:**
1. Creates TCP socket
2. Builds IPv4 address for `127.0.0.1:2000`
3. Connects to server with `connect()`
4. Reads user input with `getline()` (safer than `scanf()`)
5. Sends messages with `send()`
6. Exits on "exit" command or Ctrl+D

**Key Features:**
- Proper input handling with newline stripping
- EOF detection (Ctrl+D handling)
- Error checking at each step

#### `main__1_.c` - TCP Server
**Workflow:**
1. Creates TCP socket
2. Binds to port 2000 on all local interfaces
3. Marks socket as passive with `listen()`
4. Accepts connections in infinite loop
5. Receives and displays client messages
6. Handles graceful client disconnection

**Key Features:**
- Backlog of 10 pending connections
- Separate loops for server lifetime and per-client handling
- Buffer clearing with `memset()` before each receive
- Null-termination of received data for safe string operations

## 🔑 Key Networking Concepts

### Socket Creation
```c
socket(AF_INET, SOCK_STREAM, 0)
// AF_INET: IPv4 addressing
// SOCK_STREAM: TCP protocol
// 0: Default protocol (TCP for SOCK_STREAM)
```

### Byte Order Conversion
```c
htons(port)    // Host TO Network Short (16-bit) - for port numbers
htonl(addr)    // Host TO Network Long (32-bit) - for IP addresses
```
Network byte order is **big-endian**; most systems are little-endian, so conversion is necessary.

### Server Workflow
```
socket() → bind() → listen() → accept() → recv/send → close()
```

### Client Workflow
```
socket() → connect() → send/recv → close()
```

### Connection Backlog
The `listen()` backlog parameter (10) sets the kernel's queue size for pending connections. If exceeded, new connection attempts may be dropped.

## 🛡️ Error Handling

The project demonstrates proper error handling patterns:

- Check return values for all socket operations
- Use `perror()` to display system error messages
- Return -1 from functions on failure
- Clean up resources even on error path
- Continue server operation on non-fatal client errors

Example:
```c
if (result < 0) {
    perror("connect failed");
    close(socketFD);
    exit(EXIT_FAILURE);
}
```

## 🧹 Resource Management

- **Sockets are closed** after use: `close(socketFD)`
- **Allocated memory is freed**: `free(address)`
- **Server shutdown** uses `shutdown()` for graceful closure
- **Per-client socket closed** after handling each client

## 📝 Notes & Improvements

### Current Limitations
- Single-threaded server (handles one client at a time)
- No message protocol or framing
- No encryption or authentication
- Fixed buffer size (1024 bytes)

### Possible Extensions
- Multi-threaded or async server to handle concurrent clients
- Message length prefix for structured communication
- TLS/SSL encryption for secure transmission
- Configuration file for IP/port settings
- Logging to file instead of stdout

## 🎓 Learning Outcomes

Through this project, you've learned:
- ✅ How operating systems manage network communication
- ✅ The client-server architecture pattern
- ✅ Low-level socket API usage in C
- ✅ Proper input/output handling for network data
- ✅ Error detection and recovery strategies
- ✅ Memory and resource lifecycle management


## 📄 License
