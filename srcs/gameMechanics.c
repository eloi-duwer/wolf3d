#include <wolf3d.h>

void	doTheMove(double *pos, double vecx, double vecy)
{
	pos[0] += vecx * 0.05;
	pos[1] += vecy * 0.05;
}

void	movePlayer(t_infos *infos)
{
	double newPos[2];

	newPos[0] = infos->player_pos[0];
	newPos[1] = infos->player_pos[1];
    if (infos->keyPressed[UP])
		doTheMove(newPos, infos->view_vector[0], infos->view_vector[1]);
	if (infos->keyPressed[DOWN])
		doTheMove(newPos, -infos->view_vector[0], -infos->view_vector[1]);
	if (infos->keyPressed[LEFT])
		doTheMove(newPos, -infos->view_vector[1], infos->view_vector[0]);
	if (infos->keyPressed[RIGHT])
		doTheMove(newPos, infos->view_vector[1], -infos->view_vector[0]);

	if (infos->world_map[(int)floor(newPos[0])][(int)floor(newPos[1])] == 0)
	{
		infos->player_pos[0] = newPos[0];
		infos->player_pos[1] = newPos[1];
	}
}
