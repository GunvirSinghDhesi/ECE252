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


---



## 📄 System Call Example: `read()`

ssize_t read(fd,buf,count)
    - ssize_t --> signed int
    - fd --> int (file descriptor)
    - buf -> void (destination)
    - count -> size_t(ensgined_int) (maxbytes)
    - returns--> number of bytes read, or 0 (if at the end of the file)


