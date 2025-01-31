/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:42:13 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/31 12:15:19 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static void	execute_childcmd(int fd_in, int fd_out, int i, t_data data)
{
	char	**cmd;
	char	*path;

	if (dup2(fd_in, STDIN_FILENO) < 0 || dup2(fd_out, STDOUT_FILENO) < 0)
	{
		perror("Error: Dup2 failed on command. ");
		close_all(data, 1);
		exit(-1);
	}
	close_all(data, 1);
	cmd = ft_split(data.av[i + 2 + data.here_doc], ' ');
	if (!cmd)
		exit(close_all(data, 1));
	path = get_path(cmd, data.envp);
	if (execve(path, cmd, data.envp) < 0)
	{
		close_all_and_tabfree(data, cmd);
		free(path);
		perror("Error: A command didn't get executed: ");
		exit(-1);
	}
}

static int	execute_cmds(int fd_in, int fd_out, t_data data)
{
	int	i;
	int	errno;

	i = 0;
	while (1)
	{
		data.children[i] = fork();
		if (data.children[i] < 0)
			return (close_all(data, 1));
		else if (data.children[i] == 0)
			execute_childcmd(fd_in, fd_out, i, data);
		if (fd_out != data.fd_outfile && fd_out >= 0)
			close(fd_out);
		if (fd_out != data.fd_infile && fd_in >= 0)
			close(fd_in);
		if (i == data.pipes_amount)
			break ;
		fd_in = data.pipes[i][0];
		if (i < data.pipes_amount - 1)
			fd_out = data.pipes[i + 1][1];
		else
			fd_out = data.fd_outfile;
		i++;
	}
	i = -1;
	errno = 0;
	close_all(data, 0);
	while (++i <= data.pipes_amount)
		waitpid(data.children[i], &errno, 0);
	return (errno);
}

static void	ft_heredoc(char **av, t_data *data)
{
	char	*str;
	int		tmp_fd;

	str = NULL;
	ft_putstr_fd("> ", 1);
	tmp_fd = open(TMP_FILEPATH, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (tmp_fd < 0)
		exit(-1);
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

static int	**get_pipes(int ac, t_data *data)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = malloc((ac - 4 - data->here_doc) * sizeof(int *));
	if (!pipes)
	{
		close_files(*data);
		return (NULL);
	}
	while (i < ac - 4 - data->here_doc)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i] || pipe(pipes[i]) < 0)
		{
			perror("Error opening pipes. Aborting.\n");
			close_all(*data, 0);
			exit(-1);
		}
		i++;
		data->pipes_amount = i;
	}
	return (pipes);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		status;

	data.here_doc = 0;
	if (ac < 5 || ft_tabhasemptystr(av))
		return (0);
	if (!ft_strncmp(av[1], "here_doc", 8))
		ft_heredoc(av, &data);
	else
		data.fd_infile = open(av[1], O_RDONLY);
	data.fd_outfile = open(av[ac - 1],
			O_CREAT | O_WRONLY | O_TRUNC, 0777);
	data.pipes = get_pipes(ac, &data);
	if (!data.pipes)
		return (close_files(data));
	data.children = malloc((data.pipes_amount + 1) * sizeof(pid_t));
	if (!data.children)
		return (close_all(data, 0));
	data.av = av;
	data.envp = envp;
	status = execute_cmds(data.fd_infile, data.pipes[0][1], data);
	free(data.children);
	return (status);
}
