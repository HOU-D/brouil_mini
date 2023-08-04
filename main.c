/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:24:16 by mberrouk          #+#    #+#             */
/*   Updated: 2023/08/02 01:07:57 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Builtins/builtins.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./include/minishell.h"
#include "./include/shell.h"

/**
 * new_node - Creates a new node for the environment list
 * @key: The key for the environment variable
 * @val: The value for the environment variable
 * @idx: The index of the environment variable
 *
 * Return: A pointer to the newly created node, or NULL on failure
 */
t_env	*new_node(char *key, char *val, int idx)
{
	t_env	*new;

	(void)idx;
	new = malloc(sizeof(t_env));
	if (!new)
		return (0x00);
	new->next = 0x00;
	new->key = key;
	new->val = val;
	return (new);
}

/**
 * add_node - Adds a node to the end of the environment list
 * @lst: A pointer to the head of the environment list
 * @new: A pointer to the node to be added
 */
void	add_node(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst)
		return ;
	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/**
 * fetch_env - Fetches the environment variables and creates a linked list
 * @envlist: A pointer to the head of the list
 * @env: The array of environment variables
 */
void	fetch_env(t_env **envlist, char **env)
{
	int		i;
	char	**arg;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		arg = ft_split(env[i], '=');
		if (arg)
			add_node(envlist, new_node(arg[0], arg[1], i));
		i++;
	}
	add_node(envlist, new_node(ft_strdup("OLDPWD"), NULL, i));
}



int	main(int ac, char *av[], char *env[])
{
	(void)av;
	t_env	*envlist;
	t_cmd	*cmds;
	char	*line;
	if (ac != 1)
		return (1);
	line = NULL;
	cmds = NULL;
	fetch_env(&envlist, env);
	// ft_env(envlist, av);
	while (1)
	{
		line = readline("\033[1;34mminishell$  \033[1;0m");;
		if (!line)
		{
			//continue;
			return (EXIT_FAILURE);
		}
		add_history(line);
		if (line && *line)
		{
			builtins_main(&envlist, &line);
			init_parse(&cmds, line, env);
			//exec_cmds(cmds, 0, env);
		}
		else {
			continue;
		}
	}

	/**
	 * Test 
	for (int i = 0; envlist; i++)
	{
		printf("env : %s\n", env[i]);
		printf("envlst : %s %s\n", envlist->key, envlist->val);
		envlist = envlist->next;
	}
	*/
}
