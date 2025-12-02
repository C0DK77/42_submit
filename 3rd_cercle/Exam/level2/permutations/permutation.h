#ifndef PERMUTATION_H
#define PERMUTATION_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

char *alpha_sort (char *av);

void perm_rec(char *str, char *used, char *perm, int len, int d);

void backtrack(char *str);



#endif

