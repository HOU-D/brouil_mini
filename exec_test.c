/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:42:34 by mberrouk          #+#    #+#             */
/*   Updated: 2023/07/31 07:05:12 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "lexer/parsing.h"
#include <sys/fcntl.h>
#include <unistd.h>
#include "include/shell.h"

void	not_found(char *parm)
{
	write(STDERR_FILENO, "pipex: ", 8);
	if (parm && *parm)
		write(STDERR_FILENO, parm, ft_strlen(parm));
	write(STDERR_FILENO, ": command not found\n", 21);
	//exit(127);
}

void	puterr(char *str)
{
	if (str)
	{
		write(STDERR_FILENO, str, ft_strlen(str));
		//exit(1);
	}
	else
	{
		perror("Error");
		//exit(errno);
	}
}

char	*ft_access(char **paths, char *cmd)
{
	char	*new;
	char	*v_cmd;
	int		i;

	i = 0;
	if (!cmd || !*cmd)
		return (NULL);
	new = malloc(sizeof(char) * ft_strlen(cmd) + 2);
	if (!new)
		return (NULL);
	new[0] = '/';
	ft_strlcpy(&new[1], cmd, ft_strlen(cmd) + 1);
	while (paths && paths[i])
	{
		v_cmd = ft_strjoin(paths[i], new);
		if (!access(v_cmd, X_OK))
		{
			free(new);
			return (v_cmd);
		}
		free(v_cmd);
		i++;
	}
	free(new);
	return (NULL);
}

char	**find_path(char **env)
{
	char	**paths;
	int		i;
	int		j;
	char	*path;

	i = 0;
	path = "PATH=";
	while (env[i])
	{
		j = 0;
		while (path[j] == env[i][j])
			j++;
		if (!path[j])
		{
			paths = ft_split(&env[i][j], ':');
			return (paths);
		}		
		i++;
	}
	return (NULL);
}

void	execute_command(int ifd, int ofd, t_cmd *data, char **cmds, char **path, char **env)
{
	pid_t	pid;
	char	*cmd;
	(void)data;

	pid = fork();
	if (pid == 0)
	{
		
		if (ifd > 0)
			if (dup2(ifd, STDIN_FILENO) == -1 )
				puterr("1 :Error dup2\n");
		if (ifd == -1)
			return ;
		if (ofd > 1)
			if (dup2(ofd, STDOUT_FILENO) == -1)
				puterr("2 :Error dup2\n");
		if (ofd == -1)
		{
			close(ifd);
			return ;
		}
		if (ofd > 1)
			close(ofd);
		if (ifd > 0)
			close(ifd);
		if (cmds && cmds[0] && cmds[0][0] == '/')
			cmd = cmds[0];
		else
			cmd = ft_access(path, cmds[0]);
		if (!cmd)
		{
			not_found(cmds[0]);
			return ;
		}
		if (execve(cmd, cmds, env) == -1)
		{
			puterr(NULL);
		}
	}
	else if (pid < 0)
		puterr(NULL);
}

void	cmds(t_cmd *data, int fdi, char **path, char **env)
{
	int	pip_fds[2];
	int	i;
	int fdo = 1;
	// int status;
	int	fdapp;
	
	pip_fds[1] = 1; 
	while (data)
	{
		/**
		if (data->next)
			pipe(pip_fds);
		**/
		if (!data->cmd)
			return ;
		if (data->input)
		{
			i = 0;
			while (data->input[i])
			{
				fdi = open(data->input[i], O_RDONLY);
				if (fdi == -1)
					perror(data->input[i]);
				if (data->input[i + 1])
					close(fdi);
				i++;
			}
		}
		if (data->output)
		{
			printf("\n out on : ==> \n");
			i = 0;
			while (data->output[i])
			{
				fdo = open(data->output[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fdo == -1)
					perror(data->output[i]);
				if (data->output[i + 1])
					close(fdo);
				i++;
			}
		}
		if (data->outapp)
		{
			i = 0;
			while (data->outapp[i])
			{
				fdapp = open(data->outapp[i], O_APPEND | O_CREAT | O_RDWR, 0644);
				if (fdapp == -1)
					perror(data->outapp[i]);
				if (data->outapp[i + 1])
					close(fdapp);
				i++;
			}

		}
		if (data->next)
		{	
			if (pipe(pip_fds) == -1)
				puterr(NULL);
		}
		else 		
		{
			if (data->type == APPEND_RE)
				fdo = fdapp;
		/**	if (pip_fds[1] != 1)
				close(pip_fds[1]);**/
			pip_fds[1] = fdo;
		}	
		if (data->type == APPEND_RE)
			fdo = fdapp;
		if (fdo != 1)
		{
			/** handl ls > 1 | cat **/
		//	close(fd[1]);
			pip_fds[1] = fdo;
		}
		execute_command(fdi, pip_fds[1], data, data->cmd, path, env);
		if (fdi != 0)
			close(fdi);
		if (pip_fds[1] != 1)
			close(pip_fds[1]);
		fdi = pip_fds[0];
		data = data->next;
	}

}

void	exec_cmds(t_cmd *data, int status, char **env)
{
	// int	fdi;

	/**
	if (!data->lmt)
		fdi = data->in_file;
	else
	{
		fdi = here_doc(*data);
		data->in_file = fdi;
	}
	**/
	if (!data)
		return ;
	//data->env = env;
	char **path = find_path(env);
	if (!path)
	{
		printf("\n Error : path\n");
	}
	cmds(data, 0, path, env);
	while (wait(&status) > 0)
		;
	status = WEXITSTATUS(status);
/**	if (data->cmd)
		free_cmds(data->cmd);
	handle_error(data->path);
**/

}
