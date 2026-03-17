# File Cipher

A C++ application for batch file encryption and decryption using a Caesar cipher algorithm with multi-threaded processing.

## Overview

File Cipher processes entire directories of files, applying encryption or decryption operations using a shared secret key. The application leverages a multi-threaded task queue system with POSIX shared memory and semaphores for efficient concurrent file processing.

## Features

- Batch encryption/decryption of entire directories
- Multi-threaded processing with producer-consumer pattern
- POSIX shared memory for inter-process communication
- Semaphore-based synchronization for thread safety
- Caesar cipher encryption algorithm
- Configurable encryption key via `.env` file

## Project Structure

```
file-cipher/
├── src/app/
│   ├── encryptDecrypt/       # Core encryption/decryption logic
│   │   ├── Cryption.hpp
│   │   ├── Cryption.cpp
│   │   └── CryptionMain.cpp
│   ├── fileHandling/         # File I/O operations
│   │   ├── IO.hpp
│   │   ├── IO.cpp
│   │   └── ReadEnv.cpp
│   └── processes/            # Task queue and thread management
│       ├── ProcessManagement.hpp
│       ├── ProcessManagement.cpp
│       └── Task.hpp
├── test/                     # Test files
├── main.cpp                  # Main entry point
├── Makefile                  # Build configuration
├── makeDirs.py               # Test file generator
└── .env                      # Encryption key configuration
```

## Requirements

- C++17 compatible compiler (g++)
- POSIX-compliant system (macOS or Linux)
- Make build system

### System Dependencies

- POSIX Shared Memory (`sys/mman.h`)
- POSIX Semaphores (`semaphore.h`)
- C++17 Filesystem library

## Building

```bash
# Build both executables
make

# Clean build artifacts
make clean
```

This produces two executables:
- `encrypt_decrypt` - Main batch processing application
- `cryption` - Standalone encryption/decryption utility

## Configuration

Create a `.env` file in the project root with your encryption key:

```
12345
```

The key is used as the shift value for the Caesar cipher algorithm.

## Usage

### Batch File Processing

Run the main application:

```bash
./encrypt_decrypt
```

Follow the interactive prompts:

```
Enter the directory path: ./test
Enter the action (encrypt/decrypt): encrypt
```

All files in the specified directory will be processed concurrently.

### Standalone Cryption Utility

For single file operations:

```bash
./cryption "/path/to/file.txt,ENCRYPT"
./cryption "/path/to/file.txt,DECRYPT"
```

## Architecture

### Components

| Component | Description |
|-----------|-------------|
| **ProcessManagement** | Manages task queueing with shared memory and semaphores |
| **Task** | Represents a single encryption/decryption job |
| **Cryption** | Core Caesar cipher encryption/decryption logic |
| **IO** | File stream management and abstraction |
| **ReadEnv** | Environment configuration reader |

### Concurrency Model

- **Producer**: Main thread queues tasks via `submitToQueue()`
- **Consumers**: Worker threads process tasks from the shared queue
- **Queue**: Circular buffer with 1000-task capacity in shared memory
- **Synchronization**: Semaphores prevent queue overflow/underflow

### Encryption Algorithm

The application uses a Caesar cipher with modular arithmetic:

- **Encryption**: `ch = (ch + key) % 256`
- **Decryption**: `ch = (ch - key + 256) % 256`

Files are modified in-place, character by character.

## Testing

Generate test files:

```bash
python makeDirs.py
```

This creates 5 test files (1000 random characters each) in the `test/` directory.

## License

This project is available for educational and personal use.
