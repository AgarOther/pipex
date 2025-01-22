/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:23:47 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/09 17:02:16 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab, int size)
{
	char	**new;
	int		i;

	new = malloc((size + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = ft_strdup(tab[i]);
		if (!new[i])
		{
			ft_tabfree(new, i);
			return (NULL);
		}
		i++;
	}
	new[i] = 0;
	return (new);
}
