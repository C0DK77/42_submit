/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corentindesjars <corentindesjars@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 04:35:19 by codk              #+#    #+#             */
/*   Updated: 2025/10/25 07:28:36 by corentindes      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_expander_dollar_pos(char *s, int i, t_var_pos *var)
{
	int	j;

	j = i + 1;
	if (!s[j] || (!valid_variable_char(s[j]) && s[j] != '?'))
		return (0);
	if (s[j] == '?')
		return (extract_special_var_pos(var, i, j));
	return (extract_variable_pos(s, var, i, j));
}

int	ft_expander_dollar(char *s, int i, char **a, int *count)
{
	int		j;
	int		k;
	char	*var;

	j = i + 1;
	if (!valid_variable_char(s[j]) && s[j] != '?')
		return (i);
	if (s[j] == '?')
	{
		var = create_special_var();
		if (!var)
			return (-1);
		a[(*count)++] = var;
		return (j);
	}
	var = extract_normal_var(s, j, &k);
	if (!var)
		return (-1);
	a[(*count)++] = var;
	return (k);
}

char	*get_variable_value(t_shell *shell, char *var_name)
{
	char	*buffer;
	char	*value;

	if (ft_strncmp(var_name, "?", 1) == 0)
	{
		buffer = ft_itoa(shell->last_exit);
		return (buffer);
	}
	value = find_variable_in_env(shell->env, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

int	calculate_expanded_length(char *original, t_var_pos *vars, char **values,
		int var_count)
{
	int	new_len;
	int	i;

	new_len = ft_strlen(original);
	i = 0;
	while (i < var_count)
	{
		new_len -= (vars[i].end - vars[i].start);
		new_len += ft_strlen(values[i]);
		i++;
	}
	return (new_len);
}

void	copy_value(char *expanded, int *exp_idx, char *value)
{
	int	i;
	int	len;

	len = ft_strlen(value);
	i = 0;
	while (i < len)
	{
		expanded[(*exp_idx)++] = value[i];
		i++;
	}
}

int	valid_variable_char_number(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	strlen_variable(char *str, int j)
{
	int	count;

	count = 0;
	if (str[j] == '?')
		return (1);
	while (str[j] && valid_variable_char(str[j]))
	{
		count++;
		j++;
	}
	return (count);
}

char	**find_variable_in_str(char *str)
{
	char	**variable;
	int		i;
	int		index;
	int		result;

	if (how_many_variable(str) == 0)
		return (NULL);
	variable = malloc(sizeof(char *) * (how_many_variable(str) + 1));
	if (!variable)
		return (NULL);
	i = -1;
	index = 0;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			result = process_dollar(str, i, variable, &index);
			if (result == -1)
				return (cleanup_variables(variable, index));
			i = result;
		}
	}
	variable[index] = NULL;
	return (variable);
}
