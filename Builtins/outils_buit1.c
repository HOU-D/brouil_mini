/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_buit1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:12:09 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/03 22:25:29 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/shell.h"


int	ft_putchar(char c, int fd)
{
	write (fd, &c, 1);
	return (1);
}

int	ft_putstr(char *s, int fd)
{
	int				i;

	i = 0;
	if (!s)
	{
		write (fd, "(null)", 6);
		return (6);
	}
	else
		write (fd, s, ft_strlen(s));
	return (ft_strlen(s));
}

static	int	find(const char *f, int i, va_list ap, int fd)
{
	if (f[i + 1] == 's')
		return (ft_putstr (va_arg(ap, char *), fd));
	else
		return (ft_putchar (f[i + 1], fd));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	va_start (ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			ret += find (format, i, ap, 2);
			i++;
		}
		else
			ret += ft_putchar(format[i], 2);
		i++;
	}
	va_end (ap);
	return (ret);
}

char	*fstrdup(char *src)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!src)
		return (NULL);
	while (src[j])
		j++;
	str = malloc(sizeof(char) * (j + 1));
	if (!str)
		return (0);
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void    free_env(t_env  *current)
{
    free(current->key);
    free(current->val);
    free(current);
}