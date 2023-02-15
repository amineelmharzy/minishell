/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:48:20 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/15 10:40:12 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (shell->outfile)
		{
			if (shell->ofile == 1)
				fd = open(shell->outfile, O_WRONLY);
			else
				fd = open(shell->outfile, O_WRONLY | O_APPEND);
			dup2(fd, 1);
		}
		if (shell->infiles)
		{
			shell->infile_output = read_infile(shell);
			write(pfd[1], shell->infile_output,
				ft_strlen(shell->infile_output));
		}
		else
			write(pfd[1], shell->herdoc_output, ft_strlen(shell->herdoc_output));
		dup2(pfd[0], 0);
		close(pfd[1]);
		dup2(pfd2[1], 1);
		close(pfd2[0]);
		execve(shell->rcommand, shell->real_command, shell->envp);
		exit(0);
	}
	else
	{
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

	fd = 0;
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
		if (shell->infiles)
		{
			shell->infile_output = read_infile(shell);
			write(pfd[1], shell->infile_output,
				ft_strlen(shell->infile_output));
			close(0);
			dup2(pfd[0], 0);
			close(pfd[1]);
		}
		else
		{
			write(pfd[1], shell->herdoc_output, ft_strlen(shell->herdoc_output));
			close(0);
			dup2(pfd[0], 0);
			close(pfd[1]);
		}
		execve(shell->rcommand, shell->real_command, shell->envp);
		close(pfd[0]);
		exit(0);
	}
	else
	{
		close(0);
		dup2(shell->stdin_fd, 0);
		waitpid(-1, NULL, 0);
	}
}
