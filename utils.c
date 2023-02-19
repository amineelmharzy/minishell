/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:06:56 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/17 18:30:32 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_outfd(t_shell *shell)
{
	int	fd;

	fd = 1;
	if (shell->outfile)
	{
		if (shell->ofile == 1)
			fd = open(shell->outfile, O_TRUNC | O_WRONLY);
		else
			fd = open(shell->outfile, O_WRONLY | O_APPEND);
	}
	return (fd);
}

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
		write(fd, &s[i], fd);
		i++;
	}
}

void	env(t_shell *shell, int opt)
{
	t_env	*temp;
	int		fd;

	fd = init_outfd(shell);
	temp = shell->env;
	dup2(fd, 1);
	while (temp)
	{
		if (opt == 0)
		{
			if (temp->value[0])
				printf("%s=%s\n", temp->key, temp->value);
		}
		else
		{
			if (temp->value[0])
				printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
			else
				printf("declare -x %s\n", temp->key);
		}
		temp = temp->next;
	}
	if (fd != 1)
	{
		close(fd);
		dup2(shell->stdout_fd, 1);
	}
}

int	get_path(t_shell *shell)
{
	int		i;

	if (!shell->command)
		return (0);
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
			shell->exit_status = 126;
		}
		i++;
	}
	ft_putstr_fd("Minishell : command not found\n", 2);
	shell->exit_status = 127;
	return (0);
}

void	echo(t_shell *shell)
{
	int	i;
	int	fd;
	int	newline;

	i = 1;
	newline = 1;
	fd = init_outfd(shell);
	if (fd != 1)
		dup2(fd, 1);
	if (shell->real_command[1])
	{
		if (ft_strlen(shell->real_command[1]) == 2)
		{
			if (ft_strncmp(shell->real_command[1], "-n", 2) == 0)
			{
				newline = 0;
				i++;
			}
		}
	}
	while (shell->real_command[i] != 0)
	{
		ft_putstr_fd(shell->real_command[i], 1);
		if (shell->real_command[i + 1] != 0)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline == 1)
		write(1, "\n", 1);
	if (fd != 1)
	{
		close(fd);
		dup2(shell->stdout_fd, 1);
	}
}

void	cd(t_shell *shell)
{
	char	*target_dir;

	if (!shell->real_command[1])
		target_dir = getenv("HOME");
	else
		target_dir = shell->real_command[1];
	if (chdir(target_dir) != 0)
	{
		perror("Minishell ");
		shell->exit_status = 1;
	}
}

char	*exported_key(char *var)
{
	int	i;
	char	*key;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	key = ft_calloc(i + 1, 1);
	if (!key)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		key[i] = var[i];
		i++;
	}
	key[i] = 0;
	return (key);
}

int	check_identifier(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (!str[i] || str[i] < 65 || (str[i] < 97 && str[i] > 90 && str[i] != 95) || str[i] > 122)
	{
		write(2, "Minishell : not a valid identifier\n", 36);
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

void	export(t_shell *shell)
{
	int		i;
	char	*key;

	i = 1;
	if (!(shell->real_command[1]))
	{
		env(shell, 1);
		return ;
	}
	i = 1;
	while (shell->real_command[i] != 0)
	{
		if (!check_identifier(shell, shell->real_command[i]))
		{
			key = exported_key(shell->real_command[i]);
			if (ft_strchr(shell->real_command[i], '='))
			{
				is_env(shell, key, ft_strlen(key), 0);
				add_env_var(shell, shell->real_command[i]);
			}
			else
			{
				if (!is_env(shell, key, ft_strlen(key), 1))
					add_env_var(shell, shell->real_command[i]);
			}
			free(key);
		}
		i++;
	}
}

void	pwd(t_shell *shell)
{
	int	fd;

	fd = init_outfd(shell);
	if (getcwd(shell->cwd, sizeof(shell->cwd)) == NULL)
	{
		perror("Minishell ");
		shell->exit_status = 1;
	}
	else
	{
		if (fd != 1)
			dup2(fd, 1);
		printf("%s\n", shell->cwd);
		if (fd != 1)
		{
			close(fd);
			dup2(shell->stdout_fd, 1);
		}
	}
}

void	unset(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->real_command[i] != 0)
	{
		if (!check_identifier(shell, shell->real_command[i]))
			is_env(shell, shell->real_command[i], ft_strlen(shell->real_command[i]), 0);
		i++;
	}
}
