/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:54:27 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/14 09:38:43 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_outfiles(t_shell *shell)
{
	int	i;
	int	fd;

	i = 0;
	while (shell->outfiles[i] != 0)
	{
		if (!shell->outfiles[i + 1] && shell->outfile == 1)
			shell->outfile = shell->outfiles[i];
		i++;
	}
	i = 0;
	while (shell->afiles[i] != 0)
	{
		if (!shell->afiles[i + 1] && shell->afile == 2)
			shell->outfile = shell->afiles[1];
		i++;
	}
}
