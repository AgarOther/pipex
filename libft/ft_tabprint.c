/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:42:14 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/31 00:59:29 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabprint(char **tab, int endl)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (endl)
			ft_putendl_fd(tab[i], 1);
		else
			ft_putstr_fd(tab[i], 1);
		i++;
	}
}
