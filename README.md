# baremetal-server

## Overview

The **baremetal-server** is a minimalist HTTP server implemented entirely from scratch in C. It avoids external libraries and frameworks, emphasizing low-level control and deep understanding of systems programming. Alongside the server, several core data structures like hash maps, queues, and binary search trees (BST) have also been implemented from scratch.

This project was developed as a systems-level learning experience, with gathering experience in network programming.

---

## Key Features

- Basic HTTP request parsing (method, URI, version, headers, body)
- Custom data structures in C:
  - Hash map with string keys
  - Binary Search Tree (BST)
  - Queue and Linked List
- Modular C codebase with clear abstractions
- Custom Makefile to manage compilation, testing, and execution
- Fully open-source under the MIT License

---

## Build and Run Instructions

### Prerequisites

- GCC or compatible C compiler
- Unix-like OS (Linux/macOS preferred)
- `make` utility

### Commands

Compile all necessary object files and binaries:

```bash
make all
make run
make test
```
---

## Learning Outcomes

This project helped reinforce and apply several core computer science and software engineering principles:

- Operating systems fundamentals (memory management, process lifecycle)
- Low-level programming in C with manual memory and string handling
- TCP/IP and socket programming basics
- Modular system and low-level design practices
- Custom implementation of commonly used data structures
- Build automation using Makefile

### References and Learning Resources

The development of this project was supported by the following high-quality educational resources:
- YouTube Channel: [EOM O Meehan](https://www.youtube.com/@eom-dev)
- Article: [Beej’s Guide to Network Programming](https://beej.us/guide/bgnet/html/split/index.html)

### TODO

Future enhancements planned:

1. Dockerize the server for easier deployment and testing
2. Add support for custom route registration and handler callbacks

---

## Contribution Guidelines

Contributions are welcome. Please fork the repository and submit a pull request. Feature suggestions, bug reports, and design improvements are encouraged.

## License

This project is licensed under the MIT License. See the `LICENSE` file for more information.