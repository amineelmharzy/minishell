/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:48:20 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/14 11:30:01 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_shell *shell)
{
	int	pid;
	int	fd;
	int	pfd[2];

	pid = fork();
	pipe(pfd);
	fd = 0;
	if (pid == 0)
	{
		if (shell->outfile)
		{
			if (shell->ofile == 1)
				fd = open(shell->outfile, O_WRONLY);
			else
				fd = open(shell->outfile, O_APPEND);
			dup2(fd, 1);
		}
		printf("%s\n", shell->outfile);
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
		execve(shell->rcommand, shell->real_command, shell->envp);
		close(pfd[0]);
		if (fd)
			close(fd);
		exit(0);
	}
	wait(NULL);
}
