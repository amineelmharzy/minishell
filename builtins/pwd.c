/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 22:11:48 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/03 15:42:53 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_shell *shell)
{
	int	fd;

	fd = init_outfd(shell);
	if (getcwd(shell->cwd, sizeof(shell->cwd)) == NULL)
	{
		perror("minishell");
		shell->exit_status = 1;
	}
	else
	{
		if (fd != 1)
			dup2(fd, 1);
		printf("%s\n", shell->cwd);
		if (fd != 1)
		{
			close(fd);
			dup2(shell->stdout_fd, 1);
		}
	}
	shell->exit_status = 0;
}
