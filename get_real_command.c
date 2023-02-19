/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_real_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:48:28 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/19 21:56:57 by ael-mhar         ###   ########.fr       */
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
	while (*str != 0 && *str != '\"')
	{
		i = -1;
		if (*str && *str == '$' && *(str + 1) != 0 && *(str + 1) != ' ')
		{
			str++;
			str += expand_env(shell, str, &real);
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

	real = ft_calloc(1, 1);
	env = 0;
	while (*str != 0 && *str != ' ')
	{
		if (*str && *str == '$' && *(str + 1) != 0 && *(str + 1) != ' ')
		{
			str++;
			str += expand_env(shell, str, &real);
		}
		else
			real = ft_joinchar(real, *str++);
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

int	join_expanded(t_shell *shell, char **real, char *str, int option)
{
	if (option == 0)
	{
		*real = ft_joinstr(*real, expand_squotes(shell, str));
		return (ft_strlen_to_char(str, '\''));
	}
	else if (option == 1)
	{
		*real = ft_joinstr(*real, expand_dquote(shell, str));
		return (ft_strlen_to_char(str, '\"'));
	}
	else if (option == 2)
	{
		*real = ft_joinstr(*real, expand_noquotes(shell, str));
		return (ft_strlen_to_char(str, ' '));
	}
	return (0);
}

char	*get_real_command(t_shell *shell)
{
	char	*str;
	char	*real;
	char	*save;

	if (!shell->command || !shell->command[0])
		return (NULL);
	real = ft_calloc(1, 1);
	str = ft_strdup(shell->command);
	save = str;
	while (*str != 0)
	{
		if (*str == '\'')
			str += join_expanded(shell, &real, str, 0);
		else if (*str == '\"')
			str += join_expanded(shell, &real, str, 1);
		else if (*str == '$' && *(str + 1)
			&& *(str + 1) != ' ' && *(str + 1) != '\"')
			str += join_expanded(shell, &real, str, 2);
		else
			real = ft_joinchar(real, *str++);
	}
	free(save);
	free(shell->command);
	return (real);
}
