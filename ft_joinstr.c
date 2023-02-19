/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:00:52 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/20 00:34:42 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_joinstr(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*newstr;
	int		length;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	newstr = (char *)ft_calloc(sizeof(char) * (length + 1), 1);
	if (!newstr)
		return (NULL);
	while (s1[i] != 0)
	{
		if (s1[i] == '\\' && s1[i + 1] == 0)
			break ;
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j])
		newstr[i++] = s2[j++];
	free(s1);
	free(s2);
	newstr[i] = '\0';
	return (newstr);
}
