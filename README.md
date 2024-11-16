# Get Next Line 📜

**Get Next Line** is a custom implementation of a function that reads and returns a single line from a file descriptor, no matter how many calls it takes. This project focuses on understanding memory management, file descriptors, and efficient buffer handling in C programming.

---

## 🚀 Features

- **Line-by-Line Reading**:
  - Reads from any valid file descriptor.
  - Supports files, standard input, and even pipes.
- **Handles Variable Line Lengths**:
  - Reads lines of arbitrary length without truncation.
- **Configurable Buffer Size**:
  - Uses a `BUFFER_SIZE` macro to control reading chunks dynamically.
- **Error Handling**:
  - Gracefully handles invalid file descriptors and memory allocation failures.

---

## 🛠️ Usage

### 1. Clone the Repository
```bash
git clone https://github.com/Maj-e/get_next_line.git
cd get_next_line
