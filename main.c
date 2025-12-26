
#include "so_long.h"

void	check_filename(t_map *map)
{
	size_t	len;

	len = 0;
	while (map->filename[len])
		len++;
	if (map->filename[len - 1] == 'r' && map->filename[len - 2] == 'e'
		&& map->filename[len - 3] == 'b' && map->filename[len - 4] == '.')
		return ;
	else
		error_filename();
}

char	*addtomapstring(char *s1, char *s2)
{
	char	*joinstr;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!s1)
		return (addtomapstring("", s2));
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	joinstr = malloc(sizeof(char) * (i + j + 1));
	if (!joinstr)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		joinstr[j++] = s1[i++];
	i = 0;
	while (s2[i])
		joinstr[j++] = s2[i++];
	joinstr[j] = '\0';
	return (joinstr);
}

void	freeallarr(char **r, int j)
{
	while (j > 0)
		free(r[--j]);
	free(r);
}

char **createstringarr(char *str, char **r, int nw)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	while (j < nw)
		{
			k = 0;
			while (str[i + k] && str[i + k] != '\n')
				k++;
			r[j] = malloc(sizeof(char) * (k + 1));
			if (!r[j])
				return (freeallarr(r, j), NULL);
			k = 0;
			while (str[i] && str[i] != '\n')
				r[j][k++] = str[i++];
			r[j++][k] = '\0';
			if (str[i] == '\n')
				i++;
		}
		r[j] = NULL;
		return (r);
}

char **splitstring(char *str)
{
	char **r;
	int nw;
	int i;
	int j;

	nw = 0;
	i = 0;
	while (str && str[i])
		{
		if (str[i] != '\n' && (i == 0 || str[i - 1] == '\n'))
			nw++;
		i++;
		}
	r = malloc(sizeof(char *) * (nw + 1));
	if (!r)
		return (NULL);
	return (createstringarr(str, r, nw));
}

void	create_maparr(t_map *map)
{
	char	*mapstring;
	char	*buffer;
	char	*line;
	int		fd;

	mapstring = NULL;
	fd = open(map->filename, O_RDONLY);
	if (fd == -1)
		error_openfile();
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		buffer = addtomapstring(mapstring, line);
		if (mapstring)
			free(mapstring);
		free(line);
		if (!buffer)
			break ;
		mapstring = buffer;
	}
	close(fd);
	map->maparr = splitstring(mapstring);
	free(mapstring);
}
// if (map->maparr)
// {
// 	int i = 0;
// 	while (map->maparr[i])
// 		i++;
// 	return (freeallarr(map->maparr, i));
// }


void	checkmap(t_map *map)
{
	check_filename(map);
	create_maparr(map);
	// check_parameter(map);
}

void	map_initializer(t_map *map, char **av)
{
	map->filename = av[1];
	map->moves = 0;
	map->y = 0;
	map->e = 0;
	map->c = 0;
	map->p = 0;
	map->exit = 0;
}

int	main(int ac, char **av)
{
	t_map map;
	int fd;
	if (ac != 2)
	{
		write(2, "\033[1;31mERROR: mapfile missing\n", 31);
		write(2, "\033[1;34mExample: ./so_long [mapfile].ber\n", 41);
		return (-1);
	}

	map_initializer(&map, av);
	checkmap(&map);
	// while (1)
	// {
	// 	char *rstr = get_next_line(fd);
	// 	if (! rstr)
	// 		break ;
	// 	printf("%s", rstr);
	// 	free(rstr);
	// }
	//printf("here");
	return (0);
	// https://github.com/josephcheel/42-So_long/blob/master/Mandatory/src/check_valid_path.c
}