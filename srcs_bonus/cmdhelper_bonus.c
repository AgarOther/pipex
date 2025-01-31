/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdhelper_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:14:56 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/31 13:32:54 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static char	*iterate_paths(char **cmd, char **path_finding)
{
	char	*path;
	int		i;

	i = 0;
	while (path_finding[i])
	{
		path = ft_strjoin(path_finding[i], "/");
		path = ft_strjoin_free(path, cmd[0]);
		if (!path)
			continue ;
		if (!access(path, X_OK))
		{
			ft_tabfree(path_finding, ft_tablen((const char **)path_finding));
			return (path);
		}
		free(path);
		i++;
	}
	ft_tabfree(path_finding, ft_tablen((const char **)path_finding));
	return (NULL);
}

char	*get_path(char **cmd, char **envp)
{
	int		i;
	char	*tmp;
	char	*path;
	char	**path_finding;

	if (!access(cmd[0], X_OK))
		return (cmd[0]);
	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (ft_strlen(envp[i]) < 6)
		return (NULL);
	tmp = &envp[i][5];
	path_finding = ft_split(tmp, ':');
	if (!path_finding)
		return (NULL);
	path = iterate_paths(cmd, path_finding);
	return (path);
}

void	execute_childcmd(int fd_in, int fd_out, int i, t_data data)
{
	char	**cmd;
	char	*path;

	if (dup2(fd_in, STDIN_FILENO) < 0 || dup2(fd_out, STDOUT_FILENO) < 0)
	{
		perror("Error: Dup2 failed on command. ");
		close_all(data, 1);
		exit(-1);
	}
	close_files(data);
	close_pipes(data, 0);
	cmd = ft_split(data.av[i + 2 + data.here_doc], ' ');
	if (!cmd)
		exit(close_all(data, 1));
	path = get_path(cmd, data.envp);
	if (!path || execve(path, cmd, data.envp) < 0)
	{
		close_all_and_tabfree(data, cmd);
		if (path)
			free(path);
		perror("Error: A command didn't get executed: ");
		exit(-1);
	}
}

int	manage_fds(int *fd_in, int *fd_out, int i, t_data data)
{
	if (*fd_out != data.fd_outfile && *fd_out >= 0)
		close(*fd_out);
	if (*fd_out != data.fd_infile && *fd_in >= 0)
		close(*fd_in);
	if (i == data.pipes_amount)
		return (0);
	*fd_in = data.pipes[i][0];
	if (i < data.pipes_amount - 1)
		*fd_out = data.pipes[i + 1][1];
	else
		*fd_out = data.fd_outfile;
	return (1);
}
