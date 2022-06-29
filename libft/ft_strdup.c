#include "libft.h"

char *ft_strdup(const char *s)
{
	size_t i;
	char *str;
	char *new;

    i = 0;
	str = (char *)s;
	new = (char *)malloc((sizeof(char) * ft_strlen(str)) + 1);
	if (!new)
		return NULL;
	while (s[i] != '\0')
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}