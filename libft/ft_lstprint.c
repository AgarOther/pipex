/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:06:46 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/06 10:43:54 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_map *map, int endl)
{
	while (map)
	{
		if (endl)
			ft_putendl_fd(map->str, 1);
		else
			ft_putstr_fd(map->str, 1);
		map = map->next;
	}
}
