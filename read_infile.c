/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:16:33 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/14 09:06:21 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_infile(t_shell *shell)
{
	int		i;
	int		fd;
	char	*line;
	char	*output;

	i = 0;
	output = 0;
	while (shell->infiles[i] != 0)
	{
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
		i++;
	}
	return (output);
}
