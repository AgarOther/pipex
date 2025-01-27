/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:35:43 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/11 09:35:45 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_strs(char *str, char c)
{
	int	i;
	int	strs;
	int	is_spaced;

	i = 0;
	strs = 0;
	is_spaced = 1;
	while (str[i])
	{
		if (is_spaced && str[i] != c)
		{
			is_spaced = 0;
			strs++;
		}
		else if (!is_spaced && str[i] == c)
			is_spaced = 1;
		i++;
	}
	return (strs);
}

static int	count_char(char *str, char c)
{
	int	i;
	int	chars;

	i = 0;
	chars = 0;
	while (str[i] != c && str[i])
	{
		chars++;
		i++;
	}
	return (chars);
}

static void	free_all(char **tab, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**fill_tab(char **tab, char *str, char c, int i)
{
	int	j;
	int	is_spaced;

	j = 0;
	is_spaced = 1;
	while (str[i])
	{
		if (is_spaced && str[i] != c)
		{
			tab[j] = malloc(count_char(&str[i], c) + 1);
			if (!tab[j])
			{
				free_all(tab, j);
				return (NULL);
			}
			ft_strlcpy(tab[j], &str[i], count_char(&str[i], c) + 1);
			tab[j++][count_char(&str[i], c)] = 0;
			is_spaced = 0;
		}
		else if (!is_spaced && str[i] == c)
			is_spaced = 1;
		i++;
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_strs((char *)s, c) + 1));
	if (!tab)
		return (NULL);
	tab = fill_tab(tab, (char *)s, c, i);
	return (tab);
}
