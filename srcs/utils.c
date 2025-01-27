/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:00:45 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/27 23:25:20 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	close_all(t_data data)
{
	close(data.fd_infile);
	close(data.fd_outfile);
	close(data.pipes[0]);
	close(data.pipes[1]);
	return (1);
}
