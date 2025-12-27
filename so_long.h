

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef	struct s_player
{
	int	y;
	int	x;
}	t_player;

typedef struct s_map
{
	char		*filename;
	char		**arr;
	int			moves;
	int			y;
	int			x;
	int			c;
	int			e;
	int			c_check;
	int			e_check;
	int			p;
	t_player	player;
	int			exit;
}				t_map;

char			*get_next_line(int fd);

void			map_initializer(t_map *map, char **av);

char			*addtomapstring(char *s1, char *s2);
void			freeallarr(char **r, int j);
char			**createstringarr(char *str, char **r, int nw);
char			**splitstring(char *str);
void			create_maparr(t_map *map);

void			check_filename(t_map *map);
void			check_size(t_map *map);
void			check_wall(t_map *map);
void			check_params(t_map *map);
void			check_paths(t_map cpmap, int y, int x, t_map *map);
void			checkmap(t_map *map);

void			error_filename(void);
void			error_openfile(void);
void			error_malloc(void);
void			error_size(t_map *map);
void			error_wall(t_map *map);
void			error_params(t_map *map);
void 			error_path(t_map *map);

#endif