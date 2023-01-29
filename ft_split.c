/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:48:09 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/19 11:47:44 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_sep(char c, char sep)
{
	int	i;

	i = 0;
	if (c == sep)
		return (1);
	return (0);
}

static int	count_strings(char *str, char set)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && (check_sep(str[i], set) == 1))
		{
			i++;
		}
		if (str[i] != '\0')
		{
			count++;
		}
		while (str[i] != '\0' && (check_sep(str[i], set) == 0))
		{
			i++;
		}
	}
	return (count);
}

static int	ft_seplen(char *str, char charset)
{
	int	count;
	int	i;
	int	start;

	count = 0;
	i = 0;
	start = 0;
	while (str[i] && (check_sep(str[i], charset)))
	{
		i++;
	}
	start = i;
	while (str[i] && (!check_sep(str[i], charset)))
	{
		i++;
	}
	return (i - start);
}

static char	*ft_fill(char *str, char charset)
{
	char	*word;
	int		i;
	int		wl;

	wl = ft_seplen(str, charset);
	i = 0;
	word = malloc(wl + 1);
	if (!word)
		return (NULL);
	while (i < wl)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, char set)
{
	char	**array;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	array = malloc(sizeof(char *) * (count_strings(str, set) + 1));
	if (!array)
		return (NULL);
	while (*str != '\0')
	{
		while (*str != '\0' && check_sep(*str, set))
		{
			str++;
		}
		if (*str != '\0')
		{
			array[i] = ft_fill(str, set);
			i++;
		}
		while (*str != '\0' && !check_sep(*str, set))
			str++;
	}
	array[i] = 0;
	return (array);
}
