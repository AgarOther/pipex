/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 23:42:13 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/01 11:39:26 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

static int	execute_cmds(int fd_in, int fd_out, t_data *data)
{
	int	i;
	int	errno;

	i = 0;
	while (1)
	{
		data->children[i] = fork();
		if (data->children[i] < 0)
			return (close_all(*data, 1));
		else if (data->children[i] == 0)
			execute_childcmd(fd_in, fd_out, i, *data);
		if (!manage_fds(&fd_in, &fd_out, i, *data))
			break ;
		i++;
	}
	i = -1;
	errno = 0;
	close_all(*data, 0);
	while (++i <= data->pipes_amount)
		waitpid(data->children[i], &errno, 0);
	if (data->exit_code)
		return (data->exit_code);
	return (get_error_code(errno));
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

static void	get_pipes(int ac, t_data *data)
{
	int	i;

	if (data->fd_outfile < 0)
		data->exit_code = 1;
	data->pipes = malloc((ac - 4 - data->here_doc) * sizeof(int *));
	if (!data->pipes)
	{
		close_files(*data);
		exit(-1);
	}
	i = 0;
	while (i < ac - 4 - data->here_doc)
	{
		data->pipes[i] = malloc(2 * sizeof(int));
		if (!data->pipes[i] || pipe(data->pipes[i]) < 0)
		{
			if (data->pipes[i])
				free(data->pipes[i]);
			perror("Error opening pipes. Aborting");
			close_all(*data, 0);
			exit(-1);
		}
		i++;
		data->pipes_amount = i;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		status;

	data.here_doc = 0;
	data.exit_code = 0;
	if (ac < 5 || ft_tabhasemptystr(av))
		return (0);
	if (!ft_strncmp(av[1], "here_doc", 8))
		ft_heredoc(av, &data);
	else
		data.fd_infile = open(av[1], O_RDONLY);
	data.fd_outfile = open(av[ac - 1],
			O_CREAT | O_WRONLY | O_TRUNC, 0777);
	get_pipes(ac, &data);
	if (!data.pipes)
		return (close_files(data));
	data.children = malloc((data.pipes_amount + 1) * sizeof(pid_t));
	if (!data.children)
		return (close_all(data, 0));
	data.av = av;
	data.envp = envp;
	status = execute_cmds(data.fd_infile, data.pipes[0][1], &data);
	if (data.children)
		free(data.children);
	return (status);
}
