/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_double_ptr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:33:09 by mberrouk          #+#    #+#             */
/*   Updated: 2023/07/28 18:28:43 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int	double_len(char **ptr)
{
	int	len;

	len = 0;
	if (!ptr || !*ptr)
		return (0);
	while (ptr[len])
		len++;
	return (len);
}


char    **join_double(char **fir, char **last)
{
    char **new;
    int len;
    int i;
    int j;
    
    len = double_len(fir) + double_len(last);
	if (!len)
		return (0x00);
    new = malloc(sizeof(char *) * (len + 1));
    if (!new)
        return (0x00);
    i = 0;
    j = 0;
    while (fir && fir[i])
    {
        new[i] = ft_strdup(fir[i]);
        if (!new[i])
        {
            return (0x00);
		}	    
		free(fir[i]);
        i++;
    }
	while (last && last[j])
	{
		new[i + j] = ft_strdup(last[j]);
        if (!new[i + j])
        {
            return (0x00);
        }
		free(last[j]);
		j++;
	}
	/**
	if (fir)
		free(fir);
	if (last)
		free(last);
	**/
	new[i + j] = NULL;
	return (new);
}

