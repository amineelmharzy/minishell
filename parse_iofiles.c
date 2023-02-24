/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_iofiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:16:02 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/23 17:58:25 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_iofile_counter(char *str, char *set, int *i, int *count)
{
	if (ft_strlen(&str[*i]) >= ft_strlen(set) && ft_strncmp(&str[*i], set,
			ft_strlen(set)) == 0)
	{
		*i += ft_strlen(set);
		while (str[*i] != 0 && str[*i] == ' ')
			(*i)++;
		if (str[*i] == '<' || str[*i] == '>')
			return (-1);
		if (str[*i])
		{
			while (str[*i] != 0 && str[*i] != '<' && str[*i] != '>'
				&& str[*i] != ' ')
				(*i)++;
			(*count)++;
		}
		else
			return (-1);
	}
	return (0);
}

int	count_iofiles(char *str, char *set)
{
	int	i;
	int	start;
	int	count;

	if (!str || !str[0])
		return (0);
	i = 0;
	start = 0;
	count = 0;
	while (str[i] != 0)
	{
		while (str[i] == '\"' || str[i] == '\'')
		{
			start = str[i];
			i++;
			while (str[i] != 0 && str[i] != start)
				i++;
			i++;
		}
		if (ft_iofile_counter(str, set, &i, &count) == -1)
			return (-1);
		i++;
	}
	return (count);
}

void	parse_quotes(char **save, char *str, int *i)
{
	int	start;

	while (str[*i] && (str[*i] == '\"'
			|| str[*i] == '\"'))
	{
		start = str[*i];
		*save = ft_joinchar(*save, str[(*i)++]);
		while (str[*i] && str[*i] != start)
			*save = ft_joinchar(*save, str[(*i)++]);
		*save = ft_joinchar(*save, str[(*i)++]);
	}
}

void	parse_file(char **files, char *str, char *set, int *i)
{
	int	start;

	*i += ft_strlen(set);
	while (str[*i] != 0 && str[*i] == ' ')
		*files = ft_joinchar(*files, str[(*i)++]);
	start = str[*i];
	if (start == '\"' || start == '\'')
	{
		(*i)++;
		while (str[*i] != 0 && str[*i] != '<' && str[*i] != '>'
			&& str[*i] != start)
			*files = ft_joinchar(*files, str[(*i)++]);
		(*i)++;
	}
	else
	{
		while (str[*i] != 0 && str[*i] != '<'
			&& str[*i] != '>' && str[*i] != ' ')
			*files = ft_joinchar(*files, str[(*i)++]);
	}
	*files = ft_joinchar(*files, ' ');
}

char	*parse_iofiles(t_shell *shell, char *set)
{
	char	*files;
	char	*save;
	int		i;

	if (!shell->command || !shell->command[0])
		return (NULL);
	if (count_iofiles(shell->command, set) == 0)
		return (NULL);
	save = ft_calloc(1, 1);
	files = ft_calloc(1, 1);
	i = 0;
	while (shell->command[i] != 0)
	{
		parse_quotes(&save, shell->command, &i);
		if (shell->command[i] && ft_strlen(&shell->command[i]) >= ft_strlen(set)
			&& !ft_strncmp(&shell->command[i], set, ft_strlen(set)))
			parse_file(&files, shell->command, set, &i);
		else if (shell->command[i] != 0)
			save = ft_joinchar(save, shell->command[i++]);
	}
	free(shell->command);
	shell->command = save;
	return (files);
}
