#include "Cub3d.h"

void ft_read_map(t_data *img, char *file)
{
    int fd;

    char *line;
    int i;

    i = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0)
        printf("Error\n"), exit(0);
    line = get_next_line(fd);
    while (line)
    {
        img->map_s->map_height++;
        i = ft_strlen(line);
        if (i > img->map_s->map_width)
            img->map_s->map_width = i;
        free(line);
        line = get_next_line(fd);
    }
    // img->map_s->map_height--;
    // printf("map_width: %d, map_height: %d\n", img->map_s->map_width, img->map_s->map_height);
    close(fd);
    fd = open(file, O_RDONLY);
    if (fd < 0 || img->map_s->map_height <= 1)
        printf("Error\n"), exit(0);
    img->map_s->map = malloc(sizeof(char*) * (img->map_s->map_height + 1));
    i = 0;
    line = get_next_line(fd);
    while (line)
    {
        img->map_s->map[i++] = ft_strdup(line);
        free(line);
        line = get_next_line(fd);
    }
    img->map_s->map[i] = NULL;
    close(fd);
}
void ft_player_find(t_data *data)
{
    int i;
    int j;
    char c;

    i = 0;
    while (data->map_s->map[i])
    {
        j = 0;
        while (data->map_s->map[i][j])
        {
            if (data->map_s->map[i][j] == 'N' || data->map_s->map[i][j] == 'S'
                || data->map_s->map[i][j] == 'W' || data->map_s->map[i][j] == 'E')
            {
                data->px = (j * data->pixel) + (data->pixel / 3);
                data->py = (i * data->pixel) + (data->pixel / 3);
                data->rx = data->px + (data->pixel / 6);
                data->ry = data->py + (data->pixel / 6);
                c = data->map_s->map[i][j];
                if (c == 'N')
                    data->angle = 90;
                else if (c == 'W')
                    data->angle = 180;
                else if (c == 'S')
                    data->angle = 270;
                else if (c == 'E')
                    data->angle = 0;
            }
            j++;
        }
        i++;
    }
}
