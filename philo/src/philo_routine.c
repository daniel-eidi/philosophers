/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:56:20 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/28 16:58:44 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	get_fork_uneven(t_ph_status	*ph_stats)
{
	long	dif;

	pthread_mutex_lock(ph_stats->right_fork);
	pthread_mutex_lock(ph_stats->print_lock);
	print_actual_time(ph_stats->init);
	printf("philo %d pegou um garfo\n", ph_stats->id);
	pthread_mutex_unlock(ph_stats->print_lock);
	pthread_mutex_lock(ph_stats->left_fork);
	pthread_mutex_lock(ph_stats->print_lock);
	print_actual_time(ph_stats->init);
	dif = current_time(ph_stats->init) - ph_stats->lst_philos_meal;
	if (dif <= (ph_stats->t_die / 1000))
		printf("philo %d pegou segundo garfo  \
		e iniciou a comer após %ld ms de jejum\n", ph_stats->id, dif);
	pthread_mutex_unlock(ph_stats->print_lock);
	ph_stats->lst_philos_meal = current_time(ph_stats->init);
	usleep(ph_stats->t_eat);
	pthread_mutex_unlock(ph_stats->right_fork);
	pthread_mutex_unlock(ph_stats->left_fork);
}

static void	get_fork_even(t_ph_status *ph_stats)
{
	long	dif;

	pthread_mutex_lock(ph_stats->left_fork);
	pthread_mutex_lock(ph_stats->print_lock);
	print_actual_time(ph_stats->init);
	printf("philo %d pegou um garfo\n", ph_stats->id);
	pthread_mutex_unlock(ph_stats->print_lock);
	pthread_mutex_lock(ph_stats->right_fork);
	pthread_mutex_lock(ph_stats->print_lock);
	print_actual_time(ph_stats->init);
	dif = current_time(ph_stats->init) - ph_stats->lst_philos_meal;
	if (dif > (ph_stats->t_die / 1000))
		return ;
	else
		printf("philo %d pegou segundo garfo  e \
		iniciou a comer após %ld ms de jejum\n", ph_stats->id, dif);
	pthread_mutex_unlock(ph_stats->print_lock);
	ph_stats->lst_philos_meal = current_time(ph_stats->init);
	usleep(ph_stats->t_eat);
	pthread_mutex_unlock(ph_stats->left_fork);
	pthread_mutex_unlock(ph_stats->right_fork);
	pthread_mutex_unlock(ph_stats->print_lock);
}

void	*philo_routine(void *args)
{
	t_ph_status	*ph_stats;

	ph_stats = (t_ph_status *) args;
	while (1)
	{
		if (ph_stats->id % 2)
			get_fork_uneven(ph_stats);
		else
			get_fork_even(ph_stats);
		ph_stats->n_eat++;
		pthread_mutex_lock(ph_stats->print_lock);
		print_actual_time(ph_stats->init);
		printf("philo %d dormindo por 200ms\n", ph_stats->id);
		pthread_mutex_unlock(ph_stats->print_lock);
		usleep(ph_stats->t_sleep);
		pthread_mutex_lock(ph_stats->print_lock);
		print_actual_time(ph_stats->init);
		printf("philo %d pensando\n", ph_stats->id);
		pthread_mutex_unlock(ph_stats->print_lock);
	}
	return (NULL);
}
