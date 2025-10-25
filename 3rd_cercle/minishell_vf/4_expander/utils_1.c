/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:35:13 by codk              #+#    #+#             */
/*   Updated: 2025/10/25 07:28:52 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_var_pos	*ft_expander_var_pos(char *str, int *count)
{
	t_var_pos	*vars;
	int			i;
	int			j;
	int			res;

	*count = ft_expander_var_count(str);
	if (*count == 0)
		return (NULL);
	vars = malloc(sizeof(t_var_pos) * (*count));
	if (!vars)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			res = ft_expander_dollar_pos(str, i, &vars[j]);
			if (res == -1)
				return (cleanup_vars_pos(vars, j));
			if (res > 0)
				i = res + (++j * 0);
		}
	}
	return (vars);
}

char	**ft_expander_value(t_shell *sh, t_var_pos *vars, int count)
{
	char	**a;
	int		i;

	a = malloc(sizeof(char *) * (count + 1));
	if (!a)
		return (NULL);
	i = 0;
	while (i < count)
	{
		a[i] = get_variable_value(sh, vars[i].name);
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

	ex = malloc(sizeof(char) * (calculate_expand_length(a, var, val, i) + 1));
	if (!ex)
		return (NULL);
	orig_i = 0;
	exp_i = 0;
	var_i = 0;
	while (a[orig_i])
	{
		if (var_i < i && orig_i == var[var_i].start)
		{
			copy_value(ex, &exp_i, val[var_i]);
			orig_i = var[var_i].end;
			var_i++;
		}
		else
			ex[exp_i++] = a[orig_i++];
	}
	ex[exp_i] = '\0';
	return (ex);
}

t_element	*ft_expander_empty_var(t_command *cmd, t_element *e)
{
	t_element	*next;

	next = e->next;
	cmd->element = next;
	return (free(e->u_.arg->str), free(e->u_.arg), free(e), next);
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
			if (valid_variable_char(s[j]) || s[j] == '?')
			{
				count++;
				while (valid_variable_char(s[j]) || s[j] == '?')
					j++;
				i = j - 1;
			}
		}
		i++;
	}
	return (count);
}
