
# 🧠 Processes and System Calls in C / OS Concepts

---

## 1. 📌 Process Overview

A **process** is an instance of a running program.

### 📦 A Process Consists Of:

#### 1.1. User-Space Memory

```
|--------------------------|
| Stack    (grows down)    |
|--------------------------|
|                          |
|--------------------------|
| Heap     (grows up)      |
|--------------------------|
| Data                     |
|--------------------------|
| Text (user code)         |
|--------------------------|
```

### 🔍 Definitions

- **Heap**: Used for dynamic memory (e.g., `malloc`), holds runtime data structures.  
  ⚠️ Often described as **growing upward**, **not LIFO** in the traditional stack sense.

- **Stack**: Used for function-level memory (local variables, return addresses, saved registers).  
  ✅ **LIFO (Last-In-First-Out)** structure.

---

#### 1.2. Kernel-Space Data

(Recall: The **kernel** is the core of the OS and manages everything from process scheduling to memory management.)

| Field                     | Description                                   |
|---------------------------|-----------------------------------------------|
| PID                      | Process ID                                    |
| GID                      | Group ID                                      |
| State                    | `running`, `runnable`, `sleeping`, `zombie`   |
| Page Table               | Virtual memory mapping                        |
| File Descriptor Table    | Tracks open files                             |
| Signal Masks & Handlers  | For signal processing                         |
| Processor Usage          | CPU stats for scheduling                      |
| Limits                   | Max resources (e.g., stack size, open files)  |
| CWD                      | Current working directory                     |
| Root Directory           | Root context for file access                  |

---

#### 1.3. A Thread of Execution

*(More on this later)*

---

## 🔄 Process Creation

### 🟢 `init` / `systemd` Process
- The **first process** to run after booting.
- Has **PID = 1**.

### 👪 Parent & Child Processes

- A **parent process** creates a **child process**.
- A **terminated child** becomes a **zombie** until its return status is collected.
- If a **parent dies first**, the **init/systemd** process adopts the child.

```bash
pstree  # shows process hierarchy as a tree
```

---

## 🔧 System Calls

### ✂️ `fork()`

- Creates a **copy** of the calling process.

#### 🔍 What is Copied?

| Region   | Description                                    |
|----------|------------------------------------------------|
| Text     | Read-only (may be shared)                     |
| Data     | Copy-on-write (shared until modified)         |
| Heap     | Copied                                         |
| Stack    | Copied                                         |
| Others   | File descriptor table, CWD, root dir, signals  |

#### 🔁 Return Values

| Return Value | Meaning              |
|--------------|----------------------|
| `0`          | In child process     |
| `>0`         | In parent (child PID)|
| `-1`         | Error                |

#### 🧪 Example

```c
switch(fork()) {
    case -1:
        // error
        break;
    case 0:
        // child process code
        break;
    default:
        // parent process code
        break;
}
```

---

## 💾 Tutorial: File I/O with Structs

### 👤 `Person` Struct

| Field       | Type     |
|-------------|----------|
| Age         | `int`    |
| Height      | `float`  |
| Name Length | `int`    |
| Name        | `char[]` (flexible array member) |

### 🧠 Notes

- `sizeof(person)` = size of age + height + name length
- Allocate using:

```c
malloc(sizeof(Person) + name_length)
```

---

### 📊 Visual Flow

```
[Person Struct] → [Write to File] → [Read from File] → [Person Struct]
                      |
                      v
                  person.dat
```

- `.dat` file: Generic data file (can be binary or text depending on how it's written).

---

Let me know if you'd like the C code or diagram embedded here!
