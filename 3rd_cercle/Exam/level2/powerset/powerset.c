#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void print_tmp(int *stock, int d)
{
    int i = 0;

    while (i < d)
    {
        printf("%d", stock[i]);
        if(i + 1 < d)
            printf(" ");
        i++;
    }
    printf("\n");

    return;
}

void backtrack(int a, int *list, int *stock, int target, int len_list, int d)
{
    if(a == len_list) // tout larbre a ete parcouru (toutes les branches de solution)
    {
        if(target == 0)
            print_tmp(stock, d);
        return;
    }

    backtrack(a + 1, list, stock, target, len_list, d);

    stock[d] = list[a];

    backtrack(a + 1, list, stock, target - list[a], len_list, d + 1);

}

int main (int ac, char **av)
{   
    if (ac < 2)
        return 1;

    int target = atoi(av[1]);
    int len_list = ac - 2;
    int list[len_list];
    int stock[ac - 1];

    int i = 2;
    while(i < ac)
    {
        list[i - 2] = atoi(av[i]);
        i++;
    }

    backtrack(0, list, stock, target, len_list, 0);

    return 0;
}