/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:59:52 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/24 15:35:13 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

static void	execute_command(char **paths, char **argv)
{
	char	**cmd_args;
	char	*program_path;
	int		i;

	i = 0;
	cmd_args = ft_split(argv[2], ' ');
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		program_path = ft_strjoin(paths[i], cmd_args[0]);
		free(paths[i]);
		if (!access(program_path, X_OK))
		{
			execve(program_path, &cmd_args[0], NULL);
			ft_tabfree(cmd_args, ft_tablen((const char **)cmd_args));
			free(program_path);
			exit(1);
		}
		free(program_path);
		i++;
	}
	ft_tabfree(cmd_args, ft_tablen((const char **)cmd_args));
}

void	parse_and_execute(char **argv, char **envp)
{
	int		i;
	char	*envp_path;
	char	**paths;

	i = 0;
	while (!str_starts_with(envp[i], "PATH="))
		i++;
	envp_path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	paths = ft_split(envp_path, ':');
	free(envp_path);
	execute_command(paths, argv);
}

int	ft_error(int error_code, char *message)
{
	ft_putendl_fd(message, 1);
	return (error_code);
}
