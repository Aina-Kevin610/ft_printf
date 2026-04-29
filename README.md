*This project has been created as part of the 42 curriculum by airandri.*

---

# ft_printf

> A partial reimplementation of the C standard library `printf` function.

---

## Description

`ft_printf` is a project from the 42 school curriculum that challenges students to reproduce the core behaviour of the standard `printf` function from scratch, using only variadic functions and their own previously built `libft` library.

**Goal:** Implement the following function:

```c
int ft_printf(const char *format, ...);
```

| Return value | Meaning |
|---|---|
| `int` ≥ 0 | Total number of characters written to stdout |
| `-1` | The `format` string was `NULL` |

The function parses a format string and, each time it encounters a `%` followed by a valid specifier, fetches the next variadic argument and prints it in the appropriate format.

**Supported conversion specifiers:**

| Specifier | Output |
|---|---|
| `%c` | A single character |
| `%s` | A string (`(null)` if the pointer is NULL) |
| `%d` / `%i` | A signed decimal integer |
| `%u` | An unsigned decimal integer |
| `%x` | An unsigned integer in lowercase hexadecimal |
| `%X` | An unsigned integer in uppercase hexadecimal |
| `%p` | A pointer address (`0x…`, or `(nil)` if NULL) |
| `%%` | A literal `%` character |

No format flags (width, precision, `-`, `0`, etc.) are implemented — this is the mandatory scope of the project.

**Key learning objectives:**
- Understanding and using variadic functions (`stdarg.h`: `va_list`, `va_start`, `va_arg`, `va_end`)
- Parsing a format string character by character
- Building modular output helpers that each return a character count
- Accumulating and returning the total number of characters written

---

## Algorithm

### Architecture: dispatcher + specialised writers

The implementation is split across five files around a single central idea: **every output helper returns the number of characters it wrote**, and `ft_printf` accumulates those counts into a single total.

```
ft_printf(format, ...)
│
└── ft_formats(args, specifier)       [static dispatcher]
    ├── ft_putchar()          → %c
    ├── ft_putstr()           → %s
    ├── ft_putnbr()           → %d / %i
    ├── ft_putnbr_unsigned()  → %u
    ├── ft_putnbr_hexa_min()  → %x
    ├── ft_putnbr_hexa_maj()  → %X
    └── ft_putptr()           → %p
```

---

### `ft_printf` — format string parser

```c
int ft_printf(const char *format, ...)
```

The function iterates over every byte of `format`:

- If the current character is `%` **and** the next character exists, it calls `ft_formats` with that next character and advances the index by one extra step.
- Otherwise it writes the character directly with `ft_putchar_fd(format[i], 1)` and increments `total_len` by 1.

This design means an isolated `%` at the very end of the string (no character following it) is printed as-is rather than triggering undefined behaviour, because the condition `format[i + 1]` guards the dispatch.

The `__attribute__((format(printf, 1, 2)))` annotation on the prototype tells the compiler to type-check the variadic arguments against the format string, catching mismatches at compile time.

---

### `ft_formats` — static dispatcher

```c
static int ft_formats(va_list args, const char format)
```

A simple `if / else if` chain maps each specifier character to its dedicated output function. Making this function `static` keeps it internal to `ft_printf.c` — it is an implementation detail, not part of the public API. It returns the character count produced by whichever branch was taken.

---

### `ft_putchar` / `ft_putstr` / `ft_putnbr` — basic writers

Defined in `ft_printf_utils.c`, these wrap the `libft` functions (`ft_putstr_fd`, `ft_itoa`, `ft_strlen`) and return the exact number of characters written:

- `ft_putchar` — writes one byte via `write(1, &c, 1)`, always returns `1`.
- `ft_putstr` — if the pointer is `NULL`, prints the literal string `(null)` (6 characters) rather than crashing. Otherwise delegates to `ft_putstr_fd` and returns `ft_strlen(s)`.
- `ft_putnbr` — converts `int` to string with `ft_itoa`, writes it, frees the allocation, and returns the string length.
- `ft_putnbr_unsigned` — same pattern as `ft_putnbr` but uses the custom `ft_unsigned_itoa` to handle the unsigned type correctly.

---

### `ft_unsigned_itoa` — unsigned integer to string

```c
char *ft_unsigned_itoa(unsigned int n)
```

`libft`'s `ft_itoa` works on `int` and would misinterpret large unsigned values (above `INT_MAX`) as negative. `ft_unsigned_itoa` solves this by:

1. Casting the `unsigned int` to `long` internally to allow safe digit extraction.
2. Computing the number of digits with a dedicated `int_len` helper.
3. Filling the string from right to left using repeated `% 10` / `/ 10`.
4. Handling the `n == 0` edge case explicitly (the while loop would never execute).

---

### `ft_putnbr_hexa_min` / `ft_putnbr_hexa_maj` — hexadecimal output

```c
int ft_putnbr_hexa_min(unsigned int nb)   // "0123456789abcdef"
int ft_putnbr_hexa_maj(unsigned int nb)   // "0123456789ABCDEF"
```

Both functions use **recursive base conversion**:

- If `nb >= 16`, recurse on `nb / 16` first (this prints the most-significant digit(s)).
- Then print `base[nb % 16]` for the current least-significant digit.

Recursion naturally unwinds in most-significant-to-least-significant order, so no intermediate buffer or reversal is needed. The character count accumulates up the call stack through the return values.

---

### `ft_putptr` — pointer output

```c
int ft_putptr(unsigned long ptr)
```

- If the pointer value is `0` (NULL), prints the string `(nil)` and returns its length.
- Otherwise, prints the `0x` prefix (2 characters) then delegates the hex digits to the recursive `ft_printptr`, which uses the same base-conversion logic as the hex functions but operates on `unsigned long` to cover the full 64-bit address space.

---

### Design justification

| Choice | Justification |
|---|---|
| **Every helper returns a `int` char count** | Allows `total_len` to be accumulated with simple `+=` at every call site, with no global state. |
| **`static` for `ft_formats`** | It is an internal routing function, not part of the public interface. `static` enforces this at the linker level. |
| **Recursive hex conversion** | Eliminates the need for a temporary buffer and a reversal step. The call stack itself acts as the implicit storage for digits in the correct order. |
| **`ft_unsigned_itoa` instead of reusing `ft_itoa`** | `ft_itoa` takes a signed `int`; passing a large `unsigned int` would cause undefined behaviour on overflow. A dedicated function avoids this entirely. |
| **`(null)` / `(nil)` for null pointers** | Matches the behaviour of the standard `printf` on most systems, making the output predictable and consistent. |
| **`__attribute__((format(printf, 1, 2)))`** | Enables GCC/Clang compile-time format-string checking, catching type mismatches between the format string and the supplied arguments before the program is even run. |

---

## Instructions

### Prerequisites

- A C compiler: `gcc` or `clang`
- A Unix-like operating system (Linux or macOS)
- The `libft` library (expected at `libft/libft.h` and `libft/libft.a`)

### Files

| File | Role |
|---|---|
| `ft_printf.h` | Header — all prototypes, includes (`libft.h`, `stdarg.h`, `unistd.h`, `stdlib.h`) |
| `ft_printf.c` | Entry point `ft_printf` + static dispatcher `ft_formats` |
| `ft_printf_utils.c` | `ft_putchar`, `ft_putstr`, `ft_putnbr`, `ft_putnbr_unsigned` |
| `ft_unsigned_itoa.c` | `ft_unsigned_itoa` — unsigned integer to decimal string |
| `hexa.c` | `ft_putnbr_hexa_min`, `ft_putnbr_hexa_maj` — hex output |
| `pointer.c` | `ft_putptr`, `ft_printptr` — pointer address output |

### Compilation

```bash
# Build libft first (adjust path as needed)
make -C libft

# Compile ft_printf into a static library
ar rcs libftprintf.a ft_printf.o ft_printf_utils.o ft_unsigned_itoa.o hexa.o pointer.o

# Or compile directly with a test main
gcc -Wall -Wextra -Werror \
    ft_printf.c ft_printf_utils.c ft_unsigned_itoa.c hexa.c pointer.c \
    -L./libft -lft -o ft_printf_test
```

If a `Makefile` is provided, simply run:

```bash
make
```

### Integration example

```c
#include "ft_printf.h"

int main(void)
{
    int n = -42;
    unsigned int u = 4294967295u;
    void *ptr = &n;

    ft_printf("char    : %c\n", 'A');
    ft_printf("string  : %s\n", "hello, 42");
    ft_printf("int     : %d\n", n);
    ft_printf("unsigned: %u\n", u);
    ft_printf("hex low : %x\n", 255);
    ft_printf("hex up  : %X\n", 255);
    ft_printf("pointer : %p\n", ptr);
    ft_printf("percent : 100%%\n");
    ft_printf("null str: %s\n", (char *)NULL);
    ft_printf("null ptr: %p\n", (void *)NULL);
    return (0);
}
```

Expected output:

```
char    : A
string  : hello, 42
int     : -42
unsigned: 4294967295
hex low : ff
hex up  : FF
pointer : 0x[address]
percent : 100%
null str: (null)
null ptr: (nil)
```

### Testing

Community testers for exhaustive coverage:
- [printfTester by Tripouille](https://github.com/Tripouille/printfTester)
- [ft_printf_tester by paulo-santana](https://github.com/paulo-santana/ft_printf_tester)

---

## Resources

### Official / Reference documentation

- [Linux `man` page — `printf(3)`](https://man7.org/linux/man-pages/man3/printf.3.html) — The standard function this project reimplements.
- [Linux `man` page — `stdarg(3)`](https://man7.org/linux/man-pages/man3/stdarg.3.html) — `va_list`, `va_start`, `va_arg`, `va_end`.
- [Linux `man` page — `write(2)`](https://man7.org/linux/man-pages/man2/write.2.html) — The system call used for all output.
- [GCC — Function attributes (`format`)](https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-format-function-attribute) — Documentation for the `__attribute__((format))` annotation.
- [cppreference — Variadic functions](https://en.cppreference.com/w/c/variadic) — How variadic argument lists work in C.

### Tutorials and articles

- [How printf works internally (Medium)](https://medium.com/@saif_k/how-printf-works-internally-4e8ab3eb7ed7) — Good conceptual walkthrough of parsing and dispatching.
- [Variadic functions in C (GeeksForGeeks)](https://www.geeksforgeeks.org/variadic-functions-in-c/) — Clear primer on `va_list`.
- [Base conversion and recursion (CS concepts)](https://www.cs.utexas.edu/~scottm/cs307/handouts/recursiveBaseConversion.htm) — Explains the recursive digit-extraction technique used in the hex functions.
- [ft_printf — 42 project overview (harm-smits 42docs)](https://harm-smits.github.io/42docs/projects/ft_printf) — Project requirements and tips from the 42 community.

### Use of AI

AI assistance (Claude by Anthropic) was used during this project in the following ways:

- **Debugging** — Describing incorrect character counts (e.g. off-by-one when accumulating `total_len`, or `ft_putstr` not returning the right length for a `NULL` input) to the AI to identify the root cause quickly.
- **Understanding concepts** — Asking for clarification on how `va_arg` advances the variadic argument list, and why `unsigned int` cannot safely be passed to `ft_itoa`.
- **README drafting** — Structuring and writing this documentation, including the per-function algorithm breakdown and the design justification table.

---

*42 Antananarivo — milestone1 / ft_printf*