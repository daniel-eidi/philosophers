/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 15:20:50 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/20 08:58:26 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>
/**
 * @brief fill pointer s with constant byte c for n bytes and return s
 * 
 * @param s pointer to start fill with c for n times
 * @param c constant byte that is filled for n bytes in s 
 * @param n 
 * @return void* point to point s
 */
void	*ft_memset(void *s, int c, size_t n)
{	
	size_t	i;
	char	*b;

	b = (char *)s;
	i = 0;
	while (i < n)
	{
		b[i] = c;
		i++;
	}
	return (s);
}
