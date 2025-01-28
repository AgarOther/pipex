/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabhasemptystr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:44:09 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/28 11:45:32 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tabhasemptystr(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!tab[i][0])
			return (1);
		i++;
	}
	return (0);
}
