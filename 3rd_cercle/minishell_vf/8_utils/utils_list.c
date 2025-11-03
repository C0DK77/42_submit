/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:43:10 by codk              #+#    #+#             */
/*   Updated: 2025/10/30 01:59:12 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_all	*ft_init_all(int i)
{
	static t_all	a;

	if (i)
	{
		a.ch = NULL;
		a.tk = NULL;
		a.cmd = NULL;
	}
	return (&a);
}

size_t	ft_count_arg(t_element *e)
{
	size_t	i;

	i = 0;
	while (e)
	{
		if (e->kind == ARG)
			i++;
		e = e->next;
	}
	return (i);
}

void	ft_fill_element(t_element *e, char **argv)
{
	size_t	i;

	i = 0;
	while (e)
	{
		if (e->kind == ARG)
		{
			if (e->u_.arg)
				argv[i] = e->u_.arg->str;
			else
				argv[i] = NULL;
			i++;
		}
		e = e->next;
	}
	argv[i] = NULL;
}

t_element	*ft_element_last_node(t_element *lmt)
{
	t_element	*t;

	t = lmt;
	if (!t)
		return (NULL);
	while (t->next)
		t = t->next;
	return (t);
}

int	ft_fill_argv(t_command *cmd, char **argv)
{
	size_t		i;
	t_element	*e;

	i = 0;
	e = cmd->element;
	while (e)
	{
		if (e->kind == ARG && e->u_.arg && e->u_.arg->str)
		{
			argv[i] = ft_strdup(e->u_.arg->str);
			if (!argv[i])
			{
				while (i > 0)
					free(argv[--i]);
				return (0);
			}
			i++;
		}
		e = e->next;
	}
	argv[i] = NULL;
	return (1);
}

void	ft_debug_parsing(t_character *c, t_token *t, t_command *cmd)
{
	t_character	*ch;
	t_token		*tk;
	t_command	*cm;
	t_element	*el;

	printf("\n===== DEBUG PARSING =====\n");
	/* --- LEXER OUTPUT --- */
	printf("Characters:\n");
	ch = c;
	while (ch)
	{
		printf("'%c' [type=%d, ctx=%d, word_id=%d]\n", ch->c, ch->type,
			ch->context, ch->word_id);
		ch = ch->next;
	}
	printf("--------------------------\n");
	/* --- TOKENS --- */
	printf("Tokens:\n");
	tk = t;
	while (tk)
	{
		printf("[%s] (type=%d)\n", tk->str, tk->type);
		tk = tk->next;
	}
	printf("--------------------------\n");
	/* --- COMMANDS --- */
	printf("Commands:\n");
	cm = cmd;
	while (cm)
	{
		printf("cmd type=%d, nb_args=%zu\n", cm->cmd, cm->nb_args);
		el = cm->element;
		while (el)
		{
			if (el->kind == ARG && el->u_.arg)
				printf("  ARG: '%s' (type=%d)\n", el->u_.arg->str,
					el->u_.arg->type);
			else if (el->kind == REDIR && el->u_.redirs)
				printf("  REDIR: target='%s' type=%d\n", el->u_.redirs->target,
					el->u_.redirs->type);
			el = el->next;
		}
		if (cm->has_pipe_out)
			printf("  (pipe out → next)\n");
		cm = cm->next;
	}
	printf("==========================\n\n");
}

void	ft_debug_expander(t_command *cmd)
{
	t_command *cm;
	t_element *el;

	printf("\n===== DEBUG EXPANDER =====\n");

	cm = cmd;
	while (cm)
	{
		printf("Command type: %d, nb_args: %zu\n", cm->cmd, cm->nb_args);

		el = cm->element;
		while (el)
		{
			if (el->kind == ARG && el->u_.arg)
			{
				printf("  ARG: '%s' (type=%d)\n", el->u_.arg->str,
					el->u_.arg->type);
			}
			else if (el->kind == REDIR && el->u_.redirs)
			{
				printf("  REDIR: target='%s' type=%d target_type=%d\n",
					el->u_.redirs->target, el->u_.redirs->type,
					el->u_.redirs->target_type);
			}
			el = el->next;
		}
		if (cm->has_pipe_out)
			printf("  (pipe out → next command)\n");
		cm = cm->next;
	}
	printf("===========================\n\n");
}