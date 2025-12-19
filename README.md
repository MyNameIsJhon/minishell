# minishell

A minimal Unix shell implementation in C, created as part of the 42 school curriculum.

## About

Minishell is a simplified version of bash that replicates core shell functionality. The project focuses on understanding processes, file descriptors, and command parsing in Unix-like systems.

## Features

- Interactive command prompt
- Command execution
- Built-in commands
- Environment variable handling
- Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)
- Redirections and pipes
- Command history

## Requirements

- GCC compiler
- GNU Make
- readline library

## Installation

Clone the repository and build the project:

```bash
git clone [your-repo-url] minishell
cd minishell
make
```

## Usage

Run the shell:

```bash
./minishell
```

Execute commands just like in bash:

```bash
minishell$ echo "Hello, World!"
minishell$ ls -la
minishell$ pwd
minishell$ exit
```

## Building

```bash
make        # Build the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Rebuild from scratch
```

## Project Structure

```
srcs/               # Source files
includes/           # Header files
libft/              # Custom C library
obj/                # Compiled object files (generated)
```

## Author

42 student project

## License

This project is part of the 42 school curriculum.
