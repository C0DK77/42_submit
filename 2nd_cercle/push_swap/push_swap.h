/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:39:28 by cdesjars          #+#    #+#             */
/*   Updated: 2025/04/18 20:48:01 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_ps_list
{
	int						nb;
	int						rank;
	struct s_ps_list		*next;
}							t_ps_list;

typedef struct s_ps_list_action
{
	char					*action;
	struct s_ps_list_action	*next;
}							t_ps_list_action;

void						ft_functions(char *a, t_ps_list **pile,
								t_ps_list_action **list);
void						ft_function_revert(char *a, t_ps_list **pile,
								t_ps_list_action **list);
void						ft_function_push(char *a, t_ps_list **pile_1,
								t_ps_list **pile_2, t_ps_list_action **list);
void						ft_sort(int size, t_ps_list **pile_a,
								t_ps_list **pile_b, t_ps_list_action **list);
void						ft_sortin_a(int size, t_ps_list **pile_a,
								t_ps_list **pile_b, t_ps_list_action **list);
void						ft_sortin_b(int size, t_ps_list **pile_a,
								t_ps_list **pile_b, t_ps_list_action **list);

int							ft_list_size(t_ps_list *pile);
void						ft_append_node(t_ps_list **head, int nb);
void						ft_append_rank(t_ps_list **pile);
int							ft_max_min_rank(char *a, t_ps_list *pile);
int							ft_get_position(t_ps_list *pile, int target);
void						ft_append_node_list(t_ps_list_action **head,
								char *action);

long						ft_atoi_long(const char *str);
int							ft_isint(int ac, char **av);
int							ft_verif_doublons(int ac, char **av);
int							ft_verif_ranking(char a, t_ps_list **pile);
int							ft_ispartofgroup(t_ps_list **pile, int target);
void						ft_print_pile(t_ps_list **pile_a,
								t_ps_list **pile_b, t_ps_list_action **list);
void						ft_free_pile(t_ps_list **pile_1, t_ps_list **pile_2,
								t_ps_list_action **list);

void						ft_sort_three(t_ps_list **pile,
								t_ps_list_action **list);
int							ft_max_min_rank(char *a, t_ps_list *pile);
void						ft_sort_five(int size, t_ps_list **pile_a,
								t_ps_list **pile_b, t_ps_list_action **list);

void						push_swap(int ac, char **av);

#endif
