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