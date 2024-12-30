# 🚀 Unix Shell Project

Welcome to the **Unix Shell** project! This custom shell, written in C, provides support for basic command-line operations, file and directory navigation, and quoting for strings. Designed to demonstrate both core programming skills and system-level understanding, this project is an ideal showcase for aspiring software engineers. 🖥️

---

## 🌟 Features

- **Basic Commands**: Execute commands like `echo`, `pwd`, `cd`, `exit`, and more.
- **Quoting Support**: Handle single quotes (`'`), double quotes (`"`), and escape sequences.
- **File Navigation**: Navigate directories and list files with ease.
- **Custom Execution**: Detect and execute commands and binaries from `$PATH`.
- **Error Handling**: Gracefully handle incorrect inputs and missing files.

---

## 🔧 How It Works

The shell runs in a loop, waiting for user input, parsing it, and executing the desired operation. It supports:

1. **Built-in Commands**: Commands like `echo`, `pwd`, `cd`, and `exit` are implemented directly.
2. **External Commands**: Checks `$PATH` for executables and runs them.
3. **Quoting Mechanisms**:
   - **Single Quotes**: Preserves literal value of characters.
   - **Double Quotes**: Allows escape sequences like `\n`.
   - **No Quotes**: Handles unquoted strings and escape sequences.

---

## 📂 File Structure

```
├── main.c  # Main shell implementation
```

---

## 🛠️ Build and Run

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd unix-shell
   ```
2. Compile the shell:
   ```bash
   gcc shell.c -o shell
   ```
3. Run the shell:
   ```bash
   ./shell
   ```

---

## 📝 Example Usage

```bash
$ echo "Hello, World!"
Hello, World!
$ pwd
/home/user/unix-shell
$ cd ..
$ cat file.txt
This is a sample file.
$ exit 0
```

---

## 🌈 Why This Project Stands Out

- **Practical Application**: Demonstrates proficiency in system calls, file I/O, and process management.
- **Efficiency**: Designed to handle user input and operations with minimal overhead.
- **Scalability**: Provides a foundation for adding more advanced shell features.

---

## 🤝 Contributing

Contributions are welcome! Feel free to submit a pull request or open an issue for suggestions or improvements. 🙌

---

## 📜 License

This project is licensed under the MIT License.

---

Thank you for checking out the Unix Shell Project! 💻✨
