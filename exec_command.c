/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:48:20 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/20 18:44:53 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(t_shell *shell, int **pfd1, int **pfd2)
{

}

void	exec_command(t_shell *shell)
{
	int	pid;
	int	fd;
	int	pfd[2];
	int	pfd2[2];

	pipe(pfd);
	pipe(pfd2);
	fd = 0;
	pid = fork();
	if (pid == 0)
	{
		if (shell->infiles && shell->ifile == 0)
		{
			shell->infile = get_infile(shell);
			fd = open(shell->infile, O_RDONLY);
			dup2(fd, 0);
		}
		if (shell->outfile)
		{
			if (shell->ofile == 1)
				fd = open(shell->outfile, O_WRONLY);
			else
				fd = open(shell->outfile, O_WRONLY | O_APPEND);
			dup2(fd, 1);
		}
		else
		{
			dup2(pfd2[1], 1);
			close(pfd2[0]);
		}
		if (shell->herdocs && shell->ifile == 2)
		{
			dup2(pfd[0], 0);
			close(pfd[1]);
		}
		if (execve(shell->rcommand, shell->real_command, shell->envp) == -1)
			shell->exit_status = 1;
		exit(0);
	}
	else
	{
		if (shell->herdocs && shell->ifile == 2)
		{
			write(pfd[1], shell->herdoc_output, ft_strlen(shell->herdoc_output));
			close(pfd[1]);
		}
		dup2(pfd2[0], 0);
		close(pfd2[1]);
		waitpid(-1, NULL, 0);
	}
}

void	ecev_lastcommand(t_shell *shell)
{
	int	pid;
	int	pfd[2];
	int	fd;

	pipe(pfd);
	pid = fork();
	if (pid == 0)
	{
		if (shell->outfile)
		{
			if (shell->ofile == 1)
				fd = open(shell->outfile, O_WRONLY);
			else
				fd = open(shell->outfile, O_WRONLY | O_APPEND);
			dup2(fd, 1);
		}
		if (shell->infiles && shell->ifile == 1)
		{
			shell->infile = get_infile(shell);
			fd = open(shell->infile, O_RDONLY);
			dup2(fd, 0);
		}
		if (shell->herdocs && shell->ifile == 2)
		{
			dup2(pfd[0], 0);
			close(pfd[0]);
			close(pfd[1]);
		}
		if (execve(shell->rcommand, shell->real_command, shell->envp) == -1)
			shell->exit_status = 1;
		exit(0);
	}
	else
	{
		if (shell->herdocs && shell->ifile == 2)
		{
			write(pfd[1], shell->herdoc_output, ft_strlen(shell->herdoc_output));
			close(pfd[1]);
		}
		waitpid(-1, NULL, 0);
		close(0);
		dup2(shell->stdin_fd, 0);
	}
}
