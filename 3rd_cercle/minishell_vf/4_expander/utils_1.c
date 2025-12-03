/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdesjars <cdesjars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:35:13 by codk              #+#    #+#             */
/*   Updated: 2025/12/03 11:02:23 by cdesjars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expander_string(t_shell *sh, char *s)
{
	t_var_pos	*var;
	char		**val;
	char		*a;
	int			i;

	var = ft_expander_var_pos(s, &i);
	if (!var || i == 0)
		return (ft_strdup(s));
	val = ft_expander_value(sh, var, i);
	if (!val)
		return (ft_free_var(var, NULL, i), NULL);
	a = ft_expander_string_create(s, var, val, i);
	return (ft_free_var(var, val, i), a);
}

t_var_pos	*ft_expander_var_pos(char *s, int *count)
{
	t_var_pos	*var;
	int			i;
	int			j;
	int			res;

	*count = ft_expander_var_count(s);
	if (*count == 0)
		return (NULL);
	var = malloc(sizeof(t_var_pos) * (*count));
	if (!var)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] == '$')
		{
			res = ft_expander_dollar_pos(s, i, &var[j]);
			if (res == -1)
				return (ft_expander_cleanup_var(var, j));
			if (res > 0)
				i = res + (++j * 0);
		}
	}
	return (var);
}

char	**ft_expander_value(t_shell *sh, t_var_pos *var, int count)
{
	char	**a;
	int		i;

	a = malloc(sizeof(char *) * (count + 1));
	if (!a)
		return (NULL);
	i = 0;
	while (i < count)
	{
		a[i] = ft_expander_get_var_value(sh, var[i].name);
		if (!a[i])
		{
			while (--i >= 0)
				free(a[i]);
			return (free(a), NULL);
		}
		i++;
	}
	return (a);
}

char	*ft_expander_string_create(char *a, t_var_pos *var, char **val, int i)
{
	char	*ex;
	int		orig_i;
	int		exp_i;
	int		var_i;

	ex = malloc(sizeof(char) * (ft_expander_len(a, var, val, i) + 1));
	if (!ex)
		return (NULL);
	orig_i = 0;
	exp_i = 0;
	var_i = 0;
	while (a[orig_i])
	{
		if (var_i < i && orig_i == var[var_i].start)
		{
			ft_expander_copy_value(ex, &exp_i, val[var_i]);
			orig_i = var[var_i].end;
			var_i++;
		}
		else
			ex[exp_i++] = a[orig_i++];
	}
	ex[exp_i] = '\0';
	return (ex);
}

int	ft_expander_var_count(char *s)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			j = i + 1;
			if (ft_isalnum(s[j]) || s[j] == '?' || s[j] == '_')
			{
				count++;
				while (ft_isalnum(s[j]) || s[j] == '_' || s[j] == '?')
					j++;
				i = j - 1;
			}
		}
		i++;
	}
	return (count);
}
