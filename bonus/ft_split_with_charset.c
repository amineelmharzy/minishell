/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_charset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 14:48:09 by ael-mhar          #+#    #+#             */
/*   Updated: 2022/06/02 14:41:57 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	check_sep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	count_strings(char *str, char *charest)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && check_sep(str[i], charest) == 1)
		{
			i++;
		}
		if (str[i] != '\0')
		{
			count++;
		}
		while (str[i] != '\0' && check_sep(str[i], charest) == 0)
		{
			i++;
		}
	}
	return (count);
}

int	ft_seplen(char *str, char *charset)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] && (!check_sep(str[i], charset)))
	{
		i++;
	}
	return (i);
}

char	*ft_fill(char *str, char *charset)
{
	char	*word;
	int		i;
	int		wl;

	wl = ft_seplen(str, charset);
	i = 0;
	word = malloc(wl + 1);
	while (i < wl)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, char *charset)
{
	char	**array;
	int		i;

	i = 0;
	array = malloc(sizeof(char *) * (count_strings(str, charset) + 1));
	while (*str != '\0')
	{
		while (*str != '\0' && check_sep(*str, charset))
			str++;
		if (*str != '\0')
		{
			array[i] = ft_fill(str, charset);
			i++;
		}
		while (*str != '\0' && !check_sep(*str, charset))
			str++;
	}
	array[i] = 0;
	return (array);
}
