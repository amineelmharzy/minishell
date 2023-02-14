/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:42:59 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/14 09:36:34 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_real_command(t_shell *shell)
{
	int		i;
	char	*str;
	char	*real;
	char	*env;
	char	*save;

	real = ft_calloc(1, 1);
	str = ft_strdup(shell->command);
	save = str;
	while (*str != 0)
	{
		i = -1;
		if (*str == '\'')
		{
			real = ft_joinchar(real, *str++);
			while (*str != 0 && *str != '\'')
			{
				real = ft_joinchar(real, *str++);
			}
			if (!*str)
				break;
		}
		else if (*str == '\"')
		{
			real = ft_joinchar(real, *str++);
			while (*str != 0 && *str != '\"')
			{
				if (*str && *str == '$' && *(str + 1) != 0 && *(str + 1) != ' ')
				{
					str++;
					while (str[++i] != 0)
						if (!ft_isalnum(str[i]))
							break ;
					env = is_env(shell, str, i);
					if (env)
						real = ft_strjoin(real, env);
					str = str + i;
				}
				else
					real = ft_joinchar(real, *str++);
			}
		}
		else
		{
			if (*str && *str == '$' && *(str + 1) != 0 && *(str + 1) != ' ')
			{
				str++;
				while (str[++i] != 0)
					if (!ft_isalnum(str[i]))
						break ;
				env = is_env(shell, str, i);
				if (env)
					real = ft_strjoin(real, env);
				str = str + i;
			}
			else
				real = ft_joinchar(real, *str++);
		}
	}
	free(save);
	free(shell->command);
	return (real);
}

void	run_command(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->command[0])
		return ;
	if (is_fine_with_quotes(shell->command) == -1)
	{
		printf("quote error\n");
		return ;
	}
	shell->command = get_real_command(shell);
	if (!implement_redirection(shell))
		return ;
	if (!check_infiles(shell))
		return ;
	if (shell->herdocs)
		shell->herdoc_output = herdoc(shell);
	if (!shell->command[0])
		return ;
	shell->real_command = ft_split_with_space(shell->command);
	shell->command = shell->real_command[0];
	if (!get_path(shell))
		return ;
	shell->real_command[0] = shell->rcommand;
	exec_command(shell);
}

void	handle(int sig)
{
	if (sig == SIGINT)
	{
		(void) sig;
	}
	if (sig == SIGQUIT)
	{
		(void) sig;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	shell.envp = envp;
	shell.path = ft_split(getenv("PATH"), ':');
	shell.prompt = "~ ";
	shell.herdocs = 0;
	shell.herdoc_output = 0;
	shell.infiles = 0;
	shell.infile_output = 0;
	shell.outfile = 0;
	init_env(&shell);
	while (1)
	{
		shell.command = readline(shell.prompt);
		add_history(shell.command);
		if (shell.command)
			run_command(&shell);
		else
			exit(0);
	}
	//free_env(&shell);
	//while (1);
}
