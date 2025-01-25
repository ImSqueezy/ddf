/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:44:20 by aouaalla          #+#    #+#             */
/*   Updated: 2025/01/23 19:44:23 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "FDF.h"

void	pixel_put(t_gl *gl_ptr, int x, int y, int color)
{
	char	*pxl;

	if (x >= 0 && x < SIZE_X && y >= 0 && y < SIZE_Y)
	{
		pxl = gl_ptr->img.addr + (y * gl_ptr->img.line_len
				+ x * (gl_ptr->img.bp_pixel / 8));
		*(unsigned int *)pxl = color;
	}
}

// static void	draw(int x_step, int y_step, t_gl *gl_ptr)
// {
// 	int	dx;
// 	int	dy;
// 	int	error;
// 	int	e2;

// }
	// isomet(&c.x0, &c.y0, gl_ptr->map[c.y0][c.x0].z, gl_ptr);
	// isomet(&c.x1, &c.y1, gl_ptr->map[c.y1][c.x1].z, gl_ptr);

void	isomet(int *x, int *y, int z, t_gl *gl_ptr)
{
	float	ang;

	ang = 0.5;
	*x = (*x * gl_ptr->zoom) - (gl_ptr->width/2 * gl_ptr->zoom);
	*y = (*y * gl_ptr->zoom) - (gl_ptr->height/2 * gl_ptr->zoom);
	z *= gl_ptr->zoom;
	*x = (*x - *y) * cos(ang);
	*y = (*x + *y) * sin(ang) - z;
}

void	step_determiner(t_point p1, t_point p2, int *x_step, int *y_step)
{
	if (p1.x < p2.x)
		*x_step = 1;
	else
		*x_step = -1;
	if (p1.y < p2.y)
		*y_step = 1;
	else
		*y_step = -1;
}

void	line_draw(t_point p1, t_point p2, t_gl *gl_ptr)
{
	int	dx;
	int	dy;
	int	slope;
	int	decition;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (dx)
		slope = dy;
	else
		slope = dy/dx;
	decition = 2*dy-dx;
	while (p1.x <= p2.x)
	{
		pixel_put(gl_ptr, p1.x, p1.y, p1.color);
		if (decition >= 1)
		{
			decition = decition + 2*dy-2*dx;
			p1.y++;
		}
		else
			p1.y = p1.y;
		p1.x++;
	}
}

void	line_draw(t_point p1, t_point p2, t_gl *gl_ptr)
{
	int	dx;
	int	dy;
	int	slope;
	int	decition;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	if (dx)
		slope = dy;
	else
		slope = dy/dx;
	decition = 2*dy-dx;
	while (p1.x <= p2.x)
	{
		pixel_put(gl_ptr, p1.x, p1.y, p1.color);
		if (decition >= 1)
		{
			decition = decition + 2*dy-2*dx;
			p1.y++;
		}
		else
			p1.y = p1.y;
		p1.x++;
	}
}

int	color_def(t_point p1, t_point p2)
{
	if (p1.z || p2.z)
		return (0xff0000);
	return (p1.color);
}

void	line_draw(t_point p1, t_point p2, t_gl *gl_ptr)
{
	int dx;
	int dy;
}

void plotLine(t_point p1, t_point p2, t_gl *gl_ptr)
{
   int dx =  abs(p2.x-p1.x), sx = p1.x<p2.x ? 1 : -1;
   int dy = -abs(p2.y-p1.y), sy = p1.y<p2.y ? 1 : -1; 
   int err = dx+dy, e2; /* error value e_xy */
 
   for(;;){  /* loop */
      pixel_put(gl_ptr,p1.x,p1.y, color_def(p1, p2));
      if (p1.x==p2.x && p1.y==p2.y) break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; p1.x += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; p1.y += sy; } /* e_xy+e_y < 0 */
   }
}
  

t_point	change_point(int i, int j, t_gl *gl_ptr)
{
	t_point p;

	// for top view i would remove - gl_ptr->map[i][j].z
	p.x = gl_ptr->map[i][j].x * gl_ptr->zoom - gl_ptr->map[i][j].z;
	p.y = gl_ptr->map[i][j].y * gl_ptr->zoom - gl_ptr->map[i][j].z;
	p.z = gl_ptr->map[i][j].z;
	p.color = gl_ptr->map[i][j].color;
	return (p);
}

int	draw(t_gl *gl_ptr)
{
	int	i;
	int	j;

	if (!gl_ptr->win_ptr)
		return (0);
	i = -1;
	while (++i < gl_ptr->height)
	{
		j = -1;
		while (++j < gl_ptr->width)
		{
			if (j < gl_ptr->width - 1)
				plotLine(change_point(i, j, gl_ptr), change_point(i, j + 1, gl_ptr), gl_ptr);
			if (i < gl_ptr->height - 1)
				plotLine(change_point(i, j, gl_ptr), change_point(i + 1, j, gl_ptr), gl_ptr);
		}
	}
	mlx_put_image_to_window(gl_ptr->mlx_ptr, gl_ptr->win_ptr,
		gl_ptr->img.mlx_img, 0, 0);
	return (0);
}

// int main(int argc, char **argv)
// {
// 	t_gl gl;

// 	if (argc != 2)
// 		return (printf("invalid args"), 0);
// 	if (!file_check(argv[1], &gl))
// 		return (0);
// 	gl.zoom = 1;
// 	// printf("her");
// 	draw(&gl);
// 	return (0);
// }