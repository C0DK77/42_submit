/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/06/27 18:12:41 by corentindes      ###   ########.fr       */
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
	int				i;
	t_token	*split_line;

	i = 0;
	split_line = NULL;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break;
		if (ft_isoperator(line[i]))
		{
			parse_operator(line, i);
		}
		if (ft_issinglequote(line[i]))
		{
			ft_parse_word(split_line, line, i);
		}

	}
}
