
#include "so_long.h"

void	error_filename(void)
{
	write(2, "\033[1;31mERROR Filename incorrect (no .ber extension)\033[0m\n",
		56);
	write(2, "\033[0;34mExample: ./so_long [filename].ber\n\033[0m", 46);
	exit(1);
}

void	error_openfile(void)
{
	write(2, "\033[1;31mERROR File could not be opened\033[0m\n", 43);
	write(2, "\033[0;34mPath to file incorrect or File does not exist\n\033[0m",
		58);
	exit(1);
}

void	error_malloc(void)
{
	write(2, "\033[1;31mERROR Malloc failed\033[0m\n", 32);
	exit(1);
}

void	error_size(t_map *map)
{
	write(2, "\033[1;31mERROR Mapsize incorrect\033[0m\n", 36);
	write(2, "\033[0;34mLines not equally long / Map too small\n\033[0m", 51);
	freeallarr(map->arr, map->y);
	exit(1);
}
void	error_wall(t_map *map)
{
	write(2, "\033[1;31mERROR Map does not contain a surrounding wall\033[0m\n",
		58);
	freeallarr(map->arr, map->y);
	exit(1);
}

void	error_params(t_map *map)
{
	write(2, "\033[1;31mERROR Map parameters incorrect\033[0m\n", 43);
	write(2, "\033[0;34mMap must contain '1' and '0' + 1 'P', min 1 'C' and 'E'\n\033[0m", 68);
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

void	error_malloc_free(t_map *map)
{
	write(2, "\033[1;31mERROR Malloc failed (freeing map)\033[0m\n", 46);
	freeallarr(map->arr, map->y);
	exit(1);
}