/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:39:28 by cdesjars          #+#    #+#             */
/*   Updated: 2025/05/18 17:16:24 by corentindes      ###   ########.fr       */
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

typedef struct s_rotation
{
	int				cnt_ra;
	int				cnt_rra;
	int				cnt_rb;
	int				cnt_rrb;
}					t_rotation;

typedef struct s_reinsert
{
	t_ps			*t;
	int				best_rank;
	int				best_cost;
	int				best_i;
	int				i;
	int				cost;
	int				moves;
}					t_reinsert;

typedef struct s_patience
{
	int				*nb;
	int				*i;
	int				*pr_i;
}					t_patience;

typedef struct s_best
{
	int				cost;
	int				rank;
	int				i;
}					t_best;

//	FUNCTIONS
void				ft_swap_rotate(char *a, t_ps **p, t_action **l);
void				ft_reverse(char *a, t_ps **p, t_action **l);
void				ft_push(char *a, t_ps **p1, t_ps **p2, t_action **l);
//	LISTS
void				ft_append_node_piles(t_ps **head, int nb);
void				ft_append_ranking(t_ps **p);
int					*ft_create_tab(t_ps *p);
void				ft_append_patience(t_ps *p, int *patience, int len);
void				ft_append_node_actions(t_action **head, char *action);
//	VERIFS
int					ft_isint(int ac, char **av);
int					ft_verif_doublons(int ac, char **av);
int					ft_verif_ranking(t_ps **pile);
void				ft_free(void **list);
void				ft_free_multiple(int ac, ...);
//	SORT
void				ft_sort(t_ps **p1, t_ps **p2, t_action **l);
void				ft_sort_three(t_ps **p, t_action **l);
void				ft_sort_big(t_ps **p1, t_ps **p2, t_action **l);
//	UTILS 1
int					ft_lst_size(t_ps *p);
int					ft_rank(char *a, int target, t_ps *p);
int					ft_pos(int rank, t_ps *p);
long				ft_atoi_long(const char *s);
int					ft_0_patience(t_ps *p);
//	UTILS 2
int					*ft_tab_add_patience(int *tab, int len, int *patience_len);
void				ft_build_patience(int *tab, int len, t_patience patience,
						int *patience_len);
int					ft_patience_pos(int *nb, int patience_len, int patience_i);
void				ft_push_b(int p_len, t_ps **p1, t_ps **p2, t_action **l);
int					ft_find_best(t_ps *p1, t_ps *p2, int *best_i);
//	UTILS 3
void				ft_push_a(t_ps **p1, t_ps **p2, int best_i, t_action **l);
void				ft_rotation_a(t_ps **p1, int pos_a, t_action **l);
void				ft_apply_rotation(t_ps **p1, t_rotation rot, t_action **l);
void				ft_calcul_rotation(t_ps **p1, int pos_a, t_rotation *rot);
int					ft_cost(int len_1, int len_2, int pos_1, int pos_2);
//	UTILS 4
void				final_rotate_a(t_ps **p, t_action **l);
void				ft_action_opti(t_action **l);
int					ft_action_dif(char *action, char *next_action);
//	MAIN
void				push_swap(int ac, char **av);
//	PRINT
void				ft_print(t_ps **p1, t_ps **pb, t_action **l);
void				ft_print_tab(int *tab, int len);
int					ft_pos_2(int rank, t_ps *p);

#endif
