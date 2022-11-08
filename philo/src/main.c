/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:55:24 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/11/08 11:04:00 by daeidi-h         ###   ########.fr       */
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

void	death_monitor(t_ph_status	**ph_stats)
{
	int		i;
	long	dif;

	i = 0;
	dif = 0;
	while (i < ph_stats[0]->total_ph)
	{
		dif = now(ph_stats[i]->init) - ph_stats[i]->lst_philos_meal;
		if (dif > (ph_stats[i]->t_die / 1000))
		{
			pthread_mutex_lock(ph_stats[i]->print_lock);
			printf("%ld %d died \
			after %ld ms de jejum\n", now(ph_stats[i]->init), ph_stats[i]->id, dif);
			free_ph_stats(ph_stats);
			exit(0);
		}
		i++;
	}
}

void	*thread_monitor(void *args)
{
	t_ph_status	**ph_stats;

	ph_stats = (t_ph_status **) args;
	pthread_mutex_lock(ph_stats[0]->print_lock);
	pthread_mutex_unlock(ph_stats[0]->print_lock);
	while (1)
		death_monitor(ph_stats);
}

int	main(int argc, char **argv)
{
	long		init;
	t_ph_status	**ph_stats;
	int			i;
	pthread_t	monitor;

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
	pthread_create(&monitor, NULL, &thread_monitor, ph_stats);
	i = -1;
	while (++i < ph_stats[0]->total_ph)
		pthread_join(ph_stats[i]->pthread_ph, NULL);
	pthread_join(monitor, NULL);
	return (0);
}
