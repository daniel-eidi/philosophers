/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:55:24 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/11/08 17:22:18 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

long	init_time(void)
{
	struct timeval		tv;
	struct timezone		tz;
	long				init;

	gettimeofday(&tv, &tz);
	init = tv.tv_sec * 1000000 + tv.tv_usec;
	return (init);
}

int	main(int argc, char **argv)
{
	long		init;
	t_ph_status	**ph_stats;
	int			i;

	(void)argc;
	init = init_time();
	ph_stats = init_ph_stats(argv, init);
	pthread_create(&ph_stats[0]->pthread_ph, \
					NULL, &philo_routine, ph_stats[0]);
	i = 0;
	while (++i < ph_stats[0]->total_ph)
	{
		usleep(1000);
		pthread_create(&ph_stats[i]->pthread_ph, \
					NULL, &philo_routine, ph_stats[i]);
	}
	pthread_create(&ph_stats[0]->monitor, NULL, &thread_monitor, ph_stats);
	i = -1;
	while (++i < ph_stats[0]->total_ph)
		pthread_join(ph_stats[i]->pthread_ph, NULL);
	pthread_join(ph_stats[0]->monitor, NULL);
	return (0);
}
