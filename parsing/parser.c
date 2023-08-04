/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 03:31:45 by mberrouk          #+#    #+#             */
/*   Updated: 2023/07/31 05:23:51 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/shell.h"
char	*expan_arg(char *arg, char *env[]);
char *pars_arg_expan(char *arg, char **env);
char	*handl_quots(char *arg)
{
	int		i;
	int		n_qts;
	char	quots;
	char	*narg;

	i = 0;
	n_qts = 0;
	quots = '\0';
	narg = ft_strdup("");
	while (arg[i])
	{
		if (!quots && (arg[i] == '\'' || arg[i] == '\"'))
		{	
			quots = arg[i];
			n_qts++;
		}
		else if (quots == arg[i])
		{
			quots = '\0';
			n_qts++;
		}
		else if (arg[i] && arg[i] != quots)
			narg = ft_realloc(narg, arg[i]);
		i++;
	}
	if (n_qts && n_qts % 2)
	{
		/** ! write on stderr **/
		printf("syntax error near unexpected token `%c'\n", quots);
		//free(narg);
		return (0x00);
	}
	//free(arg);
	return (narg);
}

t_lexer	*hold_args(t_lexer *ptr, t_cmd *tmp, char **env)
{
	if (ft_strchr(ptr->arg, '$'))
		ptr->arg = pars_arg_expan(ptr->arg, env);
	if (check_quots(ptr->arg))
		ptr->arg = handl_quots(ptr->arg);
	if (tmp->type != SIMPLE_CMD && (!(ptr->arg) || !*(ptr->arg)))
	{
		printf("ambiguous redirect\n");
		/** !free data && cmd **/
		return (0x00);
	}
	if (tmp->type == INPUT_RE)
		tmp->input = join_double(tmp->input, ft_split(ptr->arg, '\0'));
	else if (tmp->type == OUTPUT_RE)
		tmp->output = join_double(tmp->output, ft_split(ptr->arg, '\0'));
	else if (tmp->type == APPEND_RE)
		tmp->outapp = join_double(tmp->outapp, ft_split(ptr->arg, '\0'));
	else
		tmp->cmd = join_double(tmp->cmd, ft_split(ptr->arg, '\0'));
	return (ptr->next);
}

t_lexer	*parse_lexer_data(t_lexer *ptr, t_cmd *cmd, char **env)
{
	t_cmd	*tmp;
	t_lexer	*tmplex;
	SymTok	token;

	tmplex = ptr;
	tmp = cmd;
	token = ptr->sym;
	if (token == SIMPLE_CMD)
		return (hold_args(ptr, tmp, env));
	ptr = ptr->next;
	if (!ptr || ptr->sym != SIMPLE_CMD)
	{
		/** !write on stderr           !handle <<<  token(newline) **/
		printf("syntax error near unexpected token `%s'\n", ptr ? ptr->arg : "newline");
		/** ! free data && cmd **/
		return (NULL);
	}
	//ptr->sym = token;
    tmp->type = token;
    return (hold_args(ptr, tmp, env));
}

void	init_parse(t_cmd **cmd, char *line, char *env[])
{
	t_lexer	*data;
	t_lexer	*ptr;
	t_cmd	*tmp;

	data = NULL;
	if (!line || !line[skip_withespace(line, 0)])
		return ;
	lexical_analysis(line, &data);
	/** if (!data)
		return ; ! Check first **/
	*cmd = parser_lstnew(NULL);
	tmp = *cmd;
	ptr = data;
	while (ptr)
	{
		while (ptr && ptr->sym != PIPE)
		{
			ptr = parse_lexer_data(ptr, tmp, env);
			//if (!tmp)
			//{
				/* Error exit */
			//	return ;
			//}
		}
		if ((ptr == data) || (ptr && ptr->next && ptr->next->sym != SIMPLE_CMD))
		{
			/** !write on stderr **/
			printf("syntax error near unexpected token `%s'\n", ptr->arg);
			/** ! free data && cmd **/
			return ;
		}
		else if ((ptr && ptr->sym == PIPE && ptr->next))
		{
			parser_lstadd_back(cmd,  parser_lstnew(NULL));
			tmp = tmp->next;
			ptr = ptr->next;
		}

	}
}
