/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_lcommand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:00:07 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/17 11:37:59 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__last_child(t_shell *shell, int *fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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

	if (pipe(pfd) == -1)
		return (_print_error(shell, strerror(errno), 1));
	if (shell->is_infile && !shell->infiles && !shell->herdocs)
	{
		dup2((pfd)[0], 0);
		close((pfd)[1]);
	}
	if (shell->herdocs && shell->ifile == 2)
	{
		dup2(shell->herdoc[0], 0);
		close(shell->herdoc[1]);
	}
}

void	last_parent(t_shell *shell, int pid)
{
	int	status;
	int	signal_number;

	waitpid(pid, &status, 0);
	if (_wifexited(status))
	{
		shell->exit_status = _wexitstatus(status);
	}
	else if (_wifsignaled(status))
	{
		signal_number = _wtermsig(status);
		if (signal_number == SIGINT || signal_number == SIGQUIT)
		{
			shell->exit_status = 128 + signal_number;
			g_status = 0;
		}
	}
	close(0);
	while (wait(NULL) > 0)
		;
	dup2(shell->stdin_fd, 0);
}

void	exec_lastcommand(t_shell *shell)
{
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
	else if (pid > 0)
		last_parent(shell, pid);
	else
		_print_error(shell, strerror(errno), 1);
}
