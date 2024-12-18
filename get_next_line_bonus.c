/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcili <bcili@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:03:32 by bcili             #+#    #+#             */
/*   Updated: 2024/12/18 15:24:03 by bcili            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*left_line_b(char *str)
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
	newstr = malloc(ft_strlen_b(str) - i + 1);
	j = 0;
	while (str[i])
		newstr[j++] = str[i++];
	newstr[j] = '\0';
	free (str);
	return (newstr);
}

static char	*current_line_b(char *str)
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

static char	*read_line_b(int fd, char *str)
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
	while (!ft_strchr_b(str, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, rdingstr, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(rdingstr), free(str), NULL);
		rdingstr[bytes_read] = '\0';
		str = ft_strjoin_b(str, rdingstr);
	}
	free(rdingstr);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[10240];
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = read_line_b(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	ret = current_line_b(str[fd]);
	str[fd] = left_line_b(str[fd]);
	return (ret);
}
