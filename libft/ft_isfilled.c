/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfilled.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:14:37 by scraeyme          #+#    #+#             */
/*   Updated: 2024/11/14 14:05:31 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_whitelist(char current, char *whitelist)
{
	int	i;

	if (!whitelist)
		return (1);
	i = 0;
	while (whitelist[i])
	{
		if (current == whitelist[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_isfilled(char *str, int c, char *whitelist)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != c && !is_whitelist(str[i], whitelist))
			return (0);
		i++;
	}
	return (1);
}
