/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stroccur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:28:45 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/09 16:27:30 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_stroccur(char *str, int c)
{
	int	i;
	int	occurences;

	i = 0;
	occurences = 0;
	while (str[i])
	{
		if (str[i] == c)
			occurences++;
		i++;
	}
	return (occurences);
}
