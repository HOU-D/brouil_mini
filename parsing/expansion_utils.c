/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 05:54:38 by mberrouk          #+#    #+#             */
/*   Updated: 2023/07/31 07:45:45 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

int    sp_stay(char ch)
{
    char    *spchar;

    spchar = " \t\n\f\v\r\b\\`~%^&$()-=+[]{};:/.>,<";
    if (ft_strchr(spchar, ch))
        return (1);
    return (0);
}

int	check_sp_char(char c)
{
	char	*sp_char;

	sp_char = " \t\n\f\v\r\b\"'\\`~!@#$%^&*()-=+[]{};:/?.>,<0123456789";
    if (ft_strchr(sp_char, c))
        return (1);
	return (0);
}

int    sp_remove(char ch)
{
    char    *spchar;

    spchar = " \t\n\f\v\r\b\\`!@#*-=+[]{};:/?.>,<0123456789";
    if (ft_strchr(spchar, ch))
        return (1);
    return (0);
}

int    sp_at_end(char ch)
{
    char    *spchar;

    spchar = " \t\n\f\v\r\b\"\'\\`~!@#$%^&*()-=+[]{};:/?.>,<";
    if (ft_strchr(spchar, ch))
        return (1);
    return (0);
}

char    *get_var(char *var, char **env)
{
    int     j;
    int     len;
    char    *value;

    j = 0;
	len = ft_strlen(var);
	value = NULL;
    while (env[j])
	{
	   	if (!_strncmp(var, env[j], len))
	    	value = ft_strdup(&env[j][len + 1]);
	    j++;
    }
    return (value);
}

int handl_spchar_cases(char *arg, char **value)
{
    int len;

    len = 0;
            
    if (sp_remove(arg[len]))
		len++;
    else
	{
		len = len_to_spchar(arg);
		*value = ft_strjoin(*value, ft_substr(arg, 0, len));
    }
	return (len);
}

int	_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		if (!s1[i] || !s2[i])
			break ;
		i++;
	}
	if(s2[i] == '=')
		return (0);
	return (1);
}

