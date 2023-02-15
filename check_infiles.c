/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 14:25:48 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/15 10:57:13 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_infiles(t_shell *shell)
{
	int	i;
	int	fd;

	i = 0;
	if (!shell->infiles)
		return (1);
	while (shell->infiles[i] != 0)
	{
		fd = open(shell->infiles[i], O_RDONLY);
		if (fd == -1)
		{
			//perror("%s : No such file or directory\n", shell->infiles[i]);
			perror("Minishell ");
			return (0);
		}
		close(fd);
		i++;
	}
	return (1);
}
