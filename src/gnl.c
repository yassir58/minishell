#include "../includes/minishell.h"


char	*advanced_get_next_line(int fd, int status)
{
    if (fd < 0)
        return (NULL);
    char buff[1];
    char line[1000000];
    line[0] = 0;
    int i = 0;
    int n;
    while ((n = read(fd, buff, 1)) && n > 0)
    {
        line[i++] = buff[0];
		line[i] = '\0';
        if (buff[0] == '\n')
		{
			if (status == 0)
				line[i - 1] = '\0';
			else
				line[i] = '\0';
            return (ft_strdup(line));
		}
    }
    if (!line[0])
        return (NULL);
    return (ft_strdup(line));
}
