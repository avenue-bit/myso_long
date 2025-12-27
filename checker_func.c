
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
