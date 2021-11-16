#include "cub3d.h"

void  map_gen(t_data *data)
{
	int i = -1;
	char **map = malloc(sizeof(char *) * (23 + 1));
	map[23] = 0;
	char *map_s[] =
	{
		"xAAAAAAAAAx",
		"D000000000B",
		"D000R0R000B",
		"D000000000B",
		"D000000000B",
		"D000R0R000B",
		"D000000000B",
		"D000000000B",
		"D000R0R000B",
		"D000000000B",
		"D000000000B",
		"D000R0R000B",
		"D000000000B",
		"D000000000B",
		"D000R0R000B",
		"D000000000B",
		"D000000000B",
		"D000R0R000B",
		"D000000000B",
		"D000000000B",
		"D000R0R000B",
		"D000000000B",
		"xCCCCCCCCCx",
	};
	while (++i < 23)
		map[i] = ft_strdup(map_s[i]);
	data->map = map;
}
