/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:00:52 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/30 13:13:40 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_joinchar(char *s1, char c)
{
	int		i;
	char	*newstr;
	int		length;

	i = 0;
	if (!s1 || !c)
		return (NULL);
	length = ft_strlen((char *)s1) + 1;
	newstr = (char *)ft_calloc(sizeof(char) * (length + 1), 1);
	if (!newstr)
		return (NULL);
	while (s1[i] != 0)
	{
		newstr[i] = s1[i];
		i++;
	}
	newstr[i++] = c;
	newstr[i] = '\0';
	free(s1);
	return (newstr);
}
