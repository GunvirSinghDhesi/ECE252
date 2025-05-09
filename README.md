# 🧠 Remote Server Basics Cheat Sheet

## 🔐 SSH into Remote Server

```bash
# Basic SSH command
ssh gdhesi@hostname_or_ip

# Example:
ssh student@linux.student.cs.uwaterloo.ca

# With identity file (if needed)
ssh -i /path/to/private_key.pem gdhesi@host
```

## 📁 Transferring Files with `scp`

```bash
# Copy file from local to remote
scp file.txt gdhesi@host:/remote/path

# Copy file from remote to local
scp username@host:/remote/file.txt /local/path
```

## 🖥️ Use VS Code with Remote SSH

1. Install the "Remote - SSH" extension from the VS Code Extensions Marketplace.
2. Press `Cmd+Shift+P` → "Remote-SSH: Connect to Host…"
3. Add your host in `~/.ssh/config` for convenience:

```ssh
# ~/.ssh/config
Host my-server
  HostName linux.student.cs.uwaterloo.ca
  User student
  IdentityFile ~/.ssh/id_rsa
```

4. Then just select `my-server` from the VS Code Remote SSH prompt.

---

# 💻 Terminal Shortcuts (iTerm + Zsh)

```bash
# Clear screen
Ctrl + L

# Cancel command
Ctrl + C

# Previous command
Up Arrow

# Search previous commands
Ctrl + R
```

---

# 📂 File Navigation

```bash
ls         # List files
cd folder  # Change directory
pwd        # Show current path
```

---

# ⚙️ Helpful Tools

```bash
# Check disk space
df -h

# Check memory usage
free -h

# Check active processes
top

# Get your IP
curl ifconfig.me
```

---

# 🧹 VS Code Shortcuts

- `Cmd + P`: Quick file search
- `Cmd + Shift + P`: Command palette
- `Cmd + /`: Toggle line comment
- `Cmd + B`: Toggle sidebar
- `Cmd + K + 0`: Fold all
