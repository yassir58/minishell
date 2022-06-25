#include <stdio.h>


int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * @brief This function will compare two strings regardless if one of the strings is
 * capitale letters
 * @param s1 The command the we want to get its type
 * @param s2 One of the builting commands
 * @return int 
 */

int	advanced_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (s1[i] && s2[i])
	{
		if ((s1[i] == s2[i] || s1[i] == s2[i] + 32 || s2[i] == s1[i] + 32))
			i++;
		else
			return (1);
	}
	return (0);
}