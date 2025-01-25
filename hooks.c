#include "FDF.h"

int	key_handle(int keysysm, t_gl *gl_ptr)
{
	if (keysysm == XK_Escape)
	{
		mlx_destroy_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr);
		gl_ptr->win_ptr = NULL;
		printf("WINDOW CLOSED!\n");
	}
	else
		printf("%d\n", keysysm);
	return (0);
}

int	hooks(t_gl *gl_ptr)
{
	mlx_loop_hook(gl_ptr->mlx_ptr, draw, gl_ptr);
	mlx_loop(gl_ptr->mlx_ptr);
	mlx_destroy_display(gl_ptr->mlx_ptr);
	return (0);
}