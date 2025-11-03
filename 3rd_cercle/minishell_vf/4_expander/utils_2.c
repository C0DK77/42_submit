/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:35:19 by codk              #+#    #+#             */
/*   Updated: 2025/10/26 07:16:55 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_expander_dollar_pos(char *s, int i, t_var_pos *var)
{
	int	j;

	j = i + 1;
	if (!s[j] && ((!ft_isalpha(s[j]) || s[j] != '_' || s[j] != '?')))
		return (0);
	if (s[j] == '?')
	{
		var->start = i;
		var->name = malloc(sizeof(char) * 2);
		if (!var->name)
			return (-1);
		var->name[0] = '?';
		var->name[1] = '\0';
		var->end = j + 1;
		return (j);
	}
	return (ft_expander_extract_var(s, var, i, j));
}

void	*ft_expander_cleanup_var(t_var_pos *var, int i)
{
	while (--i >= 0)
		free(var[i].name);
	return (free(var), NULL);
}

char	*ft_expander_get_var_value(t_shell *sh, char *var)
{
	char	*a;
	char	*s;

	if (ft_strncmp(var, "?", 1) == 0)
	{
		a = ft_itoa(sh->last_exit);
		return (a);
	}
	s = ft_env_search_value(sh->env, var);
	if (s)
		return (ft_strdup(s));
	return (ft_strdup(""));
}

int	ft_expander_len(char *a, t_var_pos *var, char **s, int count)
{
	int	j;
	int	i;

	j = ft_strlen(a);
	i = 0;
	while (i < count)
	{
		j -= (var[i].end - var[i].start);
		j += ft_strlen(s[i]);
		i++;
	}
	return (j);
}

void	ft_expander_copy_value(char *s, int *i, char *val)
{
	int	j;
	int	len;

	len = ft_strlen(val);
	j = 0;
	while (j < len)
	{
		s[(*i)++] = val[j];
		j++;
	}
}
