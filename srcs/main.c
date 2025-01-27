/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:58:55 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/27 01:01:38 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../includes/pipex.h"
#include "../libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd_infile;
	int		fd_outfile;
	int		pipes[2];
	pid_t	child_first;
	pid_t	child_second;
	char	**cmd_1;
	char	**cmd_2;

	if (argc != 5)
		return (1);
	cmd_1 = ft_split(argv[2], ' ');
	cmd_2 = ft_split(argv[3], ' ');
	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile < 0)
		return (2);
	fd_outfile = open(argv[4], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd_outfile < 0)
	{
		close(fd_infile);
		return (3);
	}
	if (pipe(pipes) == -1)
	{
		close(fd_infile);
		close(fd_outfile);
		return (4);
	}
	child_first = fork();
	if (child_first == -1)
		return (close_all_with_error(5, pipes, fd_infile, fd_outfile));
	if (child_first == 0)
	{
		if (dup2(fd_infile, STDIN_FILENO) == -1)
			return (close_all_with_error(6, pipes, fd_infile, fd_outfile));
		if (dup2(pipes[1], STDOUT_FILENO) == -1)
			return (close_all_with_error(7, pipes, fd_infile, fd_outfile));
		close_all(pipes, fd_infile, fd_outfile);
		if (execve(get_cmd_path(envp, cmd_1[0], 0), cmd_1, NULL) == -1)
			return (close_all_with_error(8, pipes, fd_infile, fd_outfile));
	}
	else
	{
		child_second = fork();
		if (child_second == -1)
			return (close_all_with_error(9, pipes, fd_infile, fd_outfile));
		else if (child_second == 0)
		{
			if (dup2(pipes[0], STDIN_FILENO) == -1)
				return (close_all_with_error(10, pipes, fd_infile, fd_outfile));
			if (dup2(fd_outfile, STDOUT_FILENO) == -1)
				return (close_all_with_error(11, pipes, fd_infile, fd_outfile));
			close_all(pipes, fd_infile, fd_outfile);
			if (execve(get_cmd_path(envp, cmd_2[0], 0), cmd_2, NULL) == -1)
				return (close_all_with_error(12, pipes, fd_infile, fd_outfile));
		}
		else
		{
			if (waitpid(child_first, NULL, 0) == -1)
				return (close_all_with_error(13, pipes, fd_infile, fd_outfile));
			if (waitpid(child_second, NULL, 0) == -1)
				return (close_all_with_error(14, pipes, fd_infile, fd_outfile));
			close_all(pipes, fd_infile, fd_outfile);
		}
	}
	ft_tabfree(cmd_1, ft_tablen((const char **)cmd_1));
	ft_tabfree(cmd_2, ft_tablen((const char **)cmd_2));
}
