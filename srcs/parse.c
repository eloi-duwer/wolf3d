/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 17:11:04 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/01 17:13:49 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int		getsizeandpos(t_infos *infos, char *line)
{
	char	**values;
	int		i;

	if (!(values = ft_strsplit(line, ' ')))
		printerror(infos, "ft_strsplit returned NULL");
	i = 0;
	while (values[i])
		++i;
	if (i != 4)
		printerror(infos, \
			"The first line of the map file must contain exactly 4 values");
	infos->map_size.x = ft_atoi(values[0]);
	infos->map_size.y = ft_atoi(values[1]);
	infos->player_pos.x = (double)ft_atoi(values[2]) + 0.5;
	infos->player_pos.y = (double)ft_atoi(values[3]) + 0.5;
	i = -1;
	while (++i < 4)
		free(values[i]);
	free(values);
	free(line);
	infos->pixelperblock = (int)floor(fmin(\
		(double)infos->miniapsizepixels.x / (double)(infos->map_size.x), \
		(double)infos->miniapsizepixels.y / (double)(infos->map_size.y)));
	setminimaptopleft(infos);
	return (-1);
}

void	allocatetheworldmap(t_infos *infos)
{
	int	i;

	if (!(infos->world_map =\
			(int **)malloc(sizeof(int *) * infos->map_size.x)))
		printerror(infos, "Malloc returned NULL");
	i = -1;
	while (++i < infos->map_size.x)
	{
		if (!(infos->world_map[i] =\
				(int *)malloc(sizeof(int) * infos->map_size.y)))
			printerror(infos, "Malloc returned NULL");
	}
}

void	filloneline(int **map, int col, char *line, t_infos *infos)
{
	int		i;
	char	**tab_line;
	int		expected_size;

	expected_size = infos->map_size.x;
	if (!(tab_line = ft_strsplit(line, ' ')))
		printerror(infos, "ft_strsplit returned NULL");
	i = -1;
	while (++i < expected_size && tab_line[i])
	{
		map[i][col] = ft_atoi(tab_line[i]);
		free(tab_line[i]);
	}
	if (i != expected_size || tab_line[i])
		printerror(infos, "Found a line with wrong line length");
	free(tab_line);
	free(line);
}

void	parsefile(t_infos *infos, char *file_name)
{
	int		fd;
	char	*line;
	int		ret;
	int		nb;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		printerror(infos, "Error: fd < 0");
	if ((ret = get_next_line(fd, &line)) != 1)
		printerror(infos, "get_next_line returned -1 or the file is empty");
	nb = getsizeandpos(infos, line);
	allocatetheworldmap(infos);
	while ((ret = get_next_line(fd, &line)) == 1 && ++nb < infos->map_size.y)
		filloneline(infos->world_map, nb, line, infos);
	if (ret == -1)
		printerror(infos, "get_next_line returned 0");
	else if (nb != infos->map_size.y - 1)
		printerror(infos,\
			"Number of lines different than the number in the declaration");
	if (infos->world_map[(int)floor(infos->player_pos.x)]\
		[(int)floor(infos->player_pos.y)] == 1)
		printerror(infos, "Player begin position is in a wall");
	close(fd);
}
