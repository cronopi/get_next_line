#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*ptr;
	char	cast_c;

	ptr = (char *)str;
	i = 0;
	cast_c = (char) c;
	while (ptr[i] != '\0')
		i++;
	if (cast_c == '\0')
		return (&ptr[i] + 1);
	return (0);
}

void	fill_string(char *str, char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1 && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;
	char	*str_s1;
	char	*str_s2;

	str_s1 = (char *)s1;
	str_s2 = (char *)s2;
	i = 0;
	j = 0;
	if (s1)
		i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = malloc ((i + j + 1) * sizeof(char));
	if (str == 0)
		return (NULL);
	fill_string(str, str_s1, str_s2);
	return (str);
}

