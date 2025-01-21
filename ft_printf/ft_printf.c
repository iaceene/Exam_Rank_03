#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

# define F	r += ft_printf

int get_len(unsigned int n, int flag)
{
    int i;

    i = 0;
    if (flag == 1)
    {
        while (n)
        {
            n /= 16;
            i++;
        }
    }
    else if (flag == 0)
    {
        while (n)
        {
            n /= 10;
            i++;
        }
    }
    return (i);
}

int ft_putstr(char *s)
{
    int i;

    i = 0;
    if (!s)
        return (ft_putstr("(null)"));
    while (s[i])
    {
        write(1, &s[i], 1);
        i++;
    }
    return (i);
}

int ft_putnbr(int n)
{
    int     nig;
    char    s[100];
    int     len;

    nig = 0;
    len = get_len(n, 0);
    if (n >= (int)2147483647)
        return (ft_putstr("2147483647"));
    if (n <= (int)-2147483648)
        return (ft_putstr("-2147483648"));
    if (n == 0)
        return (ft_putstr("0"));
    if (n < 0)
    {
        nig = 1;
        n = -n;
    }
    if (nig)
    {
        s[0] = '-';
        s[len + 1] = '\0';
    }
    else
        s[len] = '\0';
    while (n && nig == 0)
    {
        s[--len] = n % 10 + 48;
        n /= 10;
    }
    while (n && nig == 1)
    {
        s[len--] = n % 10 + 48;
        n /= 10;
    }
    return (ft_putstr(s));
}

int ft_puthex(unsigned int n)
{
    char *hex = "0123456789abcdef";
    char s[100];
    int len;

    len = get_len(n, 1);
    if (n == 0)
        return (ft_putstr("0"));
    s[len] = '\0';
    while (n)
    {
        s[--len] = hex[n % 16];
        n /= 16;
    }
    return (ft_putstr(s));
}

int ft_printf(const char *str, ... )
{
    va_list ap;
    int     len;
    int     i;

    i = 0;
    len = 0;
    va_start(ap, str);
    while (str[i])
    {
        if (str[i] == '%' && str[i + 1] == '%')
        {
            len += write(1, "%", 1);
            i++;
        }
        else if (str[i] == '%' && str[i + 1] == 'd')
        {
            len += ft_putnbr(va_arg(ap, int));
            i++;
        }
        else if (str[i] == '%' && str[i + 1] == 'x')
        {
            len += ft_puthex(va_arg(ap, unsigned int));
            i++;
        }
        else if (str[i] == '%' && str[i + 1] == 's')
        {
            len += ft_putstr(va_arg(ap, char *));
            i++;
        }
        else if (str[i] != '%')
            len += write(1, &str[i], 1);
        i++;
    }
    return (len);
}

int main(void)
{
	int	r;

	r = 0;
	F("Simple test\n");
	F("");
	F("--Format---");
	F("\n");
	F("%d\n", 0);
	F("%d\n", 42);
	F("%d\n", 1);
	F("%d\n", 5454);
	F("%d\n", (int)2147483647);
	F("%d\n", (int)2147483648);
	F("%d\n", (int)-2147483648);
	F("%d\n", (int)-2147483649);
	F("\n");
	F("%x\n", 0);
	F("%x\n", 42);
	F("%x\n", 1);
	F("%x\n", 5454);
	F("%x\n", (int)2147483647);
	F("%x\n", (int)2147483648);
	F("%x\n", (int)-2147483648);
	F("%x\n", (int)-2147483649);
	F("%x\n", (int)0xFFFFFFFF);
	F("\n");
	F("%s\n", "");
	F("%s\n", "toto");
	F("%s\n", "wiurwuyrhwrywuier");
	F("%s\n", NULL);
	F("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	F("\n--Mixed---\n");
	F("%d%x%d%x%d%x%d%x\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
	F("-%d-%x-%d-%x-%d-%x-%d-%x-\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
	F("\n");
	F("%s%s%s%s\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	F("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	printf("written: %d\n", r);
}
