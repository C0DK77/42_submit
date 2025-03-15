/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:39:28 by cdesjars          #+#    #+#             */
/*   Updated: 2025/03/15 14:20:43 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	int				nbr;
	int				value;
	int				median;
	int	target_node;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

void	ft_append_node(t_list **head, int nbr, int target_node);
void	ft_list_swap(t_list **pile);
void	ft_list_push(t_list **pile_1, t_list **pile_2);
void	ft_list_rotate(t_list **pile);
void	ft_list_reverse_rotate(t_list **pile);
void	ft_print_pile(t_list *pile_a, t_list *pile_b);
void	push_swap(int ac, char **av);

#endif
