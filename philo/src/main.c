/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:55:24 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/28 16:53:41 by daeidi-h         ###   ########.fr       */
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
		dif = current_time(ph_stats[i]->init) - ph_stats[i]->lst_philos_meal;
		if (dif > (ph_stats[i]->t_die / 1000))
		{
			pthread_mutex_lock(ph_stats[i]->print_lock);
			print_actual_time(ph_stats[i]->init);
			printf("philo %d com %ld de jejum morreu \n\n\n\n\n\n\n", \
					ph_stats[i]->id, dif);
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
	i = -1;
	while (++i < ph_stats[0]->total_ph)
		pthread_create(&ph_stats[i]->pthread_ph, \
					NULL, &philo_routine, ph_stats[i]);
	pthread_create(&monitor, NULL, &thread_monitor, ph_stats);
	i = -1;
	while (++i < ph_stats[0]->total_ph)
		pthread_join(ph_stats[i]->pthread_ph, NULL);
	pthread_join(monitor, NULL);
	return (0);
}
