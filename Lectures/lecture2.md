# Systems Programming Notes

---

## 🛠️ Valgrind in C

Valgrind is a tool for detecting:
- Memory leaks
- Invalid memory access (e.g., use-after-free, out-of-bounds)
- Uninitialized memory usage

**Usage:**

bash
valgrind your_program

---

## 🧵 Threads

- A **thread** is the smallest unit of execution within a process.
- Threads share:
  - Code
  - Data
  - Open files
- Each thread has its own:
  - Stack
  - Program counter (PC)
  - Registers

**Benefits of threads:**
- Lightweight (less overhead than processes)
- Useful for parallelism and concurrency
- Easier communication between threads (shared memory)

--- 

## 🧷 Kernel

- The **kernel** is the **core part of an operating system** that manages system resources and enables communication between hardware and software.
- It operates in **privileged (supervisor) mode**, giving it unrestricted access to:
  - CPU instructions
  - Memory
  - Devices (disk, network, etc.)

**Key responsibilities of the kernel:**
- **Process management**  
  - Creating, scheduling, and terminating processes/threads
- **Memory management**  
  - Allocating and isolating memory between processes
- **File system management**  
  - Handling storage, files, directories, and I/O
- **Device management**  
  - Communicating with hardware via drivers
- **System calls & interrupt handling**  
  - Providing APIs for user programs to request privileged services safely

**Types of kernels:**
- **Monolithic kernel**: All OS services run in kernel space (e.g., Linux)
- **Microkernel**: Minimal kernel space, with most services in user space (e.g., MINIX)

---

## ⚠️ Handling Exceptions (Interrupts and Traps)

When an exception (such as an interrupt, fault, or system call) occurs, the CPU performs the following steps to handle it safely:

1. **Interrupt Controller Checks Priority**
   - The interrupt controller (part of the processor or chipset) determines if the incoming exception has a higher priority than the currently executing task.
   - If yes, it selects the appropriate exception or interrupt handler function.

2. **Store Execution Context**
   - The CPU saves the current program state so it can resume later.
   - This typically involves pushing the following onto the stack:
     - **Program Counter (PC)** – the current instruction address
     - **Status Register (SR)** – flags and processor state
     - **Global Pointer (GP)** – if used by the architecture
     - **General Purpose Registers** – to preserve the current function’s state

3. **Invoke Handler**
   - The processor jumps to the exception handler routine.
   - This is usually a piece of code in the operating system or firmware that knows how to deal with the specific exception (e.g., keyboard input, page fault, system call).

4. **Restore Execution Context**
   - Once the handler finishes, the saved registers and state are **popped from the stack** in reverse order.
   - Execution continues from the original point of interruption, as if nothing happened.


---


## ⚙️ Context Switch (Aside)
- Happens when the kernel switches execution to another process/thread.
- Saves current context and loads a new one from a different stack.

## 🔐 Privileged Exception
- Code runs in either **user mode** or **kernel (privileged) mode**.
- Only kernel mode can:
  - Execute privileged instructions (e.g., disable interrupts)
  - Access kernel memory
  - Handle system resources (e.g., file handles)

---


## 📞 System Calls

- Used by user programs to request OS services.
- Triggered via **trap instructions**, which switch from user mode to kernel mode.

### Trap Instruction:
- A CPU instruction that causes a **software interrupt** to enter the kernel safely.

### Flow:
1. **User thread** executes in unprivileged mode.
2. Executes a **trap** to request a service.
3. CPU switches to **privileged mode**.
4. **Kernel** performs the requested system call using the given operands.


# 📄 System Call Example: `read()`




---

## University of I/O

- The same system calls (`open()`, `close()`, `read()`, `write()`) apply to files and devices such as network sockets, pipes, terminals, etc.

### System Calls:

1.  `fd = open(pathname, flags, mode)`
    * `fd` (int): file descriptor (-1 on error)
    * `pathname` (const char \*): path to the file
    * `flags` (int): specifies how the file should be opened (e.g., `O_RDONLY`, `O_WRONLY`, `O_RDWR`, `O_CREAT`, `O_EXCL`, `O_APPEND`)
    * `mode` (mode_t): permissions for a newly created file (used with `O_CREAT`)

2.  `num_read = read(fd, buf, count)`
    * `num_read` (ssize_t): signed integer representing the number of bytes read.
        * Returns the number of bytes read.
        * Returns 0 if at the end of the file.
        * Returns -1 on error.
    * `fd` (int): file descriptor.
    * `buf` (void \*): pointer to the buffer where the read data will be stored (destination).
    * `count` (size_t): unsigned integer representing the maximum number of bytes to read.

3.  `num_written = write(fd, buf, count)`
    * `num_written` (ssize_t): signed integer representing the number of bytes written.
        * Returns the number of bytes written (if successful, this should be equal to `count` unless an error or interruption occurs).
        * Returns -1 on error.
    * `fd` (int): file descriptor.
    * `buf` (const void \*): pointer to the buffer containing the data to be written.
    * `count` (size_t): unsigned integer representing the number of bytes to write.

4.  `status = close(fd)`
    * `status` (int):
        * Returns 0 if successful.
        * Returns -1 on failure.
    * `fd` (int): file descriptor to be closed.




## 5. File Systems

Disk: `[partition 1 | partition 2]`
* 1 or more partitions per disk.

**Partition 1:**
* File System
    * **Boot Block** (size 1 block, typically): Contains code to boot the operating system.
    * **Superblock** (parameters): Contains metadata about the file system itself (e.g., file system type, size, block size, number of free blocks, number of free i-nodes).
    * **I-node Table** (info about files - permissions and other stuff - file info): An array of i-nodes.
    * **Data Blocks**: Blocks where the actual file content is stored.

* Logical blocks are typically 1-64 KiB (4 KiB is common).
* The i-node table contains 1 i-node (index node) per file in the file system.

* **Example: ext2 i-node structure**

    | Field                          | Description                                         |
    | ------------------------------ | --------------------------------------------------- |
    | File type, owner, group        | e.g., regular file, directory, socket, pipe...      |
    | Permissions                    | Read, write, execute permissions for owner, group, other |
    | Timestamps                     | Last access, last modified, last i-node change      |
    | Links                          | Number of hard links to the file                    |
    | Size                           | Size of the file in bytes                           |
    | # Blocks                       | Number of disk blocks allocated to the file         |
    | Direct Block Pointers (DB 0)   | Points directly to a data block                     |
    | Direct Block Pointers (DB 1)   | Points directly to a data block                     |
    | ...                            | More direct block pointers (e.g., up to 12)         |
    | Single Indirect Pointer        | Points to a block of direct block pointers          |
    | Double Indirect Pointer        | Points to a block of single indirect pointers       |
    | Triple Indirect Pointer        | Points to a block of double indirect pointers       |

    * `index -> DB & [100 blocks or something]` (Single Indirect: one block of pointers, each pointing to a data block)
    * `index -> index -> [1000 data blocks] & DB` (Double Indirect: one block of pointers, each pointing to a block of direct pointers, which then point to data blocks)
    * `index -> index -> index -> blocks` (Triple Indirect: for very large files)


### 📂 Blocks and Pointers Summary
	•	Data Block: Stores the actual contents of the file (e.g., text, binary data).
	•	I-node: Metadata structure for each file; stores permissions, ownership, timestamps, and pointers to file content blocks (but not the filename).
	•	Direct Block Pointer: An i-node field that directly points to a data block. Most file systems have ~12 of these.
	•	Single Indirect Pointer: Points to a block that holds more pointers to data blocks (used when file size exceeds direct pointers).
	•	Double Indirect Pointer: Points to a block of single indirect pointers.
	•	Triple Indirect Pointer: Points to a block of double indirect pointers (used for very large files).


* File systems are organized in a directory hierarchy starting at the root directory `/`.

    ```
                        /
                        |
    -----------------------------------------------------------------
    |                   |                               |           |
    bin                home                             usr        ...
                        |                               |
                -----------------                 --------------------
                |               |                 |     |       |     |
                username1       username2         bin   include lib  ...
    ```

* One file system is mounted as the root (`/`), and others can be mounted as subdirectories (e.g., `/home`).
* **Absolute pathnames**: Start from the root directory (`/`) (e.g., `/home/username1/file.txt`).
* **Relative pathnames**: Start from the current working directory (cwd) (e.g., `documents/report.docx` if cwd is `/home/username1`).
* File access permissions are specified per **user (u)**, **group (g)**, and **other (o)**.
* Permissions are **read (r)**, **write (w)**, and **execute (x)**.

* **Example of `ls -li` output:**

    `4738356 -rwxr-xr-x 1 root root 47496 Dec  4 21:26 filename`

    * `4738356` -> i-node number
    * `-` -> File type ( `-` for regular file, `d` for directory, `l` for symbolic link, etc.)
    * `rwx` -> User permissions (read, write, execute)
    * `r-x` -> Group permissions (read, no write, execute)
    * `r-x` -> Other permissions (read, no write, execute)
    * `1` -> Number of hard links
    * `root` -> User (owner)
    * `root` -> Group
    * `47496` -> Size in bytes
    * `Dec 4 21:26` -> Last modified timestamp
    * `filename` -> Name of the file or directory










