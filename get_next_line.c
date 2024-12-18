/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcili <bcili@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:23:12 by bcili             #+#    #+#             */
/*   Updated: 2024/12/18 14:55:10 by bcili            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*left_line(char *str)
{
	char	*newstr;
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
		return (free(str), NULL);
	if (str[i] == '\n')
		i++;
	newstr = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!newstr)
		return (free(str), NULL);
	j = 0;
	while (str[i])
		newstr[j++] = str[i++];
	newstr[j] = '\0';
	free (str);
	return (newstr);
}

static char	*current_line(char *str)
{
	size_t	i;
	char	*s;

	i = 0;
	if (!*str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return (s);
}

static char	*read_line(int fd, char *str)
{
	ssize_t	bytes_read;
	char	*rdingstr;

	if (!str)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	bytes_read = 1;
	rdingstr = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!rdingstr)
		return (free(str), NULL);
	while (!ft_strchr(str, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, rdingstr, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(rdingstr), free(str), NULL);
		rdingstr[bytes_read] = '\0';
		str = ft_strjoin(str, rdingstr);
	}
	free(rdingstr);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_line(fd, str);
	if (!str)
		return (NULL);
	ret = current_line(str);
	str = left_line(str);
	return (ret);
}
