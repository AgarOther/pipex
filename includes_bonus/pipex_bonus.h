/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:54:36 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/31 00:10:57 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# define TMP_FILEPATH "/tmp/pipex_tmp_fd"
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"

typedef struct s_data
{
	int		fd_infile;
	int		fd_outfile;
	int		**pipes;
	int		pipes_amount;
	int		here_doc;
	char	**av;
	char	**envp;
	pid_t	*children;
}				t_data;

// Utils
int		close_files(t_data data);
int		close_all(t_data data, int free_children);
int		close_all_and_tabfree(t_data data, char **tab);
char	*get_path(char **cmd, char **envp);

#endif
