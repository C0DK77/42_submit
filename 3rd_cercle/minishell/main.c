/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/01 12:05:05 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*line;

	(void)argc;
	(void)argv;
	while ((line = readline(prompt())) != NULL)
	{
		if (*line)
			add_history(line);
		printf("%s\n", line);
		parse(line);
		free(line);
	}
	printf("exit\n");
	return (0);
}

void	parse(char *line)
{
	int		i;
	t_token	*split_line;

	i = 0;
	split_line = NULL;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break ;
		if (ft_isoperator(line[i]))
		{
			parse_operator(line, i);
		}
		if (ft_issinglequote(line[i]))
		{
			ft_parse_word_issinglequote(line, i);
		}
		if (ft_isdoublequote(line[i]))
		{
			ft_parse_word_isdoublequote(line, i);
		}

	}
}

int	ft_add_list(t_token **split_line, char *str)
{
	t_token *new_token;
	t_token *last;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		free(str);
		return (0);
	}
	new_token->type = TOKEN_WORD;
	new_token->value = str;
	new_token->next = NULL;

	if (*split_line == NULL)
	{
		*split_line = new_token;
	}
	else
	{
		last = *split_line;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
	return (1);
}