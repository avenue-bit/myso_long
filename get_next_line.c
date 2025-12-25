
#include "so_long.h"

static char	*ft_residual(char *puff)
{
	int		i;
	int		j;
	char	*residual;

	if (!puff)
		return (NULL);
	i = 0;
	j = 0;
	while (*(puff + i) != '\n' && *(puff + i))
		i++;
	i += (*(puff + i) == '\n');
	while (*(puff + i + j))
		j++;
	residual = malloc(sizeof(char) * (j + 1));
	if (!residual)
		return (free(puff), NULL);
	j = -1;
	while (*(puff + i + ++j))
		*(residual + j) = *(puff + i + j);
	*(residual + j) = '\0';
	return (free(puff), residual);
}

static char	*ft_joinstrnfree(char *puff, char *rbuffer)
{
	char	*joinedstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*(puff + i))
		i++;
	while (*(rbuffer + j))
		j++;
	joinedstr = malloc(sizeof(char) * (i + j + 1));
	if (!joinedstr)
		return (free(puff), NULL);
	i = -1;
	while (*(puff + ++i))
		*(joinedstr + i) = *(puff + i);
	j = -1;
	while (*(rbuffer + ++j))
		*(joinedstr + i + j) = *(rbuffer + j);
	*(joinedstr + i + j) = '\0';
	return (free(puff), joinedstr);
}

static char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i))
	{
		if (*(s + i) == (char)c)
			return (s + i);
		i++;
	}
	if (*(s + i) == (char)c)
		return (s + i);
	return (0);
}

static char	*ft_read_buff(int fd, char *puff, int br)
{
	char	*rbuffer;

	if (!puff)
	{
		puff = malloc(1);
		if (!puff)
			return (NULL);
		puff[0] = '\0';
	}
	rbuffer = malloc(sizeof(char) * 2);
	if (!rbuffer)
		return (free(puff), NULL);
	while (br > 0)
	{
		br = read(fd, rbuffer, 1);
		if (br == -1)
			return (free(rbuffer), NULL);
		*(rbuffer + br) = '\0';
		puff = ft_joinstrnfree(puff, rbuffer);
		if (!puff)
			return (free(rbuffer), NULL);
		if (ft_strchr(rbuffer, '\n') || !br)
			break ;
	}
	return (free(rbuffer), puff);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;
	int			i;

	temp = ft_read_buff(fd, temp, 1);
	if (!temp || !*temp)
		return (free(temp), NULL);
	i = 0;
	while (*(temp + i) && *(temp + i) != '\n')
		i++;
	i += (*(temp + i) == '\n');
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (free(temp), NULL);
	*(line + i) = '\0';
	while (i-- > 0)
		*(line + i) = *(temp + i);
	temp = ft_residual(temp);
	return (line);
}
