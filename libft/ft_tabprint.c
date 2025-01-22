/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:42:14 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/06 11:27:41 by scraeyme         ###   ########.fr       */
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
