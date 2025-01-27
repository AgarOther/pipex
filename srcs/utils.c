/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:59:52 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/27 17:18:56 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

char	*get_cmd_path(char **envp, char *cmd)
{
	char	*envp_path;
	char	*program_path;
	char	**paths;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	envp_path = &envp[i][5];
	paths = ft_split(envp_path, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin_free(paths[i], "/");
		program_path = ft_strjoin(paths[i], cmd);
		if (!access(program_path, X_OK))
		{
			ft_tabfree(paths, ft_tablen((const char **)paths));
			return (program_path);
		}
		free(program_path);
		i++;
	}
	ft_tabfree(paths, ft_tablen((const char **)paths));
	return (NULL);
}

void	close_all(int pipes[2], int fd_infile, int fd_outfile)
{
	close(pipes[0]);
	close(pipes[1]);
	close(fd_infile);
	close(fd_outfile);
}

int	close_all_with_error(int error_code, int pipes[2], int fd_infile, int fd_outfile)
{
	close_all(pipes, fd_infile, fd_outfile);
	ft_putstr_fd("PIPEX encountered an error. Code: ", 2);
	ft_putnbr_fd(error_code, 2);
	ft_putchar_fd('\n', 2);
	return (error_code);
}
