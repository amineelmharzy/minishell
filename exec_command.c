/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:48:20 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/23 18:08:48 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_shell *shell, int **pfd, int **pfd2, int *fd)
{
	if (shell->infiles && shell->ifile == 0)
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
	if (shell->herdocs && shell->ifile == 2)
	{
		dup2((*pfd)[0], 0);
		close((*pfd)[1]);
	}
}

void	parent(t_shell *shell, int **pfd, int **pfd2)
{
	int	status;

	if (shell->herdocs && shell->ifile == 2)
	{
		write((*pfd)[1], shell->herdoc_output, ft_strlen(shell->herdoc_output));
		close((*pfd)[1]);
	}
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
	fd = 0;
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
	if (shell->herdocs && shell->ifile == 2)
	{
		dup2(*pfd[0], 0);
		close(*pfd[0]);
		close(*pfd[1]);
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
		if (shell->herdocs && shell->ifile == 2)
		{
			write(pfd[1], shell->herdoc_output,
				ft_strlen(shell->herdoc_output));
			close(pfd[1]);
		}
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		close(0);
		dup2(shell->stdin_fd, 0);
		free(pfd);
	}
}
