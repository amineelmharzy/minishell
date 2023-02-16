/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:16:33 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/15 18:25:12 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_infile(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->infiles[i] != 0)
		i++;
	/*
	fd = open(shell->infiles[i], O_RDONLY);
	line = get_next_line(fd);
	if (output)
		free(output);
	output = ft_calloc(1, 1);
	while (line)
	{
		output = ft_joinstr(output, line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	*/
	return (shell->infiles[i - 1]);
}
