/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:55:24 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/26 20:02:26 by daeidi-h         ###   ########.fr       */
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

void death_monitor (t_ph_status	**ph_stats)
{
	int	i;
	long dif;

	i = 0;
	dif = 0;
	

	while (i < ph_stats[0]->total_ph)
	{
		dif = current_time(ph_stats[i]->init) - ph_stats[i]->lst_philos_meal;
		if(dif > (ph_stats[i]->t_die/1000))
		{
			pthread_mutex_lock(ph_stats[i]->print_lock);
			print_actual_time(ph_stats[i]->init, ph_stats[i]->print_lock);
			printf("philo %d com %ld de jejum entrou na morte ?????????????????\n\n\n\n\n\n\n", ph_stats[i]->id, dif);
			exit(0); //colocar os frees
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
void *thread_main(void *args)
{
	t_ph_status	**ph_stats;
	int			i;

	ph_stats = (t_ph_status	**)args;
	i = -1;
	while (++i < ph_stats[0]->total_ph)
		pthread_create(&ph_stats[i]->pthread_ph, NULL, &philo_routine, ph_stats[i]);
	i = -1;
	while (++i < ph_stats[0]->total_ph)
		pthread_join(ph_stats[i]->pthread_ph, NULL);
	return (NULL);
}

int	main(int argc, char **argv)
{
	long init;
	t_ph_status	**ph_stats;
	//int i;
	pthread_t	monitor;
	pthread_t	main_thread;

	(void)argc;
	init = init_time();
	ph_stats = init_ph_stats(argv, init);
	// i = -1;
	// while (++i < ph_stats[0]->total_ph)
	// 	pthread_create(&ph_stats[i]->pthread_ph, NULL, &philo_routine, ph_stats[i]);
	pthread_create(&main_thread, NULL, &thread_main, ph_stats);
	pthread_create(&monitor, NULL, &thread_monitor, ph_stats);
	// i = -1;
	// while (++i < ph_stats[0]->total_ph)
	// 	pthread_join(ph_stats[i]->pthread_ph, NULL);
	pthread_join(main_thread, NULL);
	pthread_join(monitor, NULL);
	
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
			if (dif > (ph_stats->t_die/1000))
				printf("philo %d com %ld de jejum morreuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n\n\n\n\n", ph_stats->id, dif);
			else
				printf("philo %d pegou segundo garfo  e iniciou a comer após %ld ms de jejum\n", ph_stats->id, dif);			
			pthread_mutex_unlock(ph_stats->print_lock);
			ph_stats->lst_philos_meal = current_time(init);
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
			ph_stats->lst_philos_meal = current_time(init);
			usleep(ph_stats->t_eat);
			pthread_mutex_unlock(ph_stats->left_fork);
			pthread_mutex_unlock(ph_stats->right_fork);
		}
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