#include "../Cub3d.h"

int     ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

void	check_white_spaces(t_map *map_data)
{
	t_vars	vars;

	vars.x = -1;
	vars.y = -1;
	while (map_data->file[++vars.y])
	{
		vars.x = -1;
		while (map_data->file[vars.y][++vars.x])
		{
			if (ft_isspace(map_data->file[vars.y][vars.x]) &&
				map_data->file[vars.y][vars.x] != ' ')
			exit_error("(Invalid white spaces)", map_data, NULL);
		}
	}
}

void    check_only_spaces_map(t_map *map_data)
{
    t_vars vars;

    vars.y = -1;
    while (map_data->file[++vars.y])
    {
        vars.x = 0;
        while (map_data->file[vars.y][vars.x] == ' ')
            vars.x++;
        if (map_data->file[vars.y][vars.x] != '\0')
            return ;
    }
    exit_error("(found spaces only!!!)", map_data, NULL);
}

void check_unwanted_chars(t_map *map_data)
{
    t_vars vars;

    vars.y = -1;
    check_only_spaces_map(map_data);
    while (map_data->file[++vars.y])
    {
        vars.x = 0;
        while (map_data->file[vars.y][vars.x] == ' ')
            vars.x++;
        if (map_data->file[vars.y][vars.x] != '\0')
        {
            if (ft_strncmp(map_data->file[vars.y], "NO", 2) != 0 && ft_strncmp(map_data->file[vars.y], "SO", 2) != 0
            && ft_strncmp(map_data->file[vars.y], "WE", 2) != 0 && ft_strncmp(map_data->file[vars.y], "EA", 2) != 0
            && ft_strncmp(map_data->file[vars.y], "C", 1) != 0 && ft_strncmp(map_data->file[vars.y], "F", 1) != 0
            && map_data->file[vars.y][vars.x] != '1')
            exit_error("(Invalid file data)", map_data, NULL);
        }
    }
}