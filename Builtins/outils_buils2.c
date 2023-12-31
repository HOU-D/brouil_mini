/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_buils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:29:44 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/03 20:30:32 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../include/minishell.h"
#include "../include/parser.h"

t_env	*searching_key(t_env *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strcmp(key, env_list->key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

void	set_oldpwd(t_env **envlist, char *dir)
{
	t_env *tmp;

	tmp = *envlist;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
			break ;
		tmp = tmp->next;
	}
	free(tmp->val);
	tmp->val = fstrdup(dir);
} 

void	set_pwd(t_env **envlist, char *dir)
{
	t_env *tmp;

	tmp = *envlist;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
			break ;
		tmp = tmp->next;
	}
	free(tmp->val);
	tmp->val = fstrdup(dir);
} 
