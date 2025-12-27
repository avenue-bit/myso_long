
#include "so_long.h"

void	error_file(void)
{
	write(2, "\033[1;31mERROR: mapfile missing or too many args\n", 48);
	write(2, "\033[1;34mExample: ./so_long [mapfile].ber\n", 41);
	exit(1);
}

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

void	error_malloc_free(t_map *map)
{
	write(2, "\033[1;31mERROR Malloc failed (freeing map)\033[0m\n", 46);
	freeallarr(map->arr, map->y);
	exit(1);
}
