# 🍦 Multi-Threaded IceCreamOS



## 🌟 Introduction

**Multi-Threaded IceCreamOS** is a lightweight operating system designed to efficiently handle multi-threading and process scheduling. This OS project demonstrates fundamental concepts of **multi-threading, scheduling algorithms, and inter-process communication (IPC).**

## 🔥 Features

✅ **Multi-threading support** for better resource utilization
✅ **Process scheduling** (FCFS, Round Robin, Priority Scheduling, etc.)
✅ **Inter-process communication (IPC)** mechanisms
✅ **Lightweight and optimized kernel design**
✅ **File system support (basic implementation)**
✅ **Memory management techniques**
✅ **Command-line interface (CLI) for user interaction**

## 🚀 Installation Guide

### Prerequisites

Ensure you have the following installed before proceeding:

- **GCC Compiler** (for compiling C code)
- **Make** (for build automation)
- **QEMU** (for OS emulation) *(optional)*

### Steps to Run IceCreamOS

1. Clone this repository:
   ```sh
   git clone https://github.com/Aliharis007/Multi-Threaded-IceCreamOS.git
   cd Multi-Threaded-IceCreamOS
   ```
2. Compile the OS source code:
   ```sh
   make
   ```
3. Run the OS in Ubuntu:
   ```sh
   ./IceCreamOS
   ```

## 📂 Directory Structure

```
📦 Multi-Threaded-IceCreamOS
├── 📁 src          # Source code for kernel and OS components
│   ├── kernel.c    # Kernel source code
│   ├── scheduler.c # Process scheduling implementation
│   ├── memory.c    # Memory management module
│   ├── ipc.c       # Inter-process communication module
│   ├── main.c      # OS main entry point
├── 📁 docs         # Documentation and research files
├── 📁 tests        # Unit tests and debugging scripts
├── Makefile       # Build script
└── README.md      # Project documentation
```

## 📜 Usage

Once the OS is running, you can:

- Use built-in commands for **process management** and **thread scheduling**
- Test different scheduling algorithms
- Perform **inter-process communication**

## 🛠️ Contributing

We welcome contributions! Feel free to fork the repository and submit **pull requests**.

1. Fork the repo and create your branch:
   ```sh
   git checkout -b feature-branch
   ```
2. Make changes and commit:
   ```sh
   git commit -m "Your commit message"
   ```
3. Push changes to your forked repo:
   ```sh
   git push origin feature-branch
   ```
4. Open a **Pull Request** 🚀

🚀 **Happy Coding!** 😊
