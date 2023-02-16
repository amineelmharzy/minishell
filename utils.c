/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:06:56 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/15 20:03:00 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	len;

	if (!s || !fd)
		return ;
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	env(t_shell *shell)
{
	t_env	*temp;

	temp = shell->env;
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

int	get_path(t_shell *shell)
{
	int		i;

	if (access(shell->command, F_OK | X_OK) != -1)
	{
		shell->rcommand = shell->command;
		return (1);
	}
	i = 0;
	while (shell->path[i] != 0)
	{
		shell->rcommand = ft_strjoin(shell->path[i], "/");
		while ((*shell->command) != 0 && (*(shell->command) == ' '
				|| (*(shell->command) == '\t')))
			(shell->command)++;
		shell->rcommand = ft_strjoin(shell->rcommand, shell->command);
		if (access(shell->rcommand, F_OK) != -1)
		{
			if (access(shell->rcommand, X_OK) != -1)
				return (1);
			else
				perror("Minishell ");
		}
		i++;
	}
	return (0);
}

void	echo(t_shell *shell)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (shell->parsed_command[1])
	{
		if (ft_strlen(shell->parsed_command[1]) == 2)
		{
			if (ft_strncmp(shell->parsed_command[1], "-n", 2) == 0)
			{
				newline = 0;
				i++;
			}
		}
	}
	while (shell->parsed_command[i] != 0)
	{
		ft_putstr_fd(shell->parsed_command[i], 1);
		i++;
	}
	if (newline == 1)
		write(1, "\n", 1);
}

void	cd(t_shell *shell)
{
	char	*cwd;
	char	*target_dir;

	cwd = getenv("PWD");
	target_dir = ft_strjoin(cwd, "/");
	target_dir = ft_strjoin(target_dir, shell->parsed_command[1]);
	if (shell->parsed_command[1])
	{
		printf("%s\n", target_dir);
		if (chdir(target_dir) != 0)
			perror("cd :");
	}
}

void	export(t_shell *shell)
{
	int	i;

	if (!(shell->parsed_command[1]))
	{
		env(shell);
		return ;
	}
	i = 1;
	while (shell->parsed_command[i] != 0)
	{
		add_env_var(shell, shell->parsed_command[i]);
		i++;
	}
}

/*
int	check_is_env_var(t_shell *shell)
{
	t_env *temp;
	while (temp)
	{
		if (
				*/
