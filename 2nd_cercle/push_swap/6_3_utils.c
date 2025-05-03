/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_3_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:11:54 by corentindes       #+#    #+#             */
/*   Updated: 2025/05/03 15:20:20 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

void	final_rotate_a(t_ps **p1, t_ps **p2, t_action **l)
{
	int	pos_min;
	int	sz;
	int	moves;

	if (!p1 || !*p1)
		return ;
	pos_min = ft_get_position(*p1, ft_max_min_rank("min", *p1));
	sz = ft_list_size(*p1);
	if (pos_min <= sz / 2)
	{
		while (pos_min > 0)
		{
			ft_swap_rotate("ra", 1, p1, p2, l);
			pos_min--;
		}
	}
	else
	{
		moves = sz - pos_min;
		while (moves > 0)
		{
			ft_reverse("rra", 1, p1, p2, l);
			moves--;
		}
	}
}

void	execute_rotations(t_ps **p1, t_ps **p2, int pos_a, int pos_b, int sz_a,
		int sz_b, t_action **l)
{
    int cnt_ra  = (pos_a <= sz_a/2) ? pos_a : 0;
    int cnt_rra = (pos_a >  sz_a/2) ? sz_a - pos_a : 0;
    int cnt_rb  = (pos_b <= sz_b/2) ? pos_b : 0;
    int cnt_rrb = (pos_b >  sz_b/2) ? sz_b - pos_b : 0;

    while (cnt_ra > 0 && cnt_rb > 0)
    {
        ft_swap_rotate("ra", 1, p1, p2, l);
        ft_swap_rotate("rb", 1, p2, p1, l);
        cnt_ra--;
        cnt_rb--;
        printf("\nRA RB oooooo\n");
    }

    while (cnt_rra > 0 && cnt_rrb > 0)
    {
        ft_reverse("rra", 1, p1, p2, l);
        ft_reverse("rrb", 1, p2, p1, l);
        cnt_rra--;
        cnt_rrb--;
        printf("\nRRA RRB oooooo\n");
    }

    while (cnt_ra--  > 0)
    {
        ft_swap_rotate("ra",  1, p1, p2, l);
        printf("\nRA oooooo\n");
    }  
    while (cnt_rra-- > 0)
    {
        ft_reverse     ("rra", 1, p1, p2, l);
        printf("\nRRA oooooo\n");
    }
    while (cnt_rb--  > 0)
    {
        ft_swap_rotate("rb",  1, p2, p1, l);
        printf("\nRB oooooo\n");
    }
    while (cnt_rrb-- > 0) 
    {
        ft_reverse     ("rrb", 1, p2, p1, l);
        printf("\nRRB oooooo\n");
    }

}

int get_lis_length(int *tab, int len)
{
    int *tail = malloc(sizeof(*tail) * len);
    int  lis_end = 0;
    int  i = 0;

    while (i < len)
    {
        int x = tab[i];
        int l = 0, r = lis_end;
        while (l < r)
        {
            int m = (l + r) / 2;
            if (tail[m] < x)
                l = m + 1;
            else
                r = m;
        }
        tail[l] = x;
        if (l == lis_end)
            lis_end++;
        i++;
    }

    free(tail);
    return lis_end;
}