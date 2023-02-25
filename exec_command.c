/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:48:20 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/25 09:46:05 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_shell *shell, int **pfd, int **pfd2, int *fd)
{
	int	pid;

	int	pfd3[2];
	pipe(pfd3);
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
		dup2((*pfd2)[1], 1);
		close((*pfd2)[0]);
	}
	if (shell->is_infile && !shell->infile && !shell->herdoc_output)
	{
		dup2(pfd3[0], 0);
		close(pfd3[1]);
	}
	if (shell->herdocs && shell->herdoc_output && shell->ifile == 2)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(pfd3[1], 1);
			close(pfd3[0]);
			printf("%s", shell->herdoc_output);
			exit(0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			dup2(pfd3[0], 0);
			close(pfd3[1]);
		}
	}
}

void	parent(t_shell *shell, int **pfd, int **pfd2)
{
	int	status;

	dup2((*pfd2)[0], 0);
	close((*pfd2)[1]);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}

void	exec_command(t_shell *shell)
{
	int	pid;
	int	fd;
	int	*pfd;
	int	*pfd2;

	pfd = (int *)ft_calloc(2, sizeof(int));
	pfd2 = (int *)ft_calloc(2, sizeof(int));
	pipe(pfd);
	pipe(pfd2);
	pid = fork();
	if (pid == 0)
	{
		child(shell, &pfd, &pfd2, &fd);
		execve(shell->rcommand, shell->parsed_command, shell->envp);
	}
	else
	{
		parent(shell, &pfd, &pfd2);
		free(pfd);
		free(pfd2);
	}
}

void	last_child(t_shell *shell, int **pfd, int *fd)
{
	int	pid;
	int	pfd2[2];
	pipe(pfd2);
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
	if (shell->is_infile && !shell->infiles && !shell->herdocs)
	{
		dup2(pfd2[0], 0);
		close(pfd2[1]);
	}
	if ((shell->herdoc_output && shell->ifile == 2))
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(pfd2[1], 1);
			close(pfd2[0]);
			printf("%s", shell->herdoc_output);
			exit(0);
		}
		else
		{
			waitpid(-1, NULL, 0);
			dup2(pfd2[0], 0);
			close(pfd2[1]);
		}
	}
	if (execve(shell->rcommand, shell->parsed_command, shell->envp) == -1)
		shell->exit_status = 1;
}

void	exec_lastcommand(t_shell *shell)
{
	int	status;
	int	pid;
	int	*pfd;
	int	fd;

	pfd = (int *)ft_calloc(2, sizeof(int));
	pipe(pfd);
	pid = fork();
	if (pid == 0)
		last_child(shell, &pfd, &fd);
	else
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		close(0);
		dup2(shell->stdin_fd, 0);
		free(pfd);
	}
}
