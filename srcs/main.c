/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:58:55 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/22 16:22:18 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <sys/types.h>
#include "../includes/pipex.h"
#include "../libft/libft.h"

int	main(int ac, char **av)
{
	pid_t child;
	int	pipes[2];
	int	status;

	(void) ac;
	if (access(av[1], R_OK) < 0)
		ft_printf("jppppppp\n");
	pipe(pipes);
	child = fork();
	waitpid(child, &status, WIFEXITED(status));
	ft_printf("FD[0]: %d | FD[1]: %d\n", pipes[0], pipes[1]);
	return (0);
}
