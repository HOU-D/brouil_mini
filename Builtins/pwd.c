/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoakoumi <hoakoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 06:03:00 by hoakoumi          #+#    #+#             */
/*   Updated: 2023/08/01 14:01:57 by hoakoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../include/minishell.h"


void	pwd(void)
{
	char	puf[100000];

	if (getcwd(puf, sizeof(puf)) == NULL)
	{
		perror("pwd");
		t_info.exit_status = 1;
	}
	else
	{
		printf("%s\n", puf);
		t_info.exit_status = 0;
	}
}
