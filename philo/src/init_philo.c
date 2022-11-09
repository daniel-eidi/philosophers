/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:45:40 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/11/09 17:42:36 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

pthread_mutex_t	**init_forks(int n_philo)
{
	pthread_mutex_t	**forks;
	int				i;

	i = 0;
	forks = calloc(sizeof(pthread_mutex_t *), n_philo + 1);
	while (i < n_philo)
	{
		forks[i] = calloc(sizeof(pthread_mutex_t), 1);
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
	forks[i] = NULL;
	return (forks);
}

void	init_philo(t_ph_status **ph_stats, int i, char **argv, long init)
{
	ph_stats[i] = calloc(sizeof(t_ph_status), 1);
	ph_stats[i]->init = init;
	ph_stats[i]->lst_philos_meal = 0;
	ph_stats[i]->id = (i + 1);
	ph_stats[i]->t_die = ft_atoi(argv[2]) * 1000;
	ph_stats[i]->t_eat = ft_atoi(argv[3]) * 1000;
	ph_stats[i]->t_sleep = ft_atoi(argv[4]) * 1000;
	ph_stats[i]->max_eat = -1;
	if (argv[5])
		ph_stats[i]->max_eat = ft_atoi(argv[5]);
	ph_stats[i]->n_eat = 0;
}

void	init_philo_forks(t_ph_status	**ph_stats, int i, \
						pthread_mutex_t **forks, int n_philo)
{
	ph_stats[i]->total_ph = n_philo;
	ph_stats[i]->forks = forks;
	ph_stats[i]->left_fork = forks[i];
	if (i + 1 == n_philo)
		ph_stats[i]->right_fork = forks[0];
	else
		ph_stats[i]->right_fork = forks[i + 1];
}

static void	malloc_exit_status(t_ph_status	**ph_stats)
{
	int *exit;
	int	i;

	exit = (int *)malloc(sizeof(int));

	*exit = 0;
	i = -1;
	while (ph_stats[++i])
		ph_stats[i]->exit = exit;
}

t_ph_status	**init_ph_stats(char **argv, long init)
{
	t_ph_status		**ph_stats;
	int				i;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	**forks;
	int				n_philo;

	n_philo = ft_atoi(argv[1]);
	print_lock = malloc (sizeof(pthread_mutex_t));
	pthread_mutex_init(print_lock, NULL);
	forks = init_forks (n_philo);
	ph_stats = calloc(sizeof(t_ph_status *), n_philo + 1);
	i = 0;
	while (i < n_philo)
	{
		init_philo(ph_stats, i, argv, init);
		init_philo_forks(ph_stats, i, forks, n_philo);
		ph_stats[i]->print_lock = print_lock;
		i++;
	}
	ph_stats[i] = NULL;
	malloc_exit_status(ph_stats);
	return (ph_stats);
}
