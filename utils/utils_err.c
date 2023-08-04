/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:34:04 by mberrouk          #+#    #+#             */
/*   Updated: 2023/07/28 17:34:05 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

/**
 * handle_error - Handles memory deallocation and returns NULL
 * @s: The array of strings to be freed
 *
 * Return: NULL
 */
char	**handle_error(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

void	*print_err(char *str)
{
	write(STDERR_FILENO, "Error: ", 7);
	if (str && *str)
		write(STDERR_FILENO, str, ft_strlen(str));
	return (NULL);
}

