#include <wolf3d.h>

int		getSizeAndPos(t_infos *infos, char *line)
{
	char	**values;
	int		i;

	if (!(values = ft_strsplit(line, ' ')))
		printError(infos, "ft_strsplit returned NULL");
	i = 0;
	while (values[i])
		i++;
	if (i != 4)
		printError(infos, \
			"The first line of the map file must contain exactly 4 values");
	infos->map_size[0] = ft_atoi(values[0]);
	infos->map_size[1] = ft_atoi(values[1]);
	infos->player_pos[0] = (double)ft_atoi(values[2]) + 0.5;
	infos->player_pos[1] = (double)ft_atoi(values[3]) + 0.5;
	i = -1;
	while (++i < 4)
		free(values[i]);
	free(values);
	free(line);
	infos->pixelPerBlock = (int)floor(fmin\
		((double)infos->miniMapSizePixels[0] / (double)(infos->map_size[0]),\
		(double)infos->miniMapSizePixels[1] / (double)(infos->map_size[1])));
	setMinimapTopLeft(infos);
	return (-1);
}

void	allocateTheWorldMap(t_infos *infos)
{
	int	i;

	if (!(infos->world_map =\
			(int **)malloc(sizeof(int *) * infos->map_size[1])))
		printError(infos, "Malloc returned NULL");
	i = -1;
	while (++i < infos->map_size[1])
	{
		if (!(infos->world_map[i] =\
				(int *)malloc(sizeof(int) * infos->map_size[0])))
			printError(infos, "Malloc returned NULL");
	}
}

void	fillOneLine(int *mapLine, char *line, t_infos *infos)
{
	int		i;
	char	**tab_line;
	int		expectedSize;

	expectedSize = infos->map_size[0];
	if (!(tab_line = ft_strsplit(line, ' ')))
		printError(infos, "ft_strsplit returned NULL");
	i = -1;
	while (++i < expectedSize && tab_line[i])
	{
		mapLine[i] = ft_atoi(tab_line[i]);
		free(tab_line[i]);
	}
	if (i != expectedSize || tab_line[i])
		printError(infos, "Found a line with wrong line length");
	free(tab_line);
	free(line);
}

void	parseFile(t_infos *infos, char *fileName)
{
	int 	fd;
	char	*line;
	int		ret;
	int		nb;

	if ((fd = open(fileName, O_RDONLY)) < 0)
		printError(infos, "Error: fd < 0");
	if ((ret = get_next_line(fd, &line)) != 1)
		printError(infos, "get_next_line returned -1 or the file is empty");
	nb = getSizeAndPos(infos, line);
	allocateTheWorldMap(infos);
	while ((ret = get_next_line(fd, &line)) == 1 && ++nb < infos->map_size[1])
		fillOneLine(infos->world_map[nb], line, infos);
	if (ret == -1)
		printError(infos, "get_next_line returned 0");
	else if (nb != infos->map_size[1] - 1)
		printError(infos,\
			"Number of lines different than the number in the declaration");
	if (infos->world_map[(int)floor(infos->player_pos[1])]\
		[(int)floor(infos->player_pos[0])] == 1)
		printError(infos, "Player begin position is in a wall");
	close(fd);
}
