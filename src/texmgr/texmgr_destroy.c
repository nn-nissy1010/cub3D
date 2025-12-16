/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texmgr_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuwahat <tkuwahat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:07:23 by nnishiya          #+#    #+#             */
/*   Updated: 2025/11/30 23:04:46 by tkuwahat         ###   ########.fr       */
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
}
