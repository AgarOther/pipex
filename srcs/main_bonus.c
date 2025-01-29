/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:42:13 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/29 14:47:49 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static pid_t	execute_second_cmd(char **av, char **envp, t_data data)
{
	pid_t	child_two;
	char	**cmd;
	char	*path;

	child_two = fork();
	if (child_two < 0)
		return (0);
	cmd = ft_split(av[3 + data.here_doc], ' ');
	if (!cmd)
		return (0);
	if (child_two == 0)
	{
		if (dup2(data.pipes[0], STDIN_FILENO) < 0)
			return (0);
		if (dup2(data.fd_outfile, STDOUT_FILENO) < 0)
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
	cmd = ft_split(av[2 + data.here_doc], ' ');
	if (!cmd)
		return (0);
	if (child_one == 0)
	{
		if (dup2(data.fd_infile, STDIN_FILENO) < 0)
			return (0);
		if (dup2(data.pipes[1], STDOUT_FILENO) < 0)
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
	close_fds(data);
	if (data.here_doc)
		unlink(TMP_FILEPATH);
	return (0);
}

static void	ft_heredoc(char **av, t_data *data)
{
	char	*str;
	int		tmp_fd;

	str = NULL;
	ft_putstr_fd("> ", 1);
	tmp_fd = open(TMP_FILEPATH, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (tmp_fd < 0)
		exit(1);
	data->here_doc = 1;
	while (1)
	{
		if (str)
			ft_putstr_fd("> ", 1);
		str = get_next_line(1);
		if (ft_strlencmp(str, av[2], 1) == 0)
			break ;
		write(tmp_fd, str, ft_strlen(str));
		free(str);
	}
	free(str);
	close(tmp_fd);
	data->fd_infile = open(TMP_FILEPATH, O_RDONLY);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	data.here_doc = 0;
	if (ac < 5 || ac > 6 || ft_tabhasemptystr(av)
		|| (ac == 6 && ft_strncmp(av[1], "here_doc", 8)))
		return (0);
	if (ac == 6 && !ft_strncmp(av[1], "here_doc", 8))
		ft_heredoc(av, &data);
	else
		data.fd_infile = open(av[1], O_RDONLY);
	if (data.fd_infile < 0)
		return (0);
	data.fd_outfile = open(av[4 + data.here_doc],
			O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (data.fd_outfile < 0)
	{
		close(data.fd_infile);
		return (0);
	}
	if (pipe(data.pipes) < 0)
		return (close_fds(data));
	return (execute_cmds(av, envp, data));
}
