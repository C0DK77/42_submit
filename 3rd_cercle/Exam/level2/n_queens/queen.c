#include <stdlib.h>
#include <stdio.h>

int is_safe(int *pos, int col, int row)
{
    int i = 0;

    while (i < col)
    {
        // même ligne
        if (pos[i] == row)
            return (0);

        // diagonale ↘
        if (pos[i] - row == i - col)
            return (0);

        // diagonale ↗
        if (row - pos[i] == i - col)
            return (0);

        i++;
    }
    return (1);
}


void print_solution(int *pos, int n)
{
    int i = 0;

    while (i < n)
    {
        fprintf(stdout, "%d", pos[i]);
        if (i + 1 < n)
            fprintf(stdout, " ");
        i++;
    }
    fprintf(stdout, "\n");
}


void solve(int n, int col, int *pos)
{
    int row = 0;

    if (col == n)
    {
        print_solution(pos, n);
        return;
    }

    while (row < n)
    {
        if (is_safe(pos, col, row))
        {
            pos[col] = row;
            solve(n, col + 1, pos);
        }
        row++;
    }
}


int main(int ac, char **av)
{
    if (ac != 2)
        return (1);

    int n = atoi(av[1]);

    int pos[n];  // tableau local SANS malloc

    solve(n, 0, pos);

    return (0);
}
