/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:04:59 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/28 16:54:56 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

long	now(long init)
{
	struct timeval	tv;
	struct timezone	tz;
	long			now;
	long			diff;

	gettimeofday(&tv, &tz);
	now = tv.tv_sec * 1000000 + tv.tv_usec;
	diff = (now - init) / 1000;
	return (diff);
}

void	print_actual_time(int long init)
{
	long	diff;

	diff = now(init);
	printf("ms: %ld ", diff);
}
