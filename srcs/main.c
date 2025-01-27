/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:51:23 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/27 23:43:23 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_path(char **cmd, char **envp, int i, int j)
{
	char	*tmp;
	char	*path;
	char	**path_finding;

	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (ft_strlen(envp[i]) < 6)
		return (NULL);
	tmp = &envp[i][5];
	path_finding = ft_split(tmp, ':');
	if (!path_finding)
		return (NULL);
	while (path_finding[++j])
	{
		path = ft_strjoin(path_finding[j], "/");
		path = ft_strjoin_free(path, cmd[0]);
		if (!access(path, X_OK))
		{
			ft_tabfree(path_finding, ft_tablen((const char **)path_finding));
			return (path);
		}
		free(path);
	}
	ft_tabfree(path_finding, ft_tablen((const char **)path_finding));
	return (NULL);
}

static int	execute_second_cmd(char **av, char **envp, t_data data)
{
	pid_t	child_two;
	char	**cmd;
	char	*path;

	child_two = fork();
	if (child_two < 0)
		return (0);
	cmd = ft_split(av[3], ' ');
	if (!cmd)
		return (0);
	if (child_two == 0)
	{
		if (dup2(data.pipes[0], STDIN_FILENO) < 0)
			return (0);
		if (dup2(data.fd_outfile, STDOUT_FILENO) < 0)
			return (0);
		close_all(data);
		path = get_path(cmd, envp, 0, -1);
		if (execve(path, cmd, envp) < 0)
			return (close_all(data));
	}
	close(data.pipes[1]);
	waitpid(child_two, NULL, 0);
	ft_tabfree(cmd, ft_tablen((const char **)cmd));
	return (1);
}

static int	execute_first_cmd(char **av, char **envp, t_data data)
{
	pid_t	child_one;
	char	**cmd;
	char	*path;

	child_one = fork();
	if (child_one < 0)
		return (0);
	cmd = ft_split(av[2], ' ');
	if (!cmd)
		return (0);
	if (child_one == 0)
	{
		if (dup2(data.fd_infile, STDIN_FILENO) < 0)
			return (0);
		if (dup2(data.pipes[1], STDOUT_FILENO) < 0)
			return (0);
		close_all(data);
		path = get_path(cmd, envp, 0, -1);
		if (execve(path, cmd, envp) < 0)
			return (close_all(data));
	}
	close(data.pipes[1]);
	waitpid(child_one, NULL, 0);
	ft_tabfree(cmd, ft_tablen((const char **)cmd));
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac != 5)
		return (0);
	data.fd_infile = open(av[1], O_RDONLY);
	if (data.fd_infile < 0)
		return (0);
	data.fd_outfile = open(av[4], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (data.fd_outfile < 0)
	{
		close(data.fd_infile);
		return (0);
	}
	if (pipe(data.pipes) < 0)
	{
		close(data.fd_infile);
		close(data.fd_outfile);
		return (0);
	}
	if (!execute_first_cmd(av, envp, data))
		close_all(data);
	execute_second_cmd(av, envp, data);
	close_all(data);
}
