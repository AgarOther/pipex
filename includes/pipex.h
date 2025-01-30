/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:54:36 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/30 16:37:34 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"

typedef struct s_data
{
	int		fd_infile;
	int		fd_outfile;
	int		pipes[2];
}				t_data;

// Utils
int		close_files(t_data data);
int		close_all(t_data data);
int		close_all_and_tabfree(t_data data, char **tab);
char	*get_path(char **cmd, char **envp);

#endif
