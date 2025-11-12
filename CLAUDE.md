# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a **minishell** implementation for the 42 school curriculum - a minimal Unix shell clone written in C. The project is in early development stages with basic readline functionality.

**Note**: The main header is currently misnamed as `philo.h` but should be `minishell.h` (includes/philo.h:13 has the correct guard `MINISHELL_H`).

## Build System

### Building the Project
```bash
make              # Build minishell executable
make clean        # Remove object files
make fclean       # Remove object files and executable
make re           # Full rebuild (fclean + all)
```

### How the Build Works
1. First builds `libft.a` static library from the `libft/` directory
2. Compiles source files from `srcs/` into `obj/srcs/`
3. Links everything together with `-lft` to create the `minishell` executable

The build uses:
- Compiler flags: `-Wall -Wextra -Werror -g`
- Include paths: `-Iincludes -Ilibft/includes`

## Code Architecture

### Directory Structure
```
srcs/           - Main minishell source code
includes/       - Project headers (currently only philo.h/minishell.h)
libft/          - Custom C library (organized in subdirectories)
  libft/        - Core library functions
  ft_printf/    - Custom printf implementation
  fileft/       - File operations (get_next_line, fd operations)
  arena_allocator/ - Arena memory allocator
  vector/       - Dynamic vector implementation
  includes/     - Library headers
obj/            - Compiled object files (generated)
```

### Libft Library Components

The custom library is divided into functional modules:

**Core libft** (`libft/libft/`):
- Standard C library reimplementations (strings, memory, lists, conversions)
- Custom utilities (ft_malloc/ft_free with size tracking, ft_realloc)
- Math utilities (ft_abs, ft_sgn, ft_max, sorting algorithms)
- String utilities (ft_split_charset, ft_strappend, ft_strisdigit)

**ft_printf** (`libft/ft_printf/`):
- Full printf implementation with format handlers
- Entry point: `ft_printf()` in ft_printf.c

**fileft** (`libft/fileft/`):
- File descriptor operations (ft_putchar_fd, ft_putstr_fd, ft_putnbr_fd)
- `get_next_line()` - reads line by line from fd (BUFFER_SIZE=42, FD_MAX=1024)
- `get_file()` - reads entire file content

**arena_allocator** (`libft/arena_allocator/`):
- Bump allocator for fast temporary allocations
- API: `arena_init()`, `arena_alloc()`, `arena_free()`

**vector** (`libft/vector/`):
- Dynamic array implementation
- String-focused operations: `vec_strappend()`, `vec_strappend_char()`

### Custom Data Structures

**t_list** (libft.h:34-46):
- Union-based linked list supporting multiple types (ptr, int, char, long)
- Type tracked via `t_type` enum
- Constructors: `ft_lstnew()`, `ft_lstnew_i()`, `ft_lstnew_chr()`, `ft_lstnew_l()`

**t_vector** (vector.h:17-23):
- Generic dynamic array with `void *content`
- Tracks capacity (`max`) and current size (`actual`)
- `size_type` indicates element size

**t_arena** (arena_allocator.h:18-23):
- Fixed-size memory arena with offset-based allocation
- No per-allocation overhead

### Current Implementation State

The minishell is currently a skeleton:
- `srcs/minishell.c:25-34` contains a basic readline loop
- Prints user input but doesn't parse or execute commands yet
- Links against readline library (implicit in code usage)

### Memory Management

The codebase uses custom allocator wrappers:
- `ft_malloc()` - wraps malloc with size header tracking
- `ft_free()` - companion free function
- `ft_sizeof()` - retrieves allocation size
- `ft_realloc()` - reallocation with size tracking
- Arena allocator available for bulk temporary allocations

## Development Notes

### 42 School Specifics
- Strict compliance with `-Wall -Wextra -Werror` (no warnings allowed)
- 42 header format used in all files (the comment block at the top)
- Norminette coding standard applies (though not enforced in build)

### Include Dependencies
Main code should include:
- `"libft.h"` - core library functions
- `"fileft.h"` - file operations and get_next_line
- Additional modules as needed (vector.h, arena_allocator.h)

### Linking Requirements
The project requires the readline library:
- Not currently specified in Makefile but used in minishell.c
- May need to add `-lreadline` to linker flags
