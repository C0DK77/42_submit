//en cours//#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *str)
{
  int i = 0;
  while (str[i])
    i++;
  return (i);
}

void ft_swap(char *a, char *b)
{
  char tmp = *a;
  *a = *b;
  *b = tmp;
}

char *ft_sort(char *str)
{
  for (int i = 0; str[i]; i++)
  {
    for (int j = 1 + i; str[j]; j++)
    {
      if (str[i] > str[j])
        ft_swap(&str[i], &str[j]);
    }
  }
  return (str);
}

int next_permutation(char *str, int len)
{
  int i = len - 2;
  int j = len - 1;
  while (i >= 0 && str[i] >= str[i + 1])
    i--;
  if (i < 0)
    return (0);
  while (str[j] <= str[i])
    j--;
  ft_swap(&str[i], &str[j]);
  for (int left = i + 1, right = len - 1; left < right; left++, right--)
    ft_swap(&str[left], &str[right]);
  return (1);
}

int main(int argc, char **argv)
{
  if (argc != 2)
    return (1);
  int len = ft_strlen(argv[1]);
  char *str = ft_sort(argv[1]);
  write(1, str, len);
  write(1, "\n", 1);
  while (next_permutation(str, len))
  {
    write(1, str, len);
    write(1, "\n", 1);
  }
  return (0);
}
/*Assignment name : permutations

Expected files : *.c *.h
Allowed functions : puts, malloc, calloc, realloc, free, write
---------------------------------------------------------------

Write a program that will print all the permutations of a string given as argument.

The solutions must be given in alphabetical order.

We will not try your program with strings containing duplicates (eg: 'abccd')

For example this should work:
$> ./permutations a | cat -e
a$
$> ./permutations ab | cat -e
ab$
ba$
$> ./permutations abc | cat -e
abc$
acb$
bac$
bca$
cab$
cba$*/
