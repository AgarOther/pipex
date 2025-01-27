/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:04:25 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/27 17:03:33 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>

char	*get_cmd_path(char **envp, char *cmd);
void	close_all(int pipes[2], int fd_infile, int fd_outfile);
int		close_all_with_error(int error_code, int pipes[2], int fd_infile, int fd_outfile);

#endif
