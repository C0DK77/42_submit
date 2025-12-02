#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>

#define CHUNK 1
int has_occurence = 0;

char *read_all(int *out_len)
{
    int len = 0;
    int r = 0;
    int capa = CHUNK;
    char *buf = malloc(capa);

    if(!buf)
        return NULL;

    while((r = read(0, buf + len, capa - len)) > 0)
    {
        len += r;
        if(len == capa)
        {
            capa *= 2;
            char *tmp = realloc(buf, capa);
            if(!tmp)
                return NULL;
            buf = tmp;
        }
    }
    
    *out_len = len;

    return buf;
}

void fill_stars(char *stars, int len_filter)
{
    int i = 0;

    while(i < len_filter)
        stars[i++] = '*';
    
    return;
}

int replace_and_write(char *buf, int out_len, char *av)
{
    char *end = buf + out_len;
    char *ptr_bloc = NULL;
    char *filter = av;
    char *tmp = buf;
    int len_filter = strlen(filter);
    char *stars = malloc(len_filter);

    if(!stars)
        return 0;

    fill_stars(stars, len_filter);
    while((ptr_bloc = memmem(tmp, end - tmp, filter, len_filter)) != NULL)
    {
        has_occurence = 1;
        write(1, tmp, ptr_bloc - tmp);
        write(1, stars, len_filter);
        tmp = ptr_bloc + len_filter;
    }

    if(has_occurence > 0)
    {
        if(tmp < end)
            write(1, tmp, end - tmp);
    }

    return 1;
}

int main(int ac, char **av) // enregistrer sortie standard et appliquer le filtrer(av[1]) dessus
{
    int len = 0;
    if(ac != 2 || (len = strlen(av[1])) == 0)
        return 1;

    len = 0;
    char *buf = read_all(&len);

    if(!buf)
    {
        perror("Error :");
        return 1;
    }

    // printf("%s", buf);

    if(!replace_and_write(buf, len, av[1]))
    {
        perror("Error :");
        free(buf);
        return 1;
    }

    return 0;
}