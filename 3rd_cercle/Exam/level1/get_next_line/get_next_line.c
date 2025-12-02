#include "get_next_line.h"

static int has_newline(char *s)
{
    if (!s) return 0;
    while (*s)
        if (*s++ == '\n')
            return 1;
    return 0;
}

static int ft_len(char *s)
{
    int i = 0;
    while (s && s[i])
        i++;
    return i;
}

static char *ft_strjoin(char *s1, char *s2)
{
    int len1 = ft_len(s1);
    int len2 = ft_len(s2);
    char *res = malloc(len1 + len2 + 1);
    int i = 0, j = 0;

    if (!res)
        return NULL;

    while (i < len1)
    {
        res[i] = s1[i];
        i++;
    }
    while (j < len2)
    {
        res[i + j] = s2[j];
        j++;
    }
    res[i + j] = '\0';

    free(s1);
    return res;
}

static char *extract_line(char *stash)
{
    int i = 0;
    char *line;

    if (!stash || !stash[0])
        return NULL;

    while (stash[i] && stash[i] != '\n')
        i++;

    line = malloc(i + (stash[i] == '\n') + 1);
    if (!line) return NULL;

    i = 0;
    while (stash[i] && stash[i] != '\n')
    {
        line[i] = stash[i];
        i++;
    }
    if (stash[i] == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return line;
}

static char *clean_stash(char *stash)
{
    int i = 0, j = 0;
    char *newstash;

    while (stash[i] && stash[i] != '\n')
        i++;

    if (!stash[i])
    {
        free(stash);
        return NULL;
    }

    newstash = malloc(ft_len(stash) - i);
    if (!newstash) return NULL;

    i++;
    while (stash[i])
        newstash[j++] = stash[i++];

    newstash[j] = '\0';
    free(stash);
    return newstash;
}

char *get_next_line(int fd)
{
    static char *stash = NULL;
    char        *buf;
    int         bytes = 1;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    buf = malloc(BUFFER_SIZE + 1);      // 🔥 ICI : malloc du buffer
    if (!buf)
        return NULL;

    while (bytes > 0 && !has_newline(stash))
    {
        bytes = read(fd, buf, BUFFER_SIZE);
        if (bytes < 0)
            return (free(buf), free(stash), stash = NULL, NULL);

        buf[bytes] = '\0';
        stash = ft_strjoin(stash, buf);
        if (!stash)
            return (free(buf), NULL);
    }

    free(buf);  // 🔥 IMPORTANT : free du buffer AVANT de retourner quoi que ce soit

    line = extract_line(stash);
    stash = clean_stash(stash);
    return line;
}


int main(void)
{
    int     fd;
    char    *line;

    fd = open("read.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("Erreur ouverture fichier\n");
        return (1);
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("LINE: %s", line);
        free(line);
    }

    close(fd);
    return (0);
}