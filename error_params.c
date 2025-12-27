
#include "so_long.h"

void	error_size(t_map *map)
{
	write(2, "\033[1;31mERROR Mapsize incorrect\033[0m\n", 36);
	write(2, "\033[0;34mLines not equally long / Map too small\n\033[0m", 51);
	freeallarr(map->arr, map->y);
	exit(1);
}
void	error_wall(t_map *map)
{
	write(2, "\033[1;31mERROR Surrounding wall in map missing\033[0m\n", 50);
	freeallarr(map->arr, map->y);
	exit(1);
}

void	error_params(t_map *map)
{
	write(2, "\033[1;31mERROR Map parameters incorrect\033[0m\n", 43);
	write(2, "\033[0;34mMap: 1 or 0s + 1 P, >0 'C' and 'E'\n\033[0m", 47);
	freeallarr(map->arr, map->y);
	exit(1);
}

void	error_path(t_map *map)
{
	write(2, "\033[1;31mERROR Invalid path\033[0m\n", 31);
	write(2, "\033[0;34mCollectable(s) or Exit cannot be reached\n\033[0m", 53);
	freeallarr(map->arr, map->y);
	exit(1);
}
