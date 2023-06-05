/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:24:52 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/05 17:44:23 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_iofile_checker(t_shell *shell)
{
	if (check_empty_iofiles(shell->command, "<<"))
	{
		print_error(shell, "", E_NFOD, 1);
		return (0);
	}
	if (check_empty_iofiles(shell->command, ">>"))
	{
		print_error(shell, "", E_NFOD, 1);
		return (0);
	}
	if (check_empty_iofiles(shell->command, "<"))
	{
		print_error(shell, "", E_NFOD, 1);
		return (0);
	}
	if (check_empty_iofiles(shell->command, ">"))
	{
		print_error(shell, "", E_NFOD, 1);
		return (0);
	}
	set_outfile(shell);
	set_infile(shell);
	return (1);
}

int	implement_redirection(t_shell *shell)
{
	char	*temp;

	if (!run_iofile_checker(shell))
		return (0);
	if (iofiles_errors(shell, "<<"))
		return (0);
	temp = parse_iofiles(shell, "<<");
	shell->herdocs = ft_split_with_space(temp, 1);
	if (iofiles_errors(shell, ">>"))
		return (0);
	temp = parse_iofiles(shell, ">>");
	shell->afiles = ft_split_with_space(temp, -1);
	if (iofiles_errors(shell, "<"))
		return (0);
	temp = parse_iofiles(shell, "<");
	shell->infiles = ft_split_with_space(temp, -1);
	if (iofiles_errors(shell, ">"))
		return (0);
	temp = parse_iofiles(shell, ">");
	shell->outfiles = ft_split_with_space(temp, -1);
	return (1);
}
