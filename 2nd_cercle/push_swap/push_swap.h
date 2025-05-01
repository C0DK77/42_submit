/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:39:28 by cdesjars          #+#    #+#             */
/*   Updated: 2025/05/01 15:05:09 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_ps
{
	struct s_ps		*next;
	int				nb;
	int				rank;
	int				patience;
}					t_ps;

typedef struct s_action
{
	struct s_action	*next;
	char			*action;
}					t_action;

typedef struct s_cost
{
	int				rb;
	int				rrb;
	int				ra;
	int				rra;
	int				cost;
	int				dir_b;
	int				dir_a;
	t_ps			*node;
}					t_cost;

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
int					*ft_create_tab(t_ps *p, int len);
void				ft_append_lis(t_ps *p, int *lis, int len);
void				ft_append_node_actions(t_action **head, char *action);

//	3_VERIFS

int					ft_isint(int ac, char **av);
int					ft_verif_doublons(int ac, char **av);
int					ft_verif_ranking(t_ps **pile);
int					ft_verif_group(t_ps **p, int target);
void				ft_free(void **list);
void				ft_print(t_ps **p1, t_ps **pb, t_action **l);
void				print_tab(int *tab, int len);

//	4_SORT

void				ft_sort(int len, t_ps **p1, t_ps **p2, t_action **l);
void				ft_sort_three(t_ps **p1, t_ps **p2, t_action **l);
void				ft_sort_until_five(int len, t_ps **p1, t_ps **p2,
						t_action **l);
void				ft_sort(int len, t_ps **p1, t_ps **p2, t_action **l);

//	ACTIONS

void				ft_action_opti(t_action **l);
int					ft_rules_opti(char *action, char *next_action, char **res);

//	UTILS 1

int					ft_list_size(t_ps *p);
int					ft_max_min_rank(char *a, t_ps *p);
int					ft_get_position(t_ps *p, int target);
int					ft_get_target_pos(t_ps *a, int rank);
long				ft_atoi_long(const char *s);

//	UTILS 2

int					*ft_tab_add_patience(int *tab, int len, int *lis_len);
void				ft_push_b(int len, t_ps **p1, t_ps **p2, t_action **l);
int					ft_get_next_non_lis(t_ps *p);
void				reinsert_b_greedy(t_ps **p1, t_ps **p2, t_action **l);
int					ft_get_cost(int sz_a, int sz_b, int pos_a, int pos_b);

//	UTILS 3

void				ft_insert_b_in_a(t_ps **p1, t_ps **p2, t_action **l);
void				final_rotate_a(t_ps **p1, t_action **l);
void				execute_rotations(t_ps **p1, t_ps **p2, int pos_a,
						int pos_b, int sz_a, int sz_b, t_action **l);
						
//	MAIN

void				push_swap(int ac, char **av);

#endif
