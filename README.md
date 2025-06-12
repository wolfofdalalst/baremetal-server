# Baremetal Server

A lightweight HTTP/1.1 server implementation written in C from scratch, featuring custom data structures and minimal dependencies.

## Features

- **HTTP/1.1 Protocol Support** - Complete request parsing and response handling
- **Static File Serving** - MIME type detection and file delivery
- **Custom Data Structures** - Hash maps, binary search trees, queues, and linked lists
- **Error Handling** - Custom 404 pages and graceful error responses
- **Modular Architecture** - Clean separation of concerns and reusable components

## Quick Start

### Prerequisites

- GCC or compatible C compiler
- Unix-like system (Linux/macOS)
- Make utility
- docker (optional, but recommended)

### Baremetal installation

```bash
make clean && make
./bin/baremetal
```

The server will start on port 8080. Access it at `http://localhost:8080`.

### Docker 

```bash
docker build -t baremetal-server .
docker run --rm --network host baremetal-server
```

## Architecture

### Core Components

- **Socket Layer** (`server.c`) - Socket creation, binding, and connection handling
- **HTTP Parser** (`httprequest.c`) - HTTP request parsing and validation
- **File Handler** (`fileutils.c`) - Static file serving and MIME type detection
- **Request Router** (`main.c`) - Request routing and response generation

### Data Structures

- **Hash Map** - String-based key-value storage for HTTP headers
- **Binary Search Tree** - Efficient data organization and retrieval
- **Linked List** - Dynamic data storage and manipulation
- **Queue** - FIFO operations for request processing

### Directory Structure

```
src/                   # Source code
├── main.c             # Server entry point
├── server.c           # Socket management
├── httprequest.c      # HTTP protocol
├── fileutils.c        # File operations
└── datastructures/    # Custom data structures

include/               # Header files
www/                   # Static web content
test/                  # Unit tests
```

## Contributing

Contributions are welcome! Please feel free to submit pull requests, report bugs, or suggest new features.

## License

This project is licensed under the MIT License. See `LICENSE` for details.
