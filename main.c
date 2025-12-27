
#include "so_long.h"

int	main(int ac, char **av)
{
	t_map map;
	int fd;
	if (ac != 2)
		error_file();

	checkmap(&map, av);

	if (map.arr)
		return (freeallarr(map.arr, map.y), 0);
	return (0);
	// https://github.com/josephcheel/42-So_long/blob/master/Mandatory/src/check_valid_path.c
}
