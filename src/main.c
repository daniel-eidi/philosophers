/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:55:24 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/20 14:54:01 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void print_actual_time(int long init, pthread_mutex_t *print_lock);
void*	philo_routine(void *args);
t_ph_status	**init_ph_stats(int n_philo, long init);

int main (void)
{
	struct timeval tv;
	struct timezone tz;
	// pthread_t philo1;
	// pthread_t philo2;
	int long init;
	long end;
	long diff;
	t_ph_status	**ph_stats;
	//char *str_diff;

	gettimeofday(&tv,&tz);
	init = tv.tv_sec * 1000000 + tv.tv_usec;

	//philo_routine(ph_stats->init);
	
	ph_stats = init_ph_stats(2, init);
	printf("&ph_stats[0]->print_lock = %p\n", ph_stats[0]->print_lock);
	printf("&ph_stats[1]->print_lock = %p\n", ph_stats[1]->print_lock);
	pthread_create(&ph_stats[0]->pthread_ph, NULL, &philo_routine, ph_stats[0]);
	pthread_create(&ph_stats[1]->pthread_ph, NULL, &philo_routine, ph_stats[1]);
	pthread_join(ph_stats[0]->pthread_ph, NULL);
	pthread_join(ph_stats[1]->pthread_ph, NULL);
	gettimeofday(&tv,&tz);
	end = tv.tv_sec * 1000000 + tv.tv_usec;
	diff = (end - init)/1000;
	//printf("ms: %ld -----fim-------\n",diff);
	//str_diff = ft_itoa(diff);
	printf("ms: %ld\n ",diff);
	//write(1, "ms: ", 4);
	//write(1, str_diff, ft_strlen(str_diff));

	return(0);
}

t_ph_status	**init_ph_stats(int n_philo, long init)
{
	t_ph_status	**ph_stats;
	int i;
	pthread_mutex_t *print_lock;

	i = 0;
	print_lock = malloc (sizeof(pthread_mutex_t));
	pthread_mutex_init(print_lock, NULL);
	ph_stats = calloc(sizeof(t_ph_status *), 1);
	while (i < n_philo)
	{
		ph_stats[i] = calloc(sizeof(t_ph_status), 1);
		ph_stats[i]->init = init;
		ph_stats[i]->lst_philos_meal = init;
		ph_stats[i]->id = i + 1;
		ph_stats[i]->print_lock = print_lock;
		i++;
	}
	ph_stats[i] = calloc(sizeof(t_ph_status), 1);
	return(ph_stats);
}

void*	philo_routine(void *args)
{
	int long	init;
	t_ph_status	*ph_stats;

	ph_stats = (t_ph_status *) args;
	init = ph_stats->init;
	(void)init;
	while (1)
	{
		pthread_mutex_lock(ph_stats->print_lock);
		print_actual_time(init, ph_stats->print_lock);
		printf("philo %d comendo por 200ms\n", ph_stats->id);
		pthread_mutex_unlock(ph_stats->print_lock);
		//write(1, " comendo por 200ms\n", 20);
		//printf("comendo por 200ms\n");
		usleep(200000);
		pthread_mutex_lock(ph_stats->print_lock);
		print_actual_time(init, ph_stats->print_lock);
		printf("philo %d dormindo por 200ms\n", ph_stats->id);
		pthread_mutex_unlock(ph_stats->print_lock);
		//write(1, " dormindo por 200ms\n", 21);
		//printf("dormindo por 200ms\n");
		usleep(200000);
		pthread_mutex_lock(ph_stats->print_lock);
		print_actual_time(init, ph_stats->print_lock);
		printf("philo %d pensando por 200ms\n", ph_stats->id);
		pthread_mutex_unlock(ph_stats->print_lock);
		//write(1, " pensando por 200ms\n", 21);
		//printf("pensando por 200ms\n");
		usleep(200000);
	}
	return(NULL);
}

void print_actual_time(int long init, pthread_mutex_t *print_lock)
{
	struct timeval tv;
	struct timezone tz;
	long now;
	long diff;
	//char *str_diff;
	(void) print_lock;

	gettimeofday(&tv,&tz);
	now = tv.tv_sec * 1000000 + tv.tv_usec;
	diff = (now - init)/1000;
	//str_diff = ft_itoa(diff);
	//pthread_mutex_unlock(print_lock);
	printf("ms: %ld ",diff);
	//pthread_mutex_unlock(print_lock);
	// write(1, "ms: ", 4);
	// write(1, str_diff, ft_strlen(str_diff));
}