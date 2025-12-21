/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texmgr_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:07:23 by nnishiya          #+#    #+#             */
/*   Updated: 2025/12/21 17:58:55 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	texmgr_destroy(t_texmgr *tm, void *mlx)
{
	if (tm->wall_north.img)
		mlx_destroy_image(mlx, tm->wall_north.img);
	if (tm->wall_south.img)
		mlx_destroy_image(mlx, tm->wall_south.img);
	if (tm->wall_west.img)
		mlx_destroy_image(mlx, tm->wall_west.img);
	if (tm->wall_east.img)
		mlx_destroy_image(mlx, tm->wall_east.img);
	if (tm->floor.img)
		mlx_destroy_image(mlx, tm->floor.img);
	if (tm->ceiling.img)
		mlx_destroy_image(mlx, tm->ceiling.img);
	if (tm->player.img)
		mlx_destroy_image(mlx, tm->player.img);
	if (tm->screen.img)
		mlx_destroy_image(mlx, tm->screen.img);
}
