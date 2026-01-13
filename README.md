🌐 Available languages:
🇺🇸 English | 🇧🇷 [Português](README.pt.md)

---

# Pipex

A 42 School project that replicates the behavior of shell pipe redirections in C.

## 📋 Description

Pipex mimics the shell pipe mechanism, allowing you to redirect the output of one command as the input of another, while handling file input/output redirections.

The program replicates the following shell behavior:
```bash
< infile cmd1 | cmd2 > outfile
```

## 🚀 Usage

```bash
./pipex infile "cmd1" "cmd2" outfile
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `infile`  | Input file (redirected to stdin of cmd1) |
| `cmd1`    | First command with its arguments |
| `cmd2`    | Second command with its arguments |
| `outfile` | Output file (receives stdout of cmd2) |

### Examples

```bash
# Equivalent to: < input.txt grep hello | wc -l > output.txt
./pipex input.txt "grep hello" "wc -l" output.txt

# Equivalent to: < file.txt cat | head -5 > result.txt
./pipex file.txt "cat" "head -5" result.txt
```

## 🛠️ Compilation

### Cloning

```bash
git clone --recurse-submodules https://github.com/brfialho/pipex.git
```

If you've already cloned without submodules:
```bash
git submodule update --init --recursive
```

### Building

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile everything
```

## 📁 Project Structure

```
pipex/
├── main.c              # Entry point
├── main.h              # Header file with structs and prototypes
├── src/
│   ├── child_processes.c   # Fork and exec logic
│   ├── destroy.c           # Memory cleanup and error handling
│   └── parsing.c           # Argument parsing
├── libft/              # My libft library
├── files/              # Test files
└── Makefile
```

## 🔧 How It Works

1. **Parsing**: Validates arguments and extracts commands
2. **Open Files**: Opens input file for reading, output file for writing
3. **Create Pipe**: Creates a pipe for inter-process communication
4. **Fork Processes**:
   - **First child**: Reads from input file → writes to pipe
   - **Second child**: Reads from pipe → writes to output file
5. **Wait**: Parent waits for all children to finish
6. **Cleanup**: Closes file descriptors and frees memory

## 📚 Key Concepts

- **`pipe()`**: Creates a unidirectional data channel
- **`fork()`**: Creates a child process
- **`dup2()`**: Redirects file descriptors
- **`execv()`**: Replaces current process with a new program
- **`waitpid()`**: Waits for child process to terminate

## ⚠️ Error Handling

There is minimal error handling in this project since Im doing it only in preparation for minishell, thus it will not be submited.
The only reason I did this is for learning the basics of pipe.

## 👤 Author

**brfialho** - 42 Cadet

## 📄 License

This project is part of the 42 School curriculum.