/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:00:52 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/02/13 17:35:06 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*newstr;
	int		length;

	i = 0;
	if (!s2)
		return (NULL);
	length = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	newstr = (char *)malloc(sizeof(char) * (length + 1));
	if (!newstr)
		return (NULL);
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	while (*s2)
		newstr[i++] = *s2++;
	newstr[i] = '\0';
	//free(s1);
	return (newstr);
}
