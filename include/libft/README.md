# Libft

Libft is a C library that contains a collection of reimplemented standard functions along with additional functionalities, such as linked list operations (bonus).  
The goal is to provide essential tools for C projects by simplifying common operations (e.g., string manipulation, memory operations, and linked list management).

## What Does This Library Include?

The library is divided into two groups:

- **Basic Functions:** Reimplementation of standard functions for handling strings, memory, and characters.  
- **Bonus Functions:** Functions to manage linked lists.

## Library Functions

| Function               | Description                                                                 |
|------------------------|-----------------------------------------------------------------------------|
| **ft_bzero**           | Fills a memory block with zero bytes.                                       |
| **ft_isalnum**         | Checks if a character is alphanumeric.                                      |
| **ft_isalpha**         | Checks if a character is alphabetic.                                        |
| **ft_isascii**         | Checks if a character is an ASCII character.                              |
| **ft_isprint**         | Checks if a character is printable.                                        |
| **ft_isdigit**         | Checks if a character is a digit.                                          |
| **ft_memchr**          | Searches for a character in a block of memory.                             |
| **ft_memcpy**          | Copies a block of memory from one location to another.                     |
| **ft_memset**          | Fills a memory area with a constant byte.                                   |
| **ft_strchr**          | Locates the first occurrence of a character in a string.                   |
| **ft_strlcat**         | Concatenates strings while ensuring not to exceed a given size.            |
| **ft_strlcpy**         | Copies strings while ensuring not to exceed a given size.                  |
| **ft_strlen**          | Calculates the length of a string.                                         |
| **ft_strncmp**         | Compares two strings up to a limited number of characters.                 |
| **ft_strrchr**         | Finds the last occurrence of a character in a string.                    |
| **ft_tolower**         | Converts a character to lowercase.                                       |
| **ft_toupper**         | Converts a character to uppercase.                                       |
| **ft_memcmp**          | Compares two blocks of memory.                                             |
| **ft_strnstr**         | Searches for a substring within a string up to a specified length.         |
| **ft_atoi**            | Converts a string to an integer.                                           |
| **ft_calloc**          | Allocates memory for an array and initializes it with zero.                |
| **ft_strdup**          | Duplicates a string.                                                       |
| **ft_substr**          | Extracts a substring from a given string.                                  |
| **ft_memmove**         | Moves memory blocks, correctly handling overlapping areas.               |
| **ft_strjoin**         | Joins two strings into a new string.                                     |
| **ft_strtrim**         | Trims specified characters from the beginning and end of a string.         |
| **ft_strmapi**         | Applies a function to each character of a string to produce a new string.  |
| **ft_striteri**        | Applies a function to each character of a string (modifying the original). |
| **ft_putchar_fd**      | Outputs a character to a file descriptor.                                |
| **ft_putstr_fd**       | Outputs a string to a file descriptor.                                   |
| **ft_putendl_fd**      | Outputs a string followed by a newline to a file descriptor.             |
| **ft_putnbr_fd**       | Outputs an integer to a file descriptor.                                 |
| **ft_itoa**            | Converts an integer to a string.                                         |
| **ft_split**           | Splits a string into an array of strings using a specified delimiter.    |

### Bonus Functions (Linked Lists)

| Function                   | Description                                                                    |
|----------------------------|--------------------------------------------------------------------------------|
| **ft_lstnew_bonus**        | Creates a new element for a linked list.                                       |
| **ft_lstadd_front_bonus**  | Adds an element at the beginning of a linked list.                           |
| **ft_lstsize_bonus**       | Returns the number of elements in a linked list.                             |
| **ft_lstlast_bonus**       | Retrieves the last element of a linked list.                                 |
| **ft_lstadd_back_bonus**   | Adds an element at the end of a linked list.                                 |
| **ft_lstdelone_bonus**     | Deletes a single element from a list, freeing its memory.                    |
| **ft_lstclear_bonus**      | Deletes all elements of a linked list.                                       |
| **ft_lstiter_bonus**       | Iterates over each element of a list and applies a function to it.           |
| **ft_lstmap_bonus**        | Creates a new list by transforming each element with a given function.       |

## Usage

1. Clone this repository:
   ```bash
   git clone https://github.com/your_username/libft.git
   ```

2. Navigate to the project directory:
   ```bash
   cd libft
   ```

3. Compile the library:
   ```bash
   make
   ```

4. To compile the version with bonus functions:
   ```bash
   make bonus
   ```

5. To clean object files:
   ```bash
   make clean
   ```

6. To completely remove the library:
   ```bash
   make fclean
   ```

## Installation

You can use this library in your projects by including the `libft.h` header and linking the `libft.a` library during compilation.  

For example:
```bash
gcc -Wall -Wextra -Werror -Iincludes -L. -lft your_program.c -o your_program
```

