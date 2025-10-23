
#include <stdio.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print_tab(int tab[10])
{
	int	i;

	i = 0;
	while (i < 10)
	{
		ft_putchar(tab[i] + 48);
		i++;
	}
	ft_putchar('\n');
}

int	ft_safe(int tab[10], int r, int c)
{
	int	i;

	i = 0;
	while (i < r)
	{
		if (tab[i] == c)
			return (0);
		if (tab[i] - i == c - r || tab[i] + i == c + r)
			return (0);
		i++;
	}
	return (1);
}

void	ft_solve(int tab[10], int r, int *c)
{
	int	i;

	i = 0;
	if (r == 10)
	{
		ft_print_tab(tab);
		*c += 1;
		return ;
	}
	while (i <= 9)
	{
		if (ft_safe(tab, r, i))
		{
			tab[r] = i;
			ft_solve(tab, r + 1, c);
		}
		i++;
	}
}

int	ft_ten_queens_puzzle(void)
{
	int	tab[10];
	int	i;

	i = 0;
	ft_solve(tab, 0, &i);
	return (i);
}

int	main(void)
{
	int i;
	i = ft_ten_queens_puzzle();
	printf("%i", i);
}