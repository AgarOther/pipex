/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:10:44 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/01 11:26:38 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

int	get_error_code(int status)
{
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status));
	return (0);
}

int	close_files(t_data data)
{
	if (data.fd_infile >= 0)
		close(data.fd_infile);
	if (data.fd_outfile >= 0)
		close(data.fd_outfile);
	return (1);
}

int	close_pipes(t_data data, int needs_free)
{
	int	i;

	i = 0;
	while (i < data.pipes_amount)
	{
		close(data.pipes[i][0]);
		close(data.pipes[i][1]);
		if (needs_free)
			free(data.pipes[i]);
		i++;
	}
	return (1);
}

int	close_all(t_data data, int free_children)
{
	close_files(data);
	close_pipes(data, 1);
	if (data.pipes)
	{
		free(data.pipes);
		data.pipes = NULL;
	}
	if (free_children && data.children)
	{
		free(data.children);
		data.children = NULL;
	}
	return (1);
}

void	close_all_and_tabfree(t_data data, char **tab)
{
	close_all(data, 1);
	if (tab)
		ft_tabfree(tab, ft_tablen((const char **)tab));
}
