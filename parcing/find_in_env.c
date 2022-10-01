#include "../includes/shell.h"

int	ft_tstrncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i]
		&& s1[i] && s2[i] && i < n - 1)
		i++;
	if (n > 0)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

char	*ft_tstrjoin(char *s1, char *s2)
{
	int		lens1;
	char	*str;
	int		i;

	i = 0;
	if (!s2)
		return (s1);
	if (!s1)
		return (s2);
	str = malloc((ft_tstrlen(s1) + ft_tstrlen(s2) +1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = ((char *)s1)[i];
		i++;
	}
	lens1 = 0;
	while (s2[lens1])
	{
		str[i] = ((char *)s2)[lens1];
		i++;
		lens1++;
	}
	str[i] = '\0';
	return (str);
}

static int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_tsubstr(char *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			i;
	unsigned int	size_sub_str;

	i = 0;
	if (!s)
		return (0);
	if (start >= (unsigned int)ft_tstrlen(s))
	{
		str = malloc(1);
		str[0] = '\0';
		return (str);
	}
	size_sub_str = min(ft_tstrlen(s) - start, len);
	str = malloc((size_sub_str + 1));
	if (str == 0)
		return (NULL);
	while (i < size_sub_str)
	{
		str[i] = s[i + start];
		i++; 
	}
	str[i] = '\0';
	return (str);
}

char	*ft_value_of_env(char *str)
{
	char **splt;

	splt = ft_split(str, '=');
	return (splt[1]);
}

char    *ft_find_in_path(char **new, char *find)
{
    int		i;
	int		k;
	char	**splt;

	k = 0;
	i = 0;
	while (new[i])
	{
		splt = ft_split(new[i], '=');
		k = ft_is_longer(splt[0], find);
		if (k > 0)
		{
			if (ft_strncmp(splt[0], find, k) == 0)
			{
				free (splt);
				return (ft_value_of_env(new[i]));
			}
			i++;
		}
		else
			i++;
		free (splt);
	}
	return ("");
}

// int main(int argc, char **argv, char **env)
// {
//     (void) argc;
//     printf("%s\n", ft_find_in_path(env, argv[1]));
// }