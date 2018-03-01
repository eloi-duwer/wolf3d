#include <wolf3d.h>

void	rotateViewVector(double *viewVector, double angle)
{
	double temp;

	temp = viewVector[1];
	viewVector[1] = viewVector[1] * cos(angle) - viewVector[0] * sin(angle);
	viewVector[0] = temp * sin(angle) + viewVector[0] * cos(angle);
}

void	normalizeVector(double *vector, double *res)
{
	double length;

	length = sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
	res[0] = vector[0] / length;
	res[1] = vector[1] / length;
}
