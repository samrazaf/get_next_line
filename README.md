*This project has been created as part of the 42 curriculum by samrazaf.*

---

# Description

`get_next_line` The goal is to implement a function that reads a line from a file descriptor, one line at a time, and returns it — including the terminating newline character when present. Each successive call to `get_next_line` returns the next line of the file, until EOF is reached.

The function has the following prototype:

```c
char *get_next_line(int fd);
```

- Returns the next line read from the file descriptor `fd`.
- Returns `NULL` when there is nothing more to read, or if an error occurred.
- Works for both file reading and standard input (`fd = 0`).
- The behavior is defined by a compile-time macro `BUFFER_SIZE`, which controls how many bytes are read from the file descriptor per `read()` call.

---

## Algorithm — Design Choices and Justification

### Overview

The implementation uses a **static buffer accumulation** approach combined with **dynamic string management**. Here is the rationale:

The core challenge of `get_next_line` is that `read()` does not respect line boundaries — it reads a fixed number of bytes at a time (`BUFFER_SIZE`). This means a single `read()` call may capture part of a line, a full line, or multiple lines at once. The function must therefore:

1. Read raw bytes into a fixed-size buffer.
2. Accumulate those bytes across multiple reads into a dynamically growing string.
3. Detect when a newline `\n` has been found.
4. Extract and return the line up to and including the `\n`.
5. Preserve the remaining bytes (after the `\n`) for the next call.

### Static Variable

A `static char *new_str` is used inside `get_next_line()`. Static variables retain their value between function calls, making it the natural choice to "remember" leftover data from a previous read that has not yet been returned as a line. This avoids the need for an external state or a wrapper struct.

### Step-by-step Flow

```
get_next_line(fd)
    │
    ├─► read_line()       → reads chunks via read(), accumulates into new_str
    │                        until '\n' is found or EOF is reached
    │
    ├─► extract_new_line() → extracts the substring [0 .. position of '\n']
    │                        (inclusive) to return as the current line
    │
    └─► update_last_line() → trims new_str to keep only the remainder
                             after the '\n', ready for the next call
```

### Why not read byte by byte?

Reading one byte at a time (with `BUFFER_SIZE = 1`) would work but is extremely inefficient — every character would trigger a system call. By reading in chunks of `BUFFER_SIZE` bytes, the number of expensive `read()` syscalls is minimized. The default `BUFFER_SIZE` is `42` but can be overridden at compile time.

### Why dynamic string concatenation?

Since we cannot predict how long a line will be, we cannot pre-allocate a fixed buffer for the line itself. The implementation uses `ft_strjoin` to grow the accumulation string as needed, freeing the old string after each join to avoid memory leaks.

### Memory management

Every heap-allocated string that is no longer needed is explicitly `free()`d. The static variable `new_str` is set to `NULL` when there is nothing left to carry over, preventing dangling pointer issues.

---

# Instructions

### Compilation

There is no `main` provided — `get_next_line` is a library function. To test it, create your own `main.c` and compile all files together:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    get_next_line.c get_next_line_utils.c main.c \
    -o gnl_test
```

You can override the buffer size at compile time:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
    get_next_line.c get_next_line_utils.c main.c \
    -o gnl_test
```

### Example `main.c`

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Reading from stdin

Pass `fd = 0` to read from standard input:

```c
char *line = get_next_line(0);
```

### Memory check

It is recommended to run with `valgrind` to verify there are no memory leaks:

```bash
valgrind --leak-check=full ./gnl_test
```

---

## Project Structure

```
.
├── get_next_line.c        # Core function: get_next_line and its static helpers
├── get_next_line.h        # Header: prototypes and BUFFER_SIZE macro
└── get_next_line_utils.c  # Utility functions: ft_strlen, ft_strjoin, ft_strchr,
                           #                    ft_strdup, ft_substr
```

---

# Resources

### Documentation & References

- [Linux `read()` man page](https://man7.org/linux/man-pages/man2/read.2.html) — understanding how the `read` syscall works, return values, and error handling.
- [C static variables — cppreference](https://en.cppreference.com/w/c/language/storage_duration) — behavior of `static` local variables across function calls.
- [GNU C Library Manual — Memory](https://www.gnu.org/software/libc/manual/html_node/Memory-Allocation.html) — `malloc`, `free`, and dynamic allocation best practices.
- [42 Docs / get_next_line subject](https://cdn.intra.42.fr/) — the official project subject from 42.

### Articles & Tutorials

- *"Understanding file descriptors in Unix"* — a useful conceptual overview before diving into the project.
- *"Valgrind Quick Start Guide"* — [valgrind.org](https://valgrind.org/docs/manual/quick-start.html) — essential for memory leak detection in C projects.

### Use of AI

AI (Claude by Anthropic) was used during this project for the following tasks:

- **Debugging**: Helping identify subtle memory management issues, such as cases where `new_str` might not be properly freed when `read()` returns `-1`.
- **Code review**: Reviewing the logic of `extract_new_line` and `update_last_line` to verify off-by-one correctness in index calculations.
- **README generation**: This README was written with the assistance of AI, following the formatting and content requirements of the 42 curriculum.

AI was **not** used to write the core algorithm or any of the source code. All implementation decisions were made by the student.
