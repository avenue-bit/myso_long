
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
	int		i;
	int		j;

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

char	**createstringarr(char *str, char **r, int nw)
{
	int	i;
	int	j;
	int	k;

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

char	**splitstring(char *str)
{
	char	**r;
	int		nw;
	int		i;
	int		j;

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
	map->arr = splitstring(mapstring);
	free(mapstring);
}

void	check_size(t_map *map)
{
	int	y;
	int	x;
	int	max;
	int	check;

	y = 0;
	x = 0;
	max = 0;
	check = 0;
	while (map->arr[0][max])
		max++;
	while (map->arr[y])
	{
		x = 0;
		while (map->arr[y][x])
			x++;
		if (max != x)
			check = 1;
		y++;
	}
	map->x = max;
	map->y = y;
	if (check || y < 3 || max < 3)
		error_size(map);
}

void	check_wall(t_map *map)
{
	int	cy;
	int	cx;

	cy = 1;
	cx = 0;
	while (map->arr[0][cx])
		if (map->arr[0][cx++] != '1')
			error_wall(map);
	while (map->arr[cy])
	{
		cx = 0;
		while (map->arr[cy][cx])
		{
			if (map->arr[cy][cx] != '1' && cx == 0)
				error_wall(map);
			cx++;
		}
		if (map->arr[cy][cx - 1] != '1')
			error_wall(map);
		cy++;
	}
	cx = 0;
	while (map->arr[cy - 1][cx])
		if (map->arr[cy - 1][cx++] != '1')
			error_wall(map);
}

void	check_params(t_map *map)
{
	int	cy;
	int	cx;

	cy = 0;
	while (map->arr[cy])
	{
		cx = 0;
		while (map->arr[cy][cx])
		{
			if (map->arr[cy][cx] == 'C')
				map->c += 1;
			else if (map->arr[cy][cx] == 'E')
				map->e += 1;
			else if (map->arr[cy][cx] == 'P')
				map->p += 1;
			else if (map->arr[cy][cx] == '0' || map->arr[cy][cx] == '1')
				;
			else
				error_params(map);
			cx++;
		}
		cy++;
	}
	if (map->p != 1 || map->e < 1 || map->c < 1)
		error_params(map);
}

char	**duplicate_strarr(char **arr, int x)
{
	char	**newarr;
	int		i;
	int		j;

	i = 0;
	while (arr[i])
		i++;
	newarr = (char **)malloc(sizeof(char *) * (i + 1));
	if (!newarr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		newarr[i] = (char *)malloc(sizeof(char) * (x + 1));
		if (!newarr[i])
			return (freeallarr(newarr, i), NULL);
		j = -1;
		while (arr[i][++j])
			newarr[i][j] = arr[i][j];
		newarr[i][j] = '\0';
		i++;
	}
	newarr[i] = NULL;
	return (newarr);
}

void	findplayer(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->arr[y])
	{
		x = 0;
		while (map->arr[y][x])
		{
			if (map->arr[y][x] == 'P')
			{
				map->player.x = x;
				map->player.y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	check_paths(char **cparr, int y, int x, t_map *map)
{
	if (cparr[y][x] == 'C')
	{
		map->c_check -= 1;
		cparr[y][x] = '1';
	}
	else if (cparr[y][x] == 'E')
	{
		map->e_check -= 1;
		cparr[y][x] = '1';
	}
	else if (cparr[y][x] == '0' || cparr[y][x] == 'P')
		cparr[y][x] = '1';
	else if (cparr[y][x] == '1')
		return ;
	check_paths(cparr, y, x + 1, map);
	check_paths(cparr, y, x - 1, map);
	check_paths(cparr, y + 1, x, map);
	check_paths(cparr, y - 1, x, map);
}

void	checkmap(t_map *map)
{
	int		y;
	int		x;
	char	**cparr;

	y = 0;
	x = 0;
	check_filename(map);
	create_maparr(map);
	if (!map->arr || !map->arr[0])
		error_malloc();
	check_size(map);
	check_wall(map);
	check_params(map);
	findplayer(map);
	map->c_check = map->c;
	map->e_check = map->e;
	cparr = duplicate_strarr(map->arr, map->x);
	if (!cparr)
		error_malloc_free(map);
	check_paths(cparr, map->player.y, map->player.x, map);
	freeallarr(cparr, map->y);
	if (map->c_check != 0 || map->e_check >= map->e)
		error_path(map);
}

void	map_initializer(t_map *map, char **av)
{
	map->filename = av[1];
	map->moves = 0;
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

	if (map.arr)
		return (freeallarr(map.arr, map.y), 0);
	return (0);
	// https://github.com/josephcheel/42-So_long/blob/master/Mandatory/src/check_valid_path.c
}