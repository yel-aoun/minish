/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:47:08 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/22 10:29:52 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr_t(const char *s, int c)
{
	int	i;

	if (!s)
		return (-1);
	if (!c)
		return ((int)ft_strlen_t(s));
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*coppy_remaind_str(char *buffer, int index_remainder)
{
	int		i;
	char	*remainder;
	char	*temp;

	i = 0;
	remainder = buffer + index_remainder;
	temp = malloc(ft_strlen_t(remainder) + 1);
	while (remainder[i])
	{
		temp[i] = remainder[i];
		i++;
	}
	temp[i] = '\0';
	free(buffer);
	return (temp);
}

char	*get_new_stock(char *buffer, int fd)
{
	int		size_readed;
	char	*temp;

	temp = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	size_readed = 1;
	while (ft_strchr_t(buffer, '\n') == -1 && size_readed != 0)
	{
		size_readed = read(fd, temp, BUFFER_SIZE);
		if (size_readed == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[size_readed] = '\0';
		buffer = ft_strjoin_t(buffer, temp);
	}
	free(temp);
	if (ft_strlen_t(buffer) == 0 && size_readed == 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	int			index_line;
	char		*line;
	static char	*buffer = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_strchr_t(buffer, '\n') == -1)
		buffer = get_new_stock(buffer, fd);
	if (!buffer)
		return (NULL);
	index_line = ft_strchr_t(buffer, '\n');
	if (index_line == -1)
	{
		line = ft_strdup_t(buffer);
		free(buffer);
		buffer = NULL;
		return (line);
	}
	line = ft_substr_t(buffer, 0, index_line);
	buffer = coppy_remaind_str(buffer, index_line + 1);
	return (line);
}
