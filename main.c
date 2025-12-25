
#include "so_long.h"

char	**addtomaparr(char *mapline)
{
	char	**maparr;
	int		i;
	int		j;

	i = j = 0;
	while (maparr[i] != NULL)
		i++;
	while (j < i)
	{
		maparr[j] = malloc(sizeof(char) * strlen(mapline));
		if (!maparr)
		{
			while (j > 0)
				free(maparr[j--]);
			return (free(mapline), NULL);
		}
		maparr[j] = mapline; //here
		j++;
	}
}

int	checkmap(int fd)
{
	static char	**map;
	char		*mapline;
	int			i;
	int			mx;

	if (fd == -1)
		write(2, "\e[1;35mERROR: Map not found.", 15);
	while (1)
	{
		mapline = get_next_line(fd);
		if (!mapline)
			break ;
		map = addtomaparr(mapline);
		if (!map)
			return (free(mapline), 0);
		free(mapline);
	}
	// printf("\n'''%s'''\n", mapline);
	i = 0;
	while (mapline[i] != '\n')
	{
		write(1, &mapline[i], 1);
		i++;
	}
	mx = strlen(mapline) - 1;
	printf("%i", mx);
	return (0);
}

int	main(void)
{
	int fd;

	fd = open("map.ber", O_RDONLY);
	// get_next_line(fd);
	checkmap(fd);
	// while (1)
	// {
	// 	char *rstr = get_next_line(fd);
	// 	if (! rstr)
	// 		break ;
	// 	printf("%s", rstr);
	// 	free(rstr);
	// }
	close(fd);
	//https://github.com/josephcheel/42-So_long/blob/master/Mandatory/src/check_valid_path.c
}