/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 08:54:27 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/06/05 17:51:51 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_remove_space(char **res, char *str, int *i, int op)
{
	int	st;

	while (op == 0 && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	while (str && (str[*i] == '\"' || str[*i] == '\''))
	{
		st = str[(*i)++];
		while (str[*i] && str[*i] != st)
			*res = ft_joinchar(*res, str[(*i)++]);
		(*i)++;
	}
}

void	__remove_space(char **res, char *str, int *i, int len)
{
	int	st;

	if (str[*i] == ' ' || str[*i] == '\t')
	{
		if (len != 0 && !check_last_space(str, *i))
		{
			while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
				*res = ft_joinchar(*res, str[(*i)++]);
		}
		else
		{
			while (str[*i] && (str[*i] == '\t' || str[*i] == ' '))
				(*i)++;
		}
		while (str[*i] && str[*i] == '\'')
		{
			st = str[(*i)++];
			while (str[*i] != 0 && str[*i] != st)
				*res = ft_joinchar(*res, str[(*i)++]);
			(*i)++;
		}
	}
}

char	*remove_spaces(char *str)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = 0;
	res = ft_calloc(1, 1);
	_remove_space(&res, str, &i, 1);
	while (str[i] != 0)
	{
		_remove_space(&res, str, &i, 0);
		__remove_space(&res, str, &i, len);
		len++;
		if (str[i] != 0 && str[i] != '\'' && str[i] != '\"')
			res = ft_joinchar(res, str[i++]);
	}
	return (res);
}

int	init_afiles(t_shell *shell)
{
	int	i;
	int	fd;

	i = -1;
	if (shell->afiles)
	{
		while (shell->afiles[++i] != 0)
		{
			if (check_ambiguous_redirect(shell, &shell->afiles[i]))
				return (0);
			fd = open(shell->afiles[i], O_CREAT, 0644);
			close(fd);
			if (access(shell->afiles[i], F_OK | W_OK) == -1)
			{
				print_error(shell, shell->afiles[i], strerror(errno), 1);
				return (0);
			}
			if (!shell->afiles[i + 1] && shell->ofile == 2)
				shell->outfile = shell->afiles[i];
		}
	}
	return (1);
}

int	init_outfiles(t_shell *shell)
{
	int		i;
	int		fd;

	i = -1;
	if (shell->outfiles)
	{
		while (shell->outfiles[++i] != 0)
		{
			if (check_ambiguous_redirect(shell, &shell->outfiles[i]))
				return (0);
			fd = open(shell->outfiles[i], O_CREAT | O_TRUNC, 0644);
			close(fd);
			if (access(shell->outfiles[i], F_OK | W_OK) == -1)
			{
				print_error(shell, shell->outfiles[i], strerror(errno), 1);
				return (0);
			}
			if (!shell->outfiles[i + 1] && shell->ofile == 1)
				shell->outfile = shell->outfiles[i];
		}
	}
	return (init_afiles(shell));
}
