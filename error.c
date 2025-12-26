
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