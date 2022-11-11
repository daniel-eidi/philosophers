/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:56:20 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/11/11 16:06:36 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	exit_or_mutex_print(t_ph_status *ph_stats)
{
	if (*ph_stats->exit != 0)
	{
		pthread_mutex_unlock(ph_stats->left_fork);
		pthread_mutex_unlock(ph_stats->right_fork);
		return (1);
	}
	return (0);
}

static void	get_fork(t_ph_status *ph_stats)
{
	long	dif;

	pthread_mutex_lock(ph_stats->left_fork);
	if (exit_or_mutex_print(ph_stats))
		return ;
	printf("%ld %d has taken a fork\n", now(ph_stats->init), ph_stats->id);
	pthread_mutex_unlock(ph_stats->print_lock);
	if (ph_stats->total_ph > 1)
	{
		pthread_mutex_lock(ph_stats->right_fork);
		dif = now(ph_stats->init) - ph_stats->lst_philos_meal;
		if (dif > (ph_stats->t_die / 1000))
			return ;
		if (exit_or_mutex_print(ph_stats))
			return ;
		printf("%ld %d is eating\n", now(ph_stats->init), ph_stats->id);
		pthread_mutex_unlock(ph_stats->print_lock);
		ph_stats->lst_philos_meal = now(ph_stats->init);
		usleep(ph_stats->t_eat);
		pthread_mutex_unlock(ph_stats->left_fork);
		pthread_mutex_unlock(ph_stats->right_fork);
	}
	else
		usleep(ph_stats->t_die + 1000);
}

void	*philo_routine(void *args)
{
	t_ph_status	*ph_stats;

	ph_stats = (t_ph_status *) args;
	while (1)
	{
		get_fork(ph_stats);
		ph_stats->n_eat++;
		if (exit_or_mutex_print(ph_stats))
			return (NULL);
		printf("%ld %d has taken a fork\n", now(ph_stats->init), ph_stats->id);
		pthread_mutex_unlock(ph_stats->print_lock);
		usleep(ph_stats->t_sleep);
		if (exit_or_mutex_print(ph_stats))
			return (NULL);
		printf("%ld %d is thinkng\n", now(ph_stats->init), ph_stats->id);
		pthread_mutex_unlock(ph_stats->print_lock);
	}
	return (NULL);
}
