/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texmgr_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnishiya <nnishiya@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:07:23 by nnishiya          #+#    #+#             */
/*   Updated: 2025/12/21 15:16:04 by nnishiya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	texmgr_destroy(t_texmgr *tm, void *mlx)
{
	if (tm->wall.img)
		mlx_destroy_image(mlx, tm->wall.img);
	if (tm->floor.img)
		mlx_destroy_image(mlx, tm->floor.img);
	if (tm->ceiling.img)
		mlx_destroy_image(mlx, tm->ceiling.img);
	if (tm->player.img)
		mlx_destroy_image(mlx, tm->player.img);
	if (tm->screen.img)
		mlx_destroy_image(mlx, tm->screen.img);
}
