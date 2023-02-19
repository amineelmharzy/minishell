/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_real_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:48:28 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/19 07:40:34 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dquote(t_shell *shell, char *str)
{
	char	*real;
	char	*env;
	int		i;

	real = ft_calloc(1, 1);
	real = ft_joinchar(real, *str++);
	i = -1;
	while (*str != 0 && *str != '\"')
	{
		if (*str && *str == '$' && *(str + 1) != 0 && *(str + 1) != ' ')
		{
			str++;
			while (str[++i] != 0)
				if (!ft_isalnum(str[i]))
					break ;
			env = is_env(shell, str, i, 1);
			if (env)
				real = ft_strjoin(real, env);
			if (*str && str[0] == '?')
			{
				real = ft_joinstr(real, ft_itoa(shell->exit_status));
				str++;
			}
			str = str + i;
		}
		else
			real = ft_joinchar(real, *str++);
	}
	return (real);
}


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
				break ;
		}
		else if (*str == '\"')
		{
			printf("%s\n", expand_dquote(shell, str));
		}
		/*
		else
		{
			if (*str && *str == '$' && *(str + 1) != 0 && *(str + 1) != ' ')
			{
				str++;
				while (str[++i] != 0)
					if (!ft_isalnum(str[i]))
						break ;
				env = is_env(shell, str, i, 1);
				if (env)
					real = ft_strjoin(real, env);
				if (*str && str[0] == '?')
				{
					real = ft_strjoin(real, ft_itoa(shell->exit_status));
					str++;
				}
				str = str + i;
			}
			else
				real = ft_joinchar(real, *str++);
		}
		*/
	}

	free(save);
	free(shell->command);
	return (real);
}
