/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:51:23 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/30 15:26:29 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static pid_t	execute_second_cmd(char **av, char **envp, t_data data)
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
		if (dup2(data.pipes[0], STDIN_FILENO) < 0
			|| dup2(data.fd_outfile, STDOUT_FILENO) < 0)
			return (0);
		close_all(data);
		path = get_path(cmd, envp);
		if (!path || execve(path, cmd, envp) < 0)
			return (close_all_and_tabfree(data, cmd));
	}
	close(data.pipes[0]);
	ft_tabfree(cmd, ft_tablen((const char **)cmd));
	return (child_two);
}

static pid_t	execute_first_cmd(char **av, char **envp, t_data data)
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
		if (dup2(data.fd_infile, STDIN_FILENO) < 0
			|| dup2(data.pipes[1], STDOUT_FILENO) < 0)
			return (0);
		close_all(data);
		path = get_path(cmd, envp);
		if (!path || execve(path, cmd, envp) < 0)
			return (close_all_and_tabfree(data, cmd));
	}
	close(data.pipes[1]);
	ft_tabfree(cmd, ft_tablen((const char **)cmd));
	return (child_one);
}

static int	execute_cmds(char **av, char **envp, t_data data)
{
	pid_t	child_one;
	int		status_one;
	pid_t	child_two;
	int		status_two;

	child_one = execute_first_cmd(av, envp, data);
	if (!child_one)
		return (close_all(data));
	child_two = execute_second_cmd(av, envp, data);
	if (!child_two)
		return (close_all(data));
	if (waitpid(child_one, &status_one, 0) < 0)
	{
		close_all(data);
		return (status_one);
	}
	else if (waitpid(child_two, &status_two, 0) < 0)
	{
		close_all(data);
		return (status_two);
	}
	close(data.fd_infile);
	close(data.fd_outfile);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac != 5 || ft_tabhasemptystr(av))
		return (0);
	data.fd_infile = open(av[1], O_RDONLY);
	data.fd_outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (data.fd_outfile < 0)
	{
		close(data.fd_infile);
		return (0);
	}
	if (data.fd_infile < 0 || pipe(data.pipes) < 0)
	{
		close(data.fd_infile);
		close(data.fd_outfile);
		return (0);
	}
	return (execute_cmds(av, envp, data));
}
