#include "../header/minishell.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

int    gn_strlen(char *str)
{
    int    i;

    i = 0;
    if(!str)
        return(0);
    while(str[i] != '\0' && str[i] != '\n')
        i++;
    if(str[i] == '\n')
        i++;
    return (i);
}

char    *gn_strjoin(char *s1, char *s2)
{
    char    *new_str;
    int    len;
    int    i;
    int    j;

    i = 0;
    j = 0;
    len = gn_strlen(s1) + gn_strlen(s2);
    new_str = (char *)malloc(sizeof(char) * len + 1);
    if (!new_str)
    {
        free(s1);
        return (NULL);
    }
    while (s1 && s1[i])
    {
        new_str[i] = s1[i];
        i++;
    }
    while(s2 && s2[j])
    {
        new_str[i] = s2[j];
        if(new_str[i] == '\n')
            break ;
        i++;
        j++;
    }
    new_str[len] = '\0';
    free(s1);
    return(new_str);
}

int    update_buffer(char *buff)
{
    int    i;
    int    j;
    int    flag;

    flag = 0;
    i = 0;
    j = 0;
    while(buff[i])
    {
        if(flag)
            buff[j++] = buff[i];
        if(buff[i] == '\n')
            flag = 1;
        buff[i++] = '\0';
    }
    return (flag);
}

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    char        *line;
    int          bytes;

    if(fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    line = NULL;
    bytes = 0;
    while (buffer[0] || (bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        line = gn_strjoin(line, buffer);
        if (!line)
            return (NULL);
        if(update_buffer(buffer))
            break ;   
    }
    if (line && bytes < 0)
    {
        free(line);
        line = NULL;
    }
    return(line);
}
