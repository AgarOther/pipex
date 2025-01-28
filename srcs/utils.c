/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:00:45 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/28 11:41:55 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
	ft_tabfree(path_finding, ft_tablen((const char **)path_finding));
	return (path);
}

int	close_all(t_data data)
{
	close(data.fd_infile);
	close(data.fd_outfile);
	close(data.pipes[0]);
	close(data.pipes[1]);
	return (0);
}

int	close_all_and_tabfree(t_data data, char **tab)
{
	close(data.fd_infile);
	close(data.fd_outfile);
	close(data.pipes[0]);
	close(data.pipes[1]);
	ft_tabfree(tab, ft_tablen((const char **)tab));
	exit(0);
}
