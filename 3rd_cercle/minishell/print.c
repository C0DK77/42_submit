/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:13:20 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/12 12:54:30 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	ft_print_token(t_token *l)
{
	t_token	*t;

	t = l;
	while (t)
	{
		printf("[TOKEN] TYPE =>%d  VALUE =>'%s'\n", t->type, t->value);
		t = t->next;
	}
}

void	ft_print_parsing(t_parsing *lst)
{
	t_parsing	*p;
	int			i;

	p = lst;
	while (p)
	{
		printf("=== Command ===\n");
		if (p->line)
		{
			i = 0;
			while (p->line[i])
			{
				printf("argv[%d]: %s\n", i, p->line[i]);
				i++;
			}
		}
		else
			printf("argv: (empty)\n");
		if (p->infile)
			printf("infile: %s\n", p->infile);
		if (p->outfile)
			printf("outfile: %s (append=%d)\n", p->outfile, p->append);
		if (p->heredoc)
			printf("heredoc: yes\n");
		printf("separator: %d\n", p->sep);
		p = p->next;
	}
}
