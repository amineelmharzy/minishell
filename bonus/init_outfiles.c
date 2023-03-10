/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:54:27 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/03/06 15:39:57 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ambiguous_redirect(t_shell *shell, char *str, char *iofile)
{
	int	i;
	int	start;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			start = str[i++];
			while (str[i] && str[i] != start)
				i++;
		}
		if (str[i] == '$')
		{
			print_error(shell, iofile, E_AMBR, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_afiles(t_shell *shell)
{
	int	i;
	int	fd;

	i = -1;
	if (shell->afiles)
	{
		while (shell->afiles[++i] != 0)
		{
			if (check_ambiguous_redirect(shell, shell->quoted_afiles[i],
					shell->afiles[i]))
				return (0);
			fd = open(shell->afiles[i], O_CREAT, 0644);
			close(fd);
			if (access(shell->afiles[i], F_OK | W_OK) == -1)
			{
				print_error(shell, shell->afiles[i], strerror(errno), 1);
				return (0);
			}
			if (!shell->afiles[i + 1] && shell->ofile == 2)
				shell->outfile = shell->afiles[i];
		}
	}
	return (1);
}

int	init_outfiles(t_shell *shell)
{
	int		i;
	int		fd;

	i = -1;
	if (shell->outfiles)
	{
		while (shell->outfiles[++i] != 0)
		{
			if (check_ambiguous_redirect(shell, shell->quoted_outfiles[i],
					shell->outfiles[i]))
				return (0);
			fd = open(shell->outfiles[i], O_CREAT | O_TRUNC, 0644);
			close(fd);
			if (access(shell->outfiles[i], F_OK | W_OK) == -1)
			{
				print_error(shell, shell->outfiles[i], strerror(errno), 1);
				return (0);
			}
			if (!shell->outfiles[i + 1] && shell->ofile == 1)
				shell->outfile = shell->outfiles[i];
		}
	}
	if (!init_afiles(shell))
		return (0);
	return (1);
}
