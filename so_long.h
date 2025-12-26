

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_map
{
	char	*filename;
	char	*line;
	char	*file;
	char	**maparr;
	char	**mapcopy;
	int		moves;
	int		y;
	int		x;
	int		e;
	int		c;
	int		c_check;
	int		e_check;
	int		p;
	int		exit;
}			t_map;

char		*get_next_line(int fd);

void		check_filename(t_map *map);
void		checkmap(t_map *map);
void		map_initializer(t_map *map, char **av);

void		error_filename();
void		error_openfile();

#endif