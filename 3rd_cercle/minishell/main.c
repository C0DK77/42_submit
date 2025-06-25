/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codk <codk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:05:29 by corentindes       #+#    #+#             */
/*   Updated: 2025/06/26 00:50:39 by codk             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv)
{
	char	*line;

	while ((line = readline("Minishell> ")) != NULL)
    {
        if (*line)
            add_history(line);
        printf("Vous avez tapé : %s\n", line);
        free(line);
    }
    printf("exit\n");
    return (0);
}

// int	ft_parse_word(char *line, int i, char c)
// {
// 	int		j;
// 	int		start;
// 	char	*str;

// 	start = i;
// 	j = 0;
// 	while (line[i] && ft_single_quote(line[i]))
// 		i++;
// 	if (line[i] == '\'')
// 	{
// 		str = malloc(sizeof(char) * (i - start + 1));
// 		while (start <= i)
// 		{
// 			str[j] = line[start];
// 			start++;
// 		}
// 		str[j] == '\0';
// 	}
// 	return (str);
// }

// void	parse(char *line)
// {
// 	int i;
// 	t_list *split_line;

// 	i = 0;
// 	split_line = NULL;
// 	while (line[i])
// 	{
// 		while (!ft_isspace(line[i]))
// 			i++;
// 		if (ft_single_quote(line[i]))
// 			ft_parse_word(line, i, '\'');
// 		if (ft_double_quote(line[i]))
// 			ft_parse_word(line, i, '\"');

// 		i++;
// 	}
// }