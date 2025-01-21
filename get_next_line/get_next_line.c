#include "libc.h"

#define BUFFER_SIZE 10

char *ft_strdup(char *s);
int ft_strlen(char *s);

int ft_strchr(char *s)
{
    if (!s)
        return (0);
    int i = 0;
    while (s[i])
    {
        if (s[i] == '\n')
            return (i);
        i++;
    }
    return (0);
}

char *ft_shrink_line(char *r)
{
    char *s;
    int i = 0;
    int flag = 0;
    if (!r)
        return (NULL);
    if (ft_strchr(r))
        flag = 1;
    if (flag)
        s = malloc(ft_strlen(r) - (ft_strlen(r) - ft_strchr(r)) + 2);
    else
    {
        char *tmp = ft_strdup(r);
        free(r);
        return(tmp);
    }
    while (r[i] && r[i] != '\n')
    {
        s[i] = r[i];
        i++;
    }
    s[i] = '\n';
    s[i + 1] = '\0';
    return (s);
}

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
    {
        i++;
    }
    return (i);
}

char *ft_strdup(char *s)
{
    int i = 0;
    if (!s)
        return (NULL);
    char *ret = malloc(ft_strlen(s) + 1);
    if (!ret)
        return (NULL);
    while (s[i])
    {
        ret[i] = s[i];
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

char *ft_join(char *s1, char *s2)
{
    if (!s1)
        return (ft_strdup(s2));
    char *ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    int i = 0;
    while (s1[i])
    {
        ret[i] = s1[i];
        i++;
    }
    int j = 0;
    while (s2[j])
    {
        ret[i] = s2[j];
        j++;
        i++;
    }
    free(s1);
    ret[i] = '\0';
    return (ret);
}

char *ft_next_line(char *r)
{
    if (!ft_strchr(r))
        return (NULL);
    char *ret = malloc(ft_strlen(r) - ft_strchr(r) + 1);
    if (!ret)
        return (NULL);
    int i = ft_strchr(r) + 1;
    int j = 0;
    while (r[i])
    {
        ret[j] = r[i];
        i++;
        j++;
    }
    ret[i] = '\0';
    free(r);
    return (ret);
}

char *get_next_line(int fd)
{
    static char *r;
    char *buffer;
    int b;

    if (read(fd, 0, 0) == -1)
        return (NULL);
    buffer = malloc((size_t)BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    while (1)
    {
        b = read(fd, buffer, BUFFER_SIZE);
        if (b == -1 || b == 0)
            break;
        buffer[b] = '\0';
        r = ft_join(r, buffer);
        if (!r)
            return (NULL);
        if (ft_strchr(r))
            break;
    }
    free(buffer);
    buffer = r;
    r = ft_next_line(r);
    return (ft_shrink_line(buffer));
}

int main(int c, char **v)
{
    if (c != 2)
        return (1);
    int fd = open(v[1], 0);
    if (fd == -1)
        return (-1);
    char *s;
    while ((s = get_next_line(fd)))
    {
        printf("%s", s);
        free(s);
    } 
    return (0);
}
