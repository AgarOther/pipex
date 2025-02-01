/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:51:23 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/01 11:43:43 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	get_error_code(int status)
{
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status));
	return (0);
}

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
			return (close_all_and_tabfree(data, cmd));
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
			return (close_all_and_tabfree(data, cmd));
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
	pid_t	child_two;
	int		errno;

	child_one = execute_first_cmd(av, envp, data);
	if (!child_one)
		return (close_all(data));
	child_two = execute_second_cmd(av, envp, data);
	if (!child_two)
		return (close_all(data));
	if (waitpid(child_one, &errno, 0) < 0 || waitpid(child_two, &errno, 0) < 0)
	{
		close_all(data);
		perror("An error occured in one of the child processes. Aborting.\n");
		exit(get_error_code(errno));
	}
	close_files(data);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac != 5 || ft_tabhasemptystr(av))
		return (1);
	data.fd_infile = open(av[1], O_RDONLY);
	data.fd_outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (pipe(data.pipes) < 0)
		return (close_files(data));
	return (execute_cmds(av, envp, data));
}
