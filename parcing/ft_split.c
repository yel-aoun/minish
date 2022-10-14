/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 21:18:53 by araysse           #+#    #+#             */
/*   Updated: 2022/10/14 11:53:40 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	count_word(char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	if (s[i] == c)
		i++;
	if (s[i] != c && s[i])
	{
		i++;
		j++;
	}
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
		{
			j++;
		}
		i++;
	}
	return (j);
}

int	ft_sep(const char *s, char c, int k)
{
	while (s[k] == c)
		k++;
	return (k);
}

char	**return_impty(void)
{
	char	**str;

	str = malloc(2 * sizeof(char *));
	str[0] = ft_strdup("");
	str[1] = NULL;
	return (str);
}

char	**ft_tsplit(char *s, char c)
{
	int		k;
	char	**str;

	if (!s)
		return (return_null());
	if (!(s) || !s[0] || s[0] == 127)
		return (return_impty());
	str = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!str)
		return (NULL);
	k = ft_sep(s, c, 0);
	str = hepl_split(s, c, str, k);
	return (str);
}

char	**hepl_split(char *s, char c, char **str, int k)
{
	int		i;
	int		j;

	i = -1;
	while (++i < count_word(s, c))
	{
		str[i] = malloc(sizeof(char) * (word_size(s, c, k) + 1));
		if (!str[i])
			return (NULL);
		j = 0;
		while (s[k] && s[k] != c)
			str[i][j++] = s[k++];
		str[i][j] = '\0';
		k = ft_sep(s, c, k);
	}
	str[i] = NULL;
	return (str);
}
