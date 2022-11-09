#include <philosophers.h>

int	death_monitor(t_ph_status	**ph_stats)
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
			//free_ph_stats(ph_stats);
			*ph_stats[i]->exit = 1;
			return (1);
		}
		i++;
	}
	return(0);
}

int	max_meal(t_ph_status	**ph_stats)
{
	int		i;
	int		count_ph;

	i = 0;
	count_ph = 0;
	while(i < ph_stats[0]->total_ph)
	{
		if(ph_stats[i]->n_eat >= ph_stats[i]->max_eat \
		&& ph_stats[i]->max_eat > 0)
			count_ph++;
		i++;
	}
	if(count_ph == ph_stats[0]->total_ph)
	{
		pthread_mutex_lock(ph_stats[0]->print_lock);
		*ph_stats[0]->exit = 1;
		return (1);
	}
	return (0);
}

void	*thread_monitor(void *args)
{
	t_ph_status	**ph_stats;

	ph_stats = (t_ph_status **) args;
	pthread_mutex_lock(ph_stats[0]->print_lock);
	pthread_mutex_unlock(ph_stats[0]->print_lock);
	while (1)
	{
		if(death_monitor(ph_stats) || max_meal(ph_stats))
			return (NULL);
	}
}