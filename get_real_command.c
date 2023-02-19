/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_real_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:48:28 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/19 09:06:56 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_to_char(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] != 0 && str[i] != c)
		i++;
	if (str[i] == c)
		i++;
	return (i);
}

char	*expand_dquote(t_shell *shell, char *str)
{
	char	*real;
	char	*env;
	int		i;

	real = ft_calloc(1, 1);
	real = ft_joinchar(real, *str++);
	while (*str != 0 && *str != '\"')
	{
		i = -1;
		if (*str && *str == '$' && *(str + 1) != 0 && *(str + 1) != ' ')
		{
			str++;
			if (*str && str[0] == '?')
			{
				real = ft_joinstr(real, ft_itoa(shell->exit_status));
				str++;
				break ;
			}
			while (str[++i] != 0)
				if (!ft_isalnum(str[i]))
					break ;
			env = is_env(shell, str, i, 1);
			if (env)
				real = ft_joinstr(real, ft_strdup(env));
			str = str + i;
		}
		else
			real = ft_joinchar(real, *str++);
	}
	if (*str == '\"')
		real = ft_joinchar(real, *str++);
	return (real);
}

char	*expand_noquotes(t_shell *shell, char *str)
{
	char	*real;
	char	*env;
	int		i;

	i = -1;
	real = ft_calloc(1, 1);
	env = 0;
	if (*str && *str == '$' && *(str + 1) != 0 && *(str + 1) != ' ')
	{
		str++;
		if (*str && str[0] == '?')
		{
			real = ft_joinstr(real, ft_itoa(shell->exit_status));
			str++;
		}
		while (str[++i] != 0)
			if (!ft_isalnum(str[i]))
				break ;
		env = is_env(shell, str, i, 1);
		str = str + i;
		if (env)
			real = ft_joinstr(real, ft_strdup(env));
	}
	return (real);
}

char	*expand_squotes(t_shell *shell, char *str)
{
	char	*real;

	real = ft_calloc(1, 1);
	real = ft_joinchar(real, *str++);
	while (*str != 0 && *str != '\'')
	{
		real = ft_joinchar(real, *str++);
	}
	if (*str != 0)
		real = ft_joinchar(real, *str++);
	return (real);
}

char	*get_real_command(t_shell *shell)
{
	char	*str;
	char	*real;
	char	*save;

	real = ft_calloc(1, 1);
	str = ft_strdup(shell->command);
	save = str;
	while (*str != 0)
	{
		if (*str == '\'')
		{
			real = ft_joinstr(real, expand_squotes(shell, str));
			str += ft_strlen_to_char(str, '\'');
		}
		else if (*str == '\"')
		{
			real = ft_joinstr(real, expand_dquote(shell, str));
			str += ft_strlen_to_char(str, '\"');
		}
		else if (*str == '$')
		{
			real = ft_joinstr(real, expand_noquotes(shell, str));
			str += ft_strlen_to_char(str, ' ');
		}
		else
			real = ft_joinchar(real, *str++);
	}
	free(save);
	free(shell->command);
	return (real);
}
