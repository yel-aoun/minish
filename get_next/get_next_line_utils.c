/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:47:46 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/22 10:27:02 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_t(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize > 0)
	{
		i = 0;
		while (i < dstsize - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen_t(src));
}

char	*ft_substr_t(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	size_sub_str;
	char	*sub_str;

	if (!s)
		return (NULL);
	s_len = ft_strlen_t(s);
	if (start >= s_len)
	{
		sub_str = (char *)malloc(1);
		sub_str[0] = '\0';
		return (sub_str);
	}
	size_sub_str = s_len - start + 1;
	if (size_sub_str > len + 1)
			size_sub_str = len + 1;
	sub_str = (char *)malloc(size_sub_str);
	if (!sub_str)
		return (NULL);
	ft_strlcpy(sub_str, s + start, size_sub_str);
	return (sub_str);
}

char	*ft_strdup_t(const char *s1)
{
	size_t	s_length;
	size_t	i;
	char	*coppy;

	s_length = ft_strlen_t(s1);
	coppy = (char *) malloc(sizeof(char) * (s_length + 1));
	if (!coppy)
		return (NULL);
	i = 0;
	while (i <= s_length)
	{
		coppy[i] = s1[i];
		i++;
	}
	return (coppy);
}

char	*ft_strjoin_t(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	len_str_join;
	char	*str_join;

	if (!s1 && s2)
		return (ft_strdup_t(s2));
	s1_len = ft_strlen_t(s1);
	s2_len = ft_strlen_t(s2);
	len_str_join = s1_len + s2_len + 1;
	str_join = malloc(len_str_join);
	if (!str_join)
		return (NULL);
	i = 0;
	ft_strlcpy(str_join, s1, ft_strlen_t(s1) + 1);
	ft_strlcpy(str_join + ft_strlen_t(s1), s2, ft_strlen_t(s2) + 1);
	str_join[len_str_join - 1] = '\0';
	free (s1);
	return (str_join);
}
