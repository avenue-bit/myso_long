
#include "so_long.h"

void	error_filename()
{
	write(2, "\033[1;31mERROR Filename incorrect (no .ber extension)\033[0m\n",
		56);
	write(2, "\033[0;34mExample: ./so_long [filename].ber\n\033[0m", 46);
	exit(1);
}

void	error_openfile()
{
	write(2, "\033[1;31mERROR File could not be opened\033[0m\n", 43);
	write(2, "\033[0;34mPath to file incorrect or File does not exist\n\033[0m",
		58);
	exit(1);
}

void	error_malloc()
{
	write(2, "\033[1;31mERROR Malloc failed\033[0m\n", 32);
	exit(1);
}

void	error_size(t_map *map)
{
	write(2, "\033[1;31mERROR Mapsize incorrect\033[0m\n", 36);
	write(2, "\033[0;34mAre all lines in the file equally long?\n\033[0m", 52);
	freeallarr(map->arr, map->y);
	exit(1);
}
void	error_wall(t_map *map)
{
	write(2, "\033[1;31mERROR Map does not contain a surrounding wall\033[0m\n", 58);
	freeallarr(map->arr, map->y);
	exit(1);
}
