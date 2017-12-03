#include <wolf3d.h>

void	parseFile(t_infos *infos, char *fileName)
{
	int 	fd;
	char	*line;
	int		ret;

	if ((fd = open(fileName, O_RDONLY)) < 0)
		printError(infos, "Error: fd < 0");
	while (ret = get_next_line(fd, &line))
	{

	}
}
