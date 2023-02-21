/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:21:34 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/21 16:32:36 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtin(t_shell *shell, void (*f)(t_shell *))
{
	int	*pfd;
	int	pid;

	pfd = (int *) ft_calloc(2, sizeof(int));
	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		if (shell->is_pipe)
		{
			dup2(pfd[1], 1);
			close(pfd[0]);
		}
		f(shell);
		exit(0);
	}
	else
	{
		waitpid(-1, NULL, 0);
		if (shell->is_pipe)
		{
			dup2(pfd[0], 0);
			close(pfd[1]);
		}
	}
}
