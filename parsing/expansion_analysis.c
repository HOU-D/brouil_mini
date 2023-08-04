/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 05:54:30 by mberrouk          #+#    #+#             */
/*   Updated: 2023/07/31 08:19:35 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"

char *expan_in_dquots(char *arg, char **env);
char *pars_arg_expan(char *arg, char **env);
int	sp_to_skip(char c);
int	_strncmp(char *s1, char *s2, int n);
int	check_sp_char(char c);
int    sp_at_end(char ch);
int    sp_remove(char ch);

char	*expan_arg(char *arg, char *env[])
{
    int     i;
	int		len;
    char    *value;

    i = 0;
    value = ft_strdup("");
    while (arg[i])
    {
        while (arg[i] != '$' && arg[i])
		{
			value = ft_realloc(value, arg[i]); 
			i++;
		}
        while (arg[i] == '$')
            i++;
        if (arg[i] && check_sp_char(arg[i]))
        {
			i += handl_spchar_cases(&arg[i], &value);
			continue;
        }
		len = len_to_spchar(&arg[i]);
		value = ft_strjoin(value, get_var(ft_substr(&arg[i], 0, len), env));
		i += len;
	}
    return (value);
}

char *continue_pars(char **env, char *arg, int *index, char sep)
{
	int		ndolr;
    int     i;
	char	*value =NULL;

    i = 0;
	ndolr = skip_char(arg, '$');
    i+= ndolr;
	while (arg[i])
    {
        i++;
        if ((arg[i] == sep || !arg[i]))
        {
        	if (sep == '\"')
        		value = expan_in_dquots(ft_substr(arg, 0, i + 1), env);
        	else if (sep == '\'')
            	value = ft_substr(arg, 0, i + 1);
        	else if (sep == '$' && ndolr % 2 != 0)
            {
                value = expan_arg(ft_substr(arg, 0, i), env);
            }
            else
                value = ft_substr(arg, 0, i);
            if ((sep == '\'' || sep == '\"') && arg[i])
					i++;
                break;
        }
    }
    *index += i;
	return (value);
}

char *pars_arg_expan(char *arg, char **env)
{
    int i;
    int s;
    char sep;
    char *value;
    
    i = 0;
    value = NULL;
    if (ft_strlen(arg) == 1)
        return (ft_strdup("$"));
    while (arg[i])
    {
        if (arg[i] == '\"' || arg[i] == '$' || arg[i] == '\'')
        {
            sep = arg[i];
            s = i;
			value = ft_strjoin(value, continue_pars(env, &arg[i], &i, sep));
        }
        else
            value = ft_realloc(value, arg[i++]);
    }
    return (value);
}

