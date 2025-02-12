#include "unistd.h"
#include "stdarg.h"

int ft_putchar(char c);
int ft_putstr(char *s);
int ft_putnbr(int n);
int ft_puthex(unsigned int n);

int ft_printf(const char *str, ... )
{
    va_list ap;
    int len;
    int i;

    va_start(ap, str);
    len = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '%' && str[i + 1] && str[i + 1] == 's')
        {
            len += ft_putstr(va_arg(ap, char *));
            i++;
        }
        else if (str[i] == '%' && str[i + 1] && str[i + 1] == 'd')
        {
            len += ft_putnbr(va_arg(ap, int));
            i++;
        }
        else if (str[i] == '%' && str[i + 1] && str[i + 1] == 'x')
        {
            len += ft_puthex(va_arg(ap, unsigned int));
            i++;   
        }
        else
            len += write(1, &str[i], 1);
        i++;
    }
    va_end(ap);
    return (len);
}


int ft_putchar(char c)
{
    return (write(1, &c, 1));
}

int ft_putstr(char *s)
{
    int len;

    len = 0;
    if (!s)
        return (ft_putstr("(null)"));
    while (*s)
    {
        write(1, s++, 1);
        len++;
    }
    return (len);
}

int ft_get_len(int n, int div)
{
    int len = 0;

    if (n < 0)
        n *= -1;
    while (n)
    {
        n = n / div;
        len++;
    }
    return (len);
}

int ft_putnbr(int n)
{
    char s[100];
    int len;
    int flag;

    if (n == 0)
        return (ft_putstr("0"));
    if (n == 2147483647)
        return (ft_putstr("2147483647"));
    if (n == -2147483648)
        return (ft_putstr("-2147483648"));
    len = ft_get_len(n, 10);
    s[len] = '\0';
    if (n < 0)
    {
        s[0] = '-';
        s[len + 1] = '\0';
        len++;
        flag = 1;
        n *= -1;
    }
    while (len--)
    {
        if (flag == 1 && len == 0)
            break;
        s[len] = n % 10 + '0';
        n /= 10;
    }
    return (ft_putstr(s));
}

int ft_puthex(unsigned int n)
{
    char s[100];
    char *hex = "0123456789abcdef";
    int len;

    if (n == 0)
        return (ft_putstr("0"));
    if (n == 4294967295)
        return (ft_putstr("ffffffff"));
    len = ft_get_len(n, 16);
    s[len] = '\0';
    while (len--)
    {
        s[len] = hex[n % 16];
        n /= 16;
    }
    return (ft_putstr(s));
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
