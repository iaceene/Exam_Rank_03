# 42 Exam Rank 03 - ft_printf & get_next_line

This repository contains my solutions for **Exam Rank 03** at 42, which consists of two main exercises:

- **ft_printf**: A custom implementation of the `printf` function in C.
- **get_next_line**: A function that reads a line from a file descriptor.

## Table of Contents

- [Overview](#overview)
- [ft_printf](#ft_printf)
- [get_next_line](#get_next_line)
- [Usage](#usage)
- [Requirements](#requirements)
- [Subjects](#Subjects)

## Overview

This repository contains my implementations of the two required exercises for **Exam Rank 03** at the 42 coding school:

1. **ft_printf**: A custom version of the `printf` function in C. It supports basic format specifiers like `%d`, `%s`, `%c`, `%x`, and `%%`.
2. **get_next_line**: A function that reads the next line from a file descriptor and returns it as a string, handling dynamic memory allocation and managing the buffer between calls.

## ft_printf

### Description

The `ft_printf` function is an implementation of the `printf` function in C. It parses a format string and prints the corresponding values based on the provided arguments.

### Supported Format Specifiers

- **%s**: Print a string.
- **%d / %i**: Print an integer.
- **%x**: Print an unsigned hexadecimal number.

### Key Concepts

- Variable argument lists using `stdarg.h`.
- Parsing format strings and handling different data types.
- Memory management and efficient printing.

### Example Usage

```c
#include "ft_printf.h"

int main() {
    ft_printf("Hello, %s! You have %d new messages.\n", "Alice", 5);
    return 0;
}
```

Output:
```
Hello, Alice! You have 5 new messages.
```

## get_next_line

### Description

The `get_next_line` function reads from a file descriptor and returns the next line as a string, handling dynamic memory allocation. It works for both file and standard input.

### Key Concepts

- Efficient buffer management.
- Reading lines from a file descriptor and handling multiple calls.
- Memory allocation for the returned line, which must be freed by the user.

### Example Usage

```c
#include "get_next_line.h"

int main() {
    char *line;
    int fd = open("example.txt", O_RDONLY);
    
    while (get_next_line(fd, &line)) {
        printf("%s\n", line);
        free(line);
    }

    close(fd);
    return 0;
}
```

Output:
```
Line 1 from the file.
Line 2 from the file.
```

## Usage

To compile and use the `ft_printf` and `get_next_line` functions, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/iaceene/Exam_Rank_03
   ```

2. Navigate to the project directory:
   ```bash
   cd Exam_Rank_03
   ```

3. Compile the source files:
   ```bash
   #use cc or gcc
   ```

4. Run the example code provided or write your own.

## Requirements

- C Compiler (gcc or clang)
- Standard C Library (libc)

## Subjects

FT_PRINTF

```
Assignment name  : ft_printf
Expected files   : ft_printf.c
Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
--------------------------------------------------------------------------------

Write a function named `ft_printf` that will mimic the real printf but 
it will manage only the following conversions: s,d and x.

Your function must be declared as follows:

int ft_printf(const char *, ... );

Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
To test your program compare your results with the true printf.

Exemples of the function output:

call: ft_printf("%s\n", "toto");
out: toto$

call: ft_printf("Magic %s is %d", "number", 42);
out: Magic number is 42%

call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
out: Hexadecimal for 42 is 2a$

Obs: Your function must not have memory leaks. Moulinette will test that.
```
GNL
```
Assignment name : get_next_line
Expected files : get_next_line.c (42_EXAM can't take .h for now)
Allowed functions: read, free, malloc
--------------------------------------------------------------------------------

Write a function named get_next_line which prototype should be:
char *get_next_line(int fd);


Your function must return a line that has been read from the file descriptor passed as parameter. What we call a "line that has been read" is a succession of 0 to n characters that end with '\n' (ascii code 0x0a) or with End Of File (EOF).

The line should be returned including the '\n' in case there is one at the end of the line that has been read. When you've reached the EOF, you must store the current buffer in a char * and return it. If the buffer is empty you must return NULL.

In case of error return NULL. In case of not returning NULL, the pointer should be free-able. Your program will be compiled with the flag -D BUFFER_SIZE=xx, which has to be used as the buffer size for the read calls in your functions.

Your function must be memory leak free. When you've reached the EOF, your function should keep 0 memory allocated with malloc, except the line that has been returned.

Calling your function get_next_line() in a loop will therefore allow you to read the text available on a file descriptor one line at a time until the end of the text, no matter the size of either the text or one of its lines.

Make sure that your function behaves well when it reads from a file, from the standard output, from a redirection, etc...

No call to another function will be done on the file descriptor between 2 calls of get_next_line(). Finally we consider that get_next_line() has an undefined behaviour when reading from a binary file.

```
