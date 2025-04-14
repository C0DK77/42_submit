/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:39:28 by cdesjars          #+#    #+#             */
/*   Updated: 2025/04/14 22:48:45 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_ps_list
{
	int					nbr;
	int					value;
	int					median;
	int					target_node;
	struct s_ps_list	*next;
	struct s_ps_list	*prev;
}						t_ps_list;

//	FONCTIONS DE TRI

void					ft_list_swap(t_ps_list **pile);
void					ft_list_push(t_ps_list **pile_1, t_ps_list **pile_2);
void					ft_list_rotate(t_ps_list **pile);
void					ft_list_reverse_rotate(t_ps_list **pile);

// 	FONCTIONS LISTES

void					ft_append_node(t_ps_list **head, int nbr,
							int target_node);
void					ft_append_target_node(t_ps_list **pile);

// 	FONCTIONS VERIFICATION

int						ft_verification_args(int ac);
int						ft_verif_int(int ac, char **av);
int						ft_verif_classement(t_ps_list **pile);
void					ft_print_pile(t_ps_list **pile_a, t_ps_list **pile_b,
							int ac);
int						ft_verif_doublons(t_ps_list **pile);

//	RULES

void					ft_split_list_between_a_and_b(t_ps_list **pile_a,
							t_ps_list **pile_b, int ac);
void					ft_rules_2_elements(char a, t_ps_list **pile);
void					ft_push_in_a(t_ps_list **pile_a, t_ps_list **pile_b);
void					ft_rules_3_elements(t_ps_list **pile);

//	FONCTION PUSH_SWAP

void					push_swap(int ac, char **av);

#endif
