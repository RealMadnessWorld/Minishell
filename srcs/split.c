#include "minishell.h"

static int	counter(char const *s, char c)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	if (s[i] != c)
		word++;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			while (s[i] == c && s[i] != '\0')
				i++;
			if (s[i] != '\0')
				word++;
		}
		else
			i++;
	}
	return (word);
}

static int	allocate_dst(char **dst, char const *s, char c)
{
	dst = (char **)malloc(sizeof(char *) * counter(s, c) + 1);
	if (!dst)
		return (0);
	return (1);
}

static int	allocate_dst_small(char **dst, int i, char *str, const char *s)
{
	dst[i] = (char *)malloc(s - str + 1);
	if (!dst[i])
		return (0);
	return (1);
}

int	split(char const *s, char c, char** save)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (allocate_dst(save, s, c) == 0)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			str = (char *)s;
			while (*s && *s != c)
				s++;
			if (allocate_dst_small(save, i, str, s) == 0)
				return (0);
			ft_strlcpy(save[i++], str, s - str + 1);
		}
		s++;
	}
	save[i] = 0;
	return (i);
}