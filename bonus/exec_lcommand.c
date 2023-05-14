/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lcommand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:00:07 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/13 14:48:59 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__last_child(t_shell *shell, int *fd)
{
	signal(SIGINT, SIG_DFL);
	if (shell->outfile)
	{
		if (shell->ofile == 1)
			*fd = open(shell->outfile, O_WRONLY);
		else
			*fd = open(shell->outfile, O_WRONLY | O_APPEND);
		dup2(*fd, 1);
	}
	if (shell->infiles && shell->ifile == 1)
	{
		shell->infile = get_infile(shell);
		*fd = open(shell->infile, O_RDONLY);
		dup2(*fd, 0);
	}
	if (shell->is_herdoc)
	{
		close(0);
		dup2(shell->stdin_fd, 0);
	}
}

void	__last_parent(int pfd[2], int pid)
{
	waitpid(pid, NULL, 0);
	dup2((pfd)[0], 0);
	close((pfd)[1]);
}

void	last_child(t_shell *shell, int *fd)
{
	int	pid;
	int	pfd[2];

	pipe(pfd);
	if ((shell->is_infile && !shell->infiles && !shell->herdocs)
		|| shell->exit_status != 0)
	{
		dup2((pfd)[0], 0);
		close((pfd)[1]);
	}
	if ((shell->herdoc_output && shell->ifile == 2))
	{
		pid = fork();
		if (pid == 0)
		{
			dup2((pfd)[1], 1);
			close((pfd)[0]);
			printf("%s", shell->herdoc_output);
			exit(0);
		}
		else
			__last_parent(pfd, pid);
	}
}

void	exec_lastcommand(t_shell *shell)
{
	int	status;
	int	pid;
	int	fd;

	pid = fork();
	if (pid == 0)
	{
		__last_child(shell, &fd);
		last_child(shell, &fd);
		if (execve(shell->rcommand, shell->parsed_command, shell->envp) < 0)
		{
			perror("minishell");
			exit(1);
		}
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		close(0);
		dup2(shell->stdin_fd, 0);
	}
}
