#include "permutation.h"

char *alpha_sort(char *av)
{
    char *buf = av;
    int len = strlen(buf);

    int i = 1;
    while(i < len)
    {
        char current = buf[i];
        int j = i;
        while(j > 0 && buf[j-1] > current)
        {
            buf[j] = buf[j-1];
            j--;
        }
        buf[j] = current;
        i++;
    }
    buf[i] = 0;

    return buf;
}

void perm_rec(char *str, char *perm, char *used, int len, int d)
{
    if (d == len)
    {
        write(1, perm, len);
        write(1, "\n", 1);
        return;
    }

    int i = 0;
    while(i < len)
    {
        if(!used[i])
        {
            used[i] = 1;
            perm[d] = str[i];
            perm_rec(str, perm, used, len, d + 1);
            used[i] = 0;
        }
        i++;
    }
    return;
}

void backtrack(char *str)
{
    int len = strlen(str);
    char *perm = malloc(len);
    char *used = calloc(1, len);
    perm_rec(str, perm, used, len, 0);
}

int main (int ac, char **av) // mettre dna lordre puis afficher toutes les possibilites
{
    if (ac != 2)
        return 1;

    char *str = alpha_sort(av[1]);
    if(!str)
        return 1;

    backtrack(str);

    return 0;
}
