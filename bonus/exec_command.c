/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:48:20 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/05/16 12:24:32 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent(t_shell *shell, int *pfd)
{
	int	status;

	dup2((pfd)[0], 0);
	close((pfd)[1]);
	close((pfd)[0]);
	free(pfd);
	shell->exit_status = 0;
}

void	_child_(t_shell *shell, int **pfd, int *fd)
{
	if (shell->infiles && shell->ifile == 1)
	{
		shell->infile = get_infile(shell);
		*fd = open(shell->infile, O_RDONLY);
		dup2(*fd, 0);
	}
	if (shell->outfile)
	{
		if (shell->ofile == 1)
			*fd = open(shell->outfile, O_WRONLY);
		else
			*fd = open(shell->outfile, O_WRONLY | O_APPEND);
		dup2(*fd, 1);
	}
	else
	{
		dup2((*pfd)[1], 1);
		close((*pfd)[0]);
	}
}

void	__parent(int pid, int pfd[2])
{
	waitpid(pid, NULL, 0);
	dup2(pfd[0], 0);
	close(pfd[1]);
	close(pfd[0]);
}

void	child(t_shell *shell)
{
	int	pid;
	int	pfd[2];

	pipe(pfd);
	if ((shell->is_infile && !shell->infile && !shell->herdoc_output)
		|| shell->exit_status != 0)
	{
		dup2(pfd[0], 0);
		close(pfd[1]);
	}
	if (shell->herdocs && shell->herdoc_output && shell->ifile == 2)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(pfd[1], 1);
			close(pfd[0]);
			printf("%s", shell->herdoc_output);
			exit(0);
		}
		else
			__parent(pid, pfd);
	}
}

void	exec_command(t_shell *shell)
{
	int	pid;
	int	fd;
	int	*pfd;

	pfd = (int *)ft_calloc(2, sizeof(int));
	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		_child_(shell, &pfd, &fd);
		child(shell);
		if (execve(shell->rcommand, shell->parsed_command, shell->envp) < 0)
		{
			perror("minishell");
			exit(1);
		}
		exit(0);
	}
	else
		parent(shell, pfd);
}
