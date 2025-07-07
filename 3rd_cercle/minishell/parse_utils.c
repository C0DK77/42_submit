/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:34:00 by corentindes       #+#    #+#             */
/*   Updated: 2025/07/07 22:07:24 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	**ft_append_token(char **line, char *value)
{
	int		i;
	char	**new;

	i = 0;
	if (!value)
		return (line);
	while (line && line[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	for (int j = 0; j < i; j++)
		new[j] = line[j];
	new[i] = strdup(value);
	new[i + 1] = NULL;
	free(line);
	return (new);
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
