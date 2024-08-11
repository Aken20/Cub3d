#include "Cub3d.h"

bool ft_check_collision(t_data *data, int x, int y, int direction)
{
    int pixel;
    int p_size;
    int speed;

    pixel = data->pixel;
    speed = data->speed;
    p_size = pixel / 3 - 1;

    // printf("x: %d, y: %d\n", x / pixel, y / pixel);
    if (direction == 1)
    {
        if (data->map_s->map[(y - speed) / pixel][x / pixel] != '1' && data->map_s->map[(y - speed) / pixel][(x + p_size) / pixel] != '1')
            return true;
    }
    else if (direction == 2)
    {
        if (data->map_s->map[(y + speed + p_size) / pixel][x / pixel] != '1' && data->map_s->map[(y + speed + p_size) / pixel][(x + p_size) / pixel] != '1')
            return true;
    }
    else if (direction == 3)
    {
        if (data->map_s->map[y / pixel][(x - speed) / pixel] != '1' && data->map_s->map[(y + p_size) / pixel][(x - speed) / pixel] != '1')
            return true;
    }
    else if (data->map_s->map[y / pixel][(x + speed + p_size) / pixel] != '1' && data->map_s->map[(y + p_size) / pixel][(x + speed + p_size) / pixel] != '1')
        return true;
    return false;
}

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
                data->rx = data->px;
                data->ry = data->py;
                c = data->map_s->map[i][j];
                if (c == 'N')
                    data->rx += data->pixel / 6;
                else if (c == 'W')
                    data->ry += data->pixel / 6;
                else if (c == 'S')
                    data->rx += data->pixel / 6, data->ry += data->pixel / 3;
                else if (c == 'E')
                    data->rx += data->pixel / 3, data->ry += data->pixel / 6;
            }
            j++;
        }
        i++;
    }
}
