
# 📂 Directories and File Links

## 🗂 What is a Directory?
- A **directory** is a special file that acts as a **table mapping file names to i-node numbers**.

---

## 🔗 Hard Links

### 📌 Key Concept:
- A **hard link** is another **directory entry that points to the same i-node** as the original file.
- Multiple hard links to the same file share **file content and metadata** (except name and directory path).

---

### 🧪 Hard Link Example

```bash
echo -n "Water" > abc
ls -li abc
ln abc xyz
ls -li abc xyz
echo "loo" >> xyz
cat abc
```

#### 📘 Step-by-Step Explanation:

1. `echo -n "Water" > abc`
   - Prints `"Water"` without a newline.
   - Creates or overwrites file `abc`.

2. `ls -li abc`
   - Displays file details including **i-node number**.

3. `ln abc xyz`
   - Creates a **hard link** named `xyz` pointing to the same i-node as `abc`.

4. `ls -li abc xyz`
   - Both files have the same **i-node number** and link count is now `2`.

5. `echo "loo" >> xyz`
   - Appends `"loo"` to the file. Since both files share the same i-node, the content is shared.

6. `cat abc`
   - Output:  
     ```
     Waterloo
     ```

---

### 📎 Quick Notes on Hard Links

- `ln file1 file2`: Creates a hard link to `file1` named `file2`.
- Hard links:
  - Cannot span across different file systems.
  - Share the same i-node.
  - Are indistinguishable in content from the original file.

---

## 🔗 Symbolic (Soft) Links

### 📌 Key Concept:
- A **symbolic link** is a special file that **contains a path** to another file.
- Symbolic links:
  - Can span across file systems.
  - Point to a file **name**, not its i-node.
  - Break if the target file is deleted.

---

### 🧪 Symbolic Link Example

```bash
ln -s abc uvw
cat uvw
ls -l uvw
rm abc
cat uvw
ls -li uvw
ls -li xyz uvw
```

#### 📘 Explanation:

1. `ln -s abc uvw`
   - Creates a **symbolic link** `uvw` → `abc`.

2. `cat uvw`
   - Displays contents of `abc`.

3. `ls -l uvw`
   - Output:
     ```
     lrwxrwxrwx 1 user user 3 May 15 14:10 uvw -> abc
     ```

4. `rm abc`
   - Deletes the file `abc`. `uvw` becomes a **broken link**.

5. `cat uvw`
   - Error:  
     ```
     cat: uvw: No such file or directory
     ```

6. `ls -li uvw`
   - Shows the i-node of the **symbolic link** itself.

7. `ls -li xyz uvw`
   - `xyz` and `abc` shared i-nodes (hard link).
   - `uvw` has a **different i-node**, pointing to a file path.

---

### ⚠️ Hard Link vs Symbolic Link

| Feature                  | Hard Link               | Symbolic Link              |
|--------------------------|-------------------------|----------------------------|
| Points to                | I-node (file data)      | File name (path)           |
| Works across FS?         | ❌ No                   | ✅ Yes                     |
| Survives target deletion | ✅ Yes                  | ❌ No (becomes broken)     |
| Has its own i-node?      | ❌ No                   | ✅ Yes                     |

---

## 🧠 Other Notes

### Deleted File Behavior
- A deleted file remains accessible **until the last open file descriptor** to it is closed.

---

## 🧾 File Descriptors and Tables

### 🔢 File Descriptors
- Small non-negative integers that reference an open file.
- Managed per process.
- Standard descriptors:

| Stream        | FD | `unistd.h`       | `stdio.h` |
|---------------|----|------------------|-----------|
| stdin         | 0  | `STDIN_FILENO`   | `stdin`   |
| stdout        | 1  | `STDOUT_FILENO`  | `stdout`  |
| stderr        | 2  | `STDERR_FILENO`  | `stderr`  |

---

### 🧱 System Tables Overview

#### 1. File Descriptor Table (per process)

| FD | Flags | File Ptr (→ Open File Table) |
|----|-------|-------------------------------|
| 0  |       |                               |
| 1  |       |                               |
| 2  |       |                               |

#### 2. Open File Table (system-wide)

| Offset | Flags | I-node Pointer |
|--------|-------|----------------|

#### 3. I-node Table (per file system)

| Type | Locks | Attributes |
|------|-------|------------|

- `File Ptr (FD)` → Open File Table Entry → Offset + i-node
- Multiple processes can point to the same Open File Table entry.

---

## 📚 C File I/O (via `stdio.h`)

- Built on **system calls** like `open()`, `read()`, `write()`, and `close()`.
- Uses `FILE*` (a struct) instead of low-level file descriptors.
- Advantages:
  1. Formatted I/O (e.g. `fprintf`, `fscanf`)
  2. Buffered in blocks (e.g. 4096B) → fewer system calls → faster I/O

---

### 🔤 Common C File I/O Functions

```c
FILE *fp = fopen(pathname, mode);
```

| Mode | Description                        |
|------|------------------------------------|
| "r"  | Read only                          |
| "w"  | Write only (truncates if exists)   |
| "a"  | Append                             |
| "r+" | Read & write                       |
| "w+" | Read & write (truncates)           |
| "a+" | Read & append                      |

- Returns `NULL` on error.

#### Other C I/O Functions:
- `fscanf()`
- `fread()`
- `fwrite()`
- `fprintf()`
- `fseek()`
