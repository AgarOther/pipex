/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:03:07 by scraeyme          #+#    #+#             */
/*   Updated: 2024/10/30 10:03:07 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}

int	has_newline(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = ft_calloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1, 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	free(s1);
	return (str);
}

char	*get_until_newline(char *buffer, int fd)
{
	char	*line;
	int		i;

	i = 1;
	line = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!line || !buffer)
		return (NULL);
	while (!has_newline(buffer) && i > 0)
	{
		i = read(fd, line, BUFFER_SIZE);
		if (i == -1)
			return (free_all(buffer, line));
		line[i] = 0;
		buffer = ft_strjoin_gnl(buffer, line);
		if (!buffer)
			return (NULL);
	}
	free(line);
	if (i == 0 && !buffer[0])
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*transform_buffer(char *buffer)
{
	char		*str;
	size_t		i;
	size_t		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	str = ft_calloc(i + 1 + (buffer[i] == '\n'), 1);
	if (!str)
		return (NULL);
	j = 0;
	while (j < i)
	{
		str[j] = buffer[j];
		j++;
	}
	if (buffer[j] == '\n')
		str[j++] = '\n';
	return (str);
}
