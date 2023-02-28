/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mhar <ael-mhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:51:15 by ael-mhar          #+#    #+#             */
/*   Updated: 2023/01/29 16:28:10 by ael-mhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*cpy;
	size_t			i;

	cpy = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		cpy[i] = 0;
		i++;
	}
	s = cpy;
}

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*ptr;

	if (elementCount == SIZE_MAX && elementCount == SIZE_MAX)
		return (NULL);
	if (!elementCount || !elementSize)
		return (malloc(0));
	ptr = (void *)malloc(elementCount * elementSize);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, elementCount * elementSize);
	return (ptr);
}
