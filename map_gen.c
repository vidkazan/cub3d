#include "cub3d.h"

void  map_gen(t_data *data)
{
	int i = -1;
	char **map = malloc(sizeof(char *) * (10 + 1));
	map[10] = 0;
	char *map_s[] =
	{
		"           xAAAx",
		"           D000B",
		"xAAAAAAAAAAD000BAAAAAAAAAAAAAx",
		"D0000000000000000000000000000B",
		"D0000000000000000000000000000B",
		"xCCCCCCCCCCD000BCCCCCCCCCCCCCx",
		"           D000B",
		"           D000B",
		"           D000B",
		"           xCCCx"
	};
	while (++i < 10)
		map[i] = ft_strdup(map_s[i]);
	data->map = map;
}
