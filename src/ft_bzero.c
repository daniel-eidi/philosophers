/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:17:55 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/20 08:57:53 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

/**
 * @brief function erases the data in the n bytes of the memory
 * starting at the location pointed to by s, by writing zeros 
 * (bytes containing '\0') to * that area
 * 
 * @param s location pointer
 * @param n num of bytes to put '\0'
 */
void	ft_bzero(void *s, size_t n)
{
	ft_memset (s, '\0', n);
}
