/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:55:24 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/20 19:28:17 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void print_actual_time(int long init, pthread_mutex_t *print_lock);
void*	philo_routine(void *args);
long init_time (void)
{
	struct timeval tv;
	struct timezone tz;
	long init;

	gettimeofday(&tv,&tz);
	init = tv.tv_sec * 1000000 + tv.tv_usec;
	return (init);
}
int	main(int argc, char **argv)
{
	int long init;
	t_ph_status	**ph_stats;
	int i;

	(void)argc;
	init = init_time();
	ph_stats = init_ph_stats(argv, init);
	i = -1;
	while (++i < ph_stats[0]->total_ph)
		pthread_create(&ph_stats[i]->pthread_ph, NULL, &philo_routine, ph_stats[i]);
	i = -1;
	while (++i < ph_stats[0]->total_ph)
		pthread_join(ph_stats[i]->pthread_ph, NULL);
	return(0);
}

void*	philo_routine(void *args)
{
	int long	init;
	long	dif;
	t_ph_status	*ph_stats;

	ph_stats = (t_ph_status *) args;
	init = ph_stats->init;
	(void)init;
	while (1)
	{
		if (ph_stats->id % 2)
		{
			pthread_mutex_lock(ph_stats->right_fork);
			pthread_mutex_lock(ph_stats->print_lock);
			print_actual_time(init, ph_stats->print_lock);
			printf("philo %d pegou um garfo\n", ph_stats->id);
			pthread_mutex_unlock(ph_stats->print_lock);
			pthread_mutex_lock(ph_stats->left_fork);
			pthread_mutex_lock(ph_stats->print_lock);
			print_actual_time(init, ph_stats->print_lock);
			dif = current_time(init) - ph_stats->lst_philos_meal;
			printf("philo %d pegou segundo garfo  e iniciou a comer após %ld ms de jejum\n", ph_stats->id, dif);
			pthread_mutex_unlock(ph_stats->print_lock);
			usleep(ph_stats->t_eat);
			pthread_mutex_unlock(ph_stats->right_fork);
			pthread_mutex_unlock(ph_stats->left_fork);
		}
		else
		{
			pthread_mutex_lock(ph_stats->left_fork);
			pthread_mutex_lock(ph_stats->print_lock);
			print_actual_time(init, ph_stats->print_lock);
			printf("philo %d pegou um garfo\n", ph_stats->id);
			pthread_mutex_unlock(ph_stats->print_lock);
			pthread_mutex_lock(ph_stats->right_fork);
			pthread_mutex_lock(ph_stats->print_lock);
			print_actual_time(init, ph_stats->print_lock);
			dif = current_time(init) - ph_stats->lst_philos_meal;
			printf("philo %d pegou segundo garfo  e iniciou a comer após %ld ms de jejum\n", ph_stats->id, dif);
			pthread_mutex_unlock(ph_stats->print_lock);
			usleep(ph_stats->t_eat);
			pthread_mutex_unlock(ph_stats->left_fork);
			pthread_mutex_unlock(ph_stats->right_fork);
		}
		ph_stats->lst_philos_meal = current_time(init);
		ph_stats->n_eat++;
		pthread_mutex_lock(ph_stats->print_lock);
		print_actual_time(init, ph_stats->print_lock);
		printf("philo %d dormindo por 200ms\n", ph_stats->id);
		pthread_mutex_unlock(ph_stats->print_lock);
		//write(1, " dormindo por 200ms\n", 21);
		//printf("dormindo por 200ms\n");
		usleep(ph_stats->t_sleep);
		pthread_mutex_lock(ph_stats->print_lock);
		print_actual_time(init, ph_stats->print_lock);
		printf("philo %d pensando\n", ph_stats->id);
		pthread_mutex_unlock(ph_stats->print_lock);
		//write(1, " pensando por 200ms\n", 21);
		//printf("pensando por 200ms\n");
		//usleep(200000);
	}
	return(NULL);
}

long	current_time(long init)
{
	struct timeval tv;
	struct timezone tz;
	long now;
	long diff;

	gettimeofday(&tv, &tz);
	now = tv.tv_sec * 1000000 + tv.tv_usec;
	diff = (now - init)/1000;
	return (diff);
}

void print_actual_time(int long init, pthread_mutex_t *print_lock)
{
	long diff;
	(void) print_lock;

	diff = current_time(init);
	printf("ms: %ld ",diff);
	//pthread_mutex_unlock(print_lock);
	// write(1, "ms: ", 4);
	// write(1, str_diff, ft_strlen(str_diff));
}