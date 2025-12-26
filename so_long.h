

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
	char	**arr;
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

char		*addtomapstring(char *s1, char *s2);
void		freeallarr(char **r, int j);
char 		**createstringarr(char *str, char **r, int nw);
char 		**splitstring(char *str);
void		create_maparr(t_map *map);

void		check_size(t_map *map);
void		check_wall(t_map *map);

void		error_filename();
void		error_openfile();
void		error_malloc();
void		error_size(t_map *map);
void		error_wall(t_map *map);

#endif