/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:21:34 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/23 16:47:23 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_env(t_shell *shell, int option, void (*f)(t_shell *, int))
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
		f(shell, option);
	}
	else
	{
		waitpid(-1, NULL, 0);
		if (shell->is_pipe)
		{
			dup2(pfd[0], 0);
			close(pfd[1]);
		}
		free(pfd);
	}
}