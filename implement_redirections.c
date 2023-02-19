/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:24:52 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/19 17:51:00 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	implement_redirection(t_shell *shell)
{
	char	*temp;

	set_outfile(shell);
	set_infile(shell);
	if (iofiles_errors(shell, "<<"))
		return (0);
	temp = parse_iofiles(shell, "<<");
	shell->herdocs = ft_split(temp, ' ');
	free(temp);
	if (iofiles_errors(shell, ">>"))
		return (0);
	temp = parse_iofiles(shell, ">>");
	shell->afiles = ft_split(temp, ' ');
	free(temp);
	if (iofiles_errors(shell, "<"))
		return (0);
	temp = parse_iofiles(shell, "<");
	shell->infiles = ft_split(temp, ' ');
	free(temp);
	if (iofiles_errors(shell, ">"))
		return (0);
	temp = parse_iofiles(shell, ">");
	shell->outfiles = ft_split(temp, ' ');
	free(temp);
	return (1);
}
