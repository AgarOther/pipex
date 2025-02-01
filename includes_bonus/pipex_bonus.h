/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 22:54:36 by scraeyme          #+#    #+#             */
/*   Updated: 2025/02/01 11:26:50 by scraeyme         ###   ########.fr       */
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
	int		exit_code;
}				t_data;

// Utils
int		get_error_code(int status);
int		close_files(t_data data);
int		close_all(t_data data, int free_children);
void	close_all_and_tabfree(t_data data, char **tab);
int		close_pipes(t_data data, int needs_free);

// Cmds helper
char	*get_path(char **cmd, char **envp);
int		manage_fds(int *fd_in, int *fd_out, int i, t_data data);
void	execute_childcmd(int fd_in, int fd_out, int i, t_data data);

#endif
