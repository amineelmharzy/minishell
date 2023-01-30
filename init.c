/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:42:59 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/30 13:12:32 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_real_command(t_shell *shell)
{
	int	i;
	char	*str;
	char	*real;
	char	*env;
	char	*save;

	real = ft_calloc(1, 1);
	str = ft_strdup(shell->command);
	save = str;
	while (*str != 0)
	{
		/*
		i = -1;
		if (*str && *str == '$' && *(str + 1) != 0 && *(str + 1) != ' ')
		{
			str++;
			while (str[++i] != 0)
			{
				if (!ft_isalnum(str[i]))
					break;
			}
			env = is_env(shell, str, i);
			if (env)
				real = ft_strjoin(real, env);
			str = str + i;
		}
		else
		{
			real = ft_joinchar(real, *str);
			str++;
		}*/
		real = ft_joinchar(real, *str);
		str++;
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
	shell->command = get_real_command(shell);
	//printf("%s\n", shell->command);
	/*
	if (is_fine_with_quotes(shell->command) == -1)
	{
		printf("quote error\n");
		return ;
	}
	while (*shell->command && shell->command[ft_strlen(shell->command) -1] == '\\')
	{
		shell->cmd = readline("> ");
		if (is_fine_with_quotes(shell->cmd) == -1)
		{
			free(shell->cmd);
			printf("quote error\n");
			return ;
		}
		shell->command = ft_joinstr(shell->command, shell->cmd);
	}*/
	//printf("%s\n", shell->command);
	//printf("%s", shell->command);
	//while (1);
	shell->commands = ft_split_semicolon(ft_strdup(shell->command));
	while (shell->commands[i] != 0)
	{
		printf("%s\n", shell->commands[i]);
		i++;
	}
	/*
	while (shell->commands[i] != 0)
	{
		printf("%s\n", shell->commands[i]);
		shell->command = shell->commands[i];
		shell->parsed_command = ft_split(shell->command, ' ');
		if (get_path(shell))
		{
			if (!check_command(shell))
				exec_command(shell);
		}
		else if (!check_command(shell))
			return ;
		i++;
	}
	//free(shell->command);
	i = 0;
	*/
	//while (1);
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
	//init_env(&shell);
	//free_env(&shell);
	while (1)
	{
		shell.command = readline(shell.prompt);
		add_history(shell.command);
		if (shell.command)
			run_command(&shell);
		if (!shell.command)
			exit(0);
	}
}
