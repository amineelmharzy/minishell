/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:06:47 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/21 16:29:09 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chk_newline(char *s)
{
	if (!s)
		return (0);
	if (ft_strlen(s) == 2)
	{
		if (ft_strncmp(s, "-n", 2) == 0)
			return (0);
	}
	return (1);
}

void	echo(t_shell *shell)
{
	int	fd;
	int	newline;
	int	i;

	i = 1;
	newline = chk_newline(shell->parsed_command[1]);
	fd = init_outfd(shell);
	if (fd != 1)
		dup2(fd, 1);
	if (!newline)
		i++;
	while (shell->parsed_command[i] != 0)
	{
		ft_putstr_fd(shell->parsed_command[i], 1);
		if (shell->parsed_command[i + 1] != 0)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline == 1)
		write(1, "\n", 1);
	if (fd != 1)
	{
		close(fd);
		dup2(shell->stdout_fd, 1);
	}
}
