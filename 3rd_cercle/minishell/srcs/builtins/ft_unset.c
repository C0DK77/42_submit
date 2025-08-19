/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecid <ecid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:25:51 by ecid              #+#    #+#             */
/*   Updated: 2025/08/19 21:25:52 by ecid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int ft_unset(char **s, t_envp **l)
{
    int i;
    char **current_arg;

    i = 0;

    current_arg = s + 1; 

    while (*current_arg)
    {

        if ((*current_arg)[0] == '-' && (*current_arg)[1] != '\0')
        {

            ft_unset_error(0, *current_arg); 
            continue;
        }

        if (!ft_unset_check_identifier(current_arg))
        {
            i = 1; 
            current_arg++;
            continue;
        }
        

        ft_unset_change(current_arg, l);
        current_arg++;
    }
    

    if (i)
        g_exit_status = 1;
    else
        g_exit_status = 0; 
    return (g_exit_status);
}


int ft_unset_check_identifier(char **s)
{
    char    *t;

    t = *s;
    
 
    if (!t || (!ft_isalpha((unsigned char)t[0]) && t[0] != '_'))
    {
     
        char *error_msg = ft_strjoin_three("minishell: unset: `", t, "': not a valid identifier\n");
        if (error_msg)
        {
            write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
            free(error_msg);
        }
        else
        {
            write(STDERR_FILENO, "minishell: unset: not a valid identifier\n", 41);
        }
        return (0);
    }
    
   
    t++; 
    while (*t)
    {
        if (!(ft_isalnum((unsigned char)*t) || *t == '_'))
        {
            char *error_msg = ft_strjoin_three("minishell: unset: `", *s, "': not a valid identifier\n");
            if (error_msg)
            {
                write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
                free(error_msg);
            }
            else
            {
                write(STDERR_FILENO, "minishell: unset: not a valid identifier\n", 41);
            }
            return (0);
        }
        t++;
    }
    return (1);
}

void ft_unset_change(char **s, t_envp **l)
{
    t_envp  *current;
    t_envp  *prev;
    char    *var_to_unset = *s;

    current = *l;
    prev = NULL;

    while (current)
    {
        if (ft_strcmp(current->var, var_to_unset) == 0)
        {
            if (prev)
                prev->next = current->next;
            else 
                *l = current->next;
            
        
            free(current->var);
            if (current->value)
                free(current->value);
            free(current);
            break ;
        }
        prev = current;
        current = current->next;
    }
}

int ft_unset_error(int i, char *s)
{
    char *error_msg;

    g_exit_status = 1;
    if (i == 0)
    {
        error_msg = ft_strjoin_three("minishell: unset: `", s, "': invalid option\n");
        if (error_msg)
        {
            write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
            free(error_msg);
        }
        else
        {
            write(STDERR_FILENO, "minishell: unset: invalid option\n", 33);
        }
        write(STDERR_FILENO, "unset: usage: unset name [name ...]\n", 36);
        g_exit_status = 2; 
    }

    return (g_exit_status);
}


