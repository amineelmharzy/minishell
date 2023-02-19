/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:06:47 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/19 22:10:49 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chk_newline(char *s)
{
	if (!s)
		return (0);
	if (ft_strlen(shell->real_command[1]) == 2)
	{
		if (ft_strncmp(shell->real_command[1], "-n", 2) == 0)
			return (1);
	}
	return (0);
}

void	echo(t_shell *shell)
{
	int	i;
	int	fd;
	int	newline;

	i = 1;
	newline = chk_new_line(shell->real_command[1]);
	fd = init_outfd(shell);
	if (fd != 1)
		dup2(fd, 1);
	if (newline)
		i++;
	while (shell->real_command[i] != 0)
	{
		ft_putstr_fd(shell->real_command[i], 1);
		if (shell->real_command[i + 1] != 0)
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
