/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:58:55 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/24 15:34:03 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include "../includes/pipex.h"
#include "../libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd_infile;
	int		fd_outfile;

	if (argc != 5)
		return (1);
	fd_infile = open(argv[1], O_RDONLY);
	fd_outfile = open(argv[4], O_CREAT | O_WRONLY);
	if (fd_infile < 0 || fd_outfile < 0)
		return (2);
	close(fd_infile);
	close(fd_outfile);
	parse_and_execute(argv, envp);
}
