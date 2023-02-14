/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:54:27 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/14 11:38:40 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_outfiles(t_shell *shell)
{
	int	i;
	int	fd;

	i = 0;
	if (shell->outfiles)
	{
		while (shell->outfiles[i] != 0)
		{
			fd = open(shell->outfiles[i], O_CREAT, 0644);
			close(fd);
			if (!shell->outfiles[i + 1] && shell->ofile == 1)
				shell->outfile = shell->outfiles[i];
			i++;
		}
	}
	i = 0;
	if (shell->afiles)
	{
		while (shell->afiles[i] != 0)
		{
			shell->outfile = shell->afiles[1];
			/*
			printf("%s\n", shell->outfile);
			fd = open(shell->afiles[i], O_CREAT, 0644);
			close(fd);
			if (!shell->afiles[i + 1] && shell->ofile == 2)
				shell->outfile = shell->afiles[1];
			printf("%s\n", shell->outfile);
			*/
			i++;
		}
	}
	return (1);
}
