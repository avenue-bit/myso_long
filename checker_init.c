
#include "so_long.h"

void	map_initializer(t_map *map, char **av)
{
	map->filename = av[1];
	map->moves = 0;
	map->e = 0;
	map->c = 0;
	map->p = 0;
	map->exit = 0;
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

void	checkmap(t_map *map, char **av)
{
	int		y;
	int		x;
	char	**cparr;

	y = 0;
	x = 0;
    map_initializer(map, av);
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
