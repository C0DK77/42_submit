/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:39:28 by cdesjars          #+#    #+#             */
/*   Updated: 2025/04/23 15:25:09 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_ps
{
	struct s_ps		*next;
	int				nb;
	int				rank;
}					t_ps;

typedef struct s_action
{
	struct s_action	*next;
	char			*action;
}					t_action;

//	1_FUNCTIONS
void				ft_swap_rotate(char *a, int b, t_ps **p1, t_ps **p2,
						t_action **l);
void				ft_reverse(char *a, int b, t_ps **p1, t_ps **p2,
						t_action **l);
void				ft_push(char *a, t_ps **p1, t_ps **p2, t_action **l);
void				ft_try_reverse(char *a, int b, t_ps **p2, t_ps **p1,
						t_action **l);

//	2_PILES_ACTIONS

void				ft_append_node_piles(t_ps **head, int nb);
void				ft_append_ranking(t_ps **p);
void				ft_append_node_actions(t_action **head, char *action);

//	3_VERIFS

int					ft_isint(int ac, char **av);
int					ft_verif_doublons(int ac, char **av);
int					ft_verif_ranking(t_ps **p);
int					ft_verif_group(t_ps **p, int target);
int					ft_ispartofgroup(t_ps **p, int target);
void				ft_free(void **list);
void				ft_print(t_ps **p1, t_ps **pb, t_action **l);

//	4_SORT

void				ft_sort(int len, t_ps **p1, t_ps **p2, t_action **l);
void				ft_sort_three(t_ps **p1, t_ps **p2, t_action **l);
void				ft_sort_until_five(int len, t_ps **p1, t_ps **p2,
						t_action **l);
void				ft_sortin_a(int len, t_ps **p1, t_ps **p2, t_action **l);
void				ft_dual_sort(t_ps **p1, t_ps **p2, t_action **l);
void				ft_sortin_b(int len, t_ps **p1, t_ps **p2, t_action **l);

//	UTILS

int					ft_list_size(t_ps *p);
int					ft_max_min_rank(char *a, t_ps *p);
int					ft_get_position(t_ps *p, int target);
long				ft_atoi_long(const char *s);
int					ft_get_chunks(int size);
void				ft_action_opti(t_action **l);
int					ft_rules_opti(char *action, char *next_action, char **res);

int					needs_rotate_a(t_ps *a);
int					needs_reverse_rotate_a(t_ps *a);
int					ft_get_rank_last_nb(t_ps *p);

void				push_swap(int ac, char **av);

#endif
