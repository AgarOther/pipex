/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:59:52 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/27 01:02:20 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

char	*get_cmd_path(char **envp, char *cmd, int i)
{
	char	*envp_path;
	char	*program_path;
	char	**paths;

	while (!ft_strstartswith(envp[i], "PATH="))
		i++;
	envp_path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	paths = ft_split(envp_path, ':');
	free(envp_path);
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin_free(paths[i], "/");
		program_path = ft_strjoin(paths[i], cmd);
		if (!access(program_path, X_OK))
		{
			free(cmd);
			ft_tabfree(paths, ft_tablen((const char **)paths));
			return (program_path);
		}
		free(program_path);
	}
	free(cmd);
	ft_tabfree(paths, ft_tablen((const char **)paths));
	return (NULL);
}

void	close_all(int pipes[2], int fd_infile, int fd_outfile)
{
	// Might be the issue tbh
	close(pipes[0]);
	close(pipes[1]);
	close(fd_infile);
	close(fd_outfile);
}

int	close_all_with_error(int error_code, int pipes[2], int fd_infile, int fd_outfile)
{
	close_all(pipes, fd_infile, fd_outfile);
	return (error_code);
}
