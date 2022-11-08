/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:13:29 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/11/08 17:45:10 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include<philosophers.h>

void	free_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_ptr_ptr(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free_ptr((void *) &ptr[i++]);
}

void	free_ph_stats(t_ph_status	**ph_stats)
{
	pthread_mutex_t	**forks;
	int i;
 	int n_philo;

	i = 0;
	n_philo = ph_stats[0]->total_ph;
	pthread_mutex_destroy(ph_stats[0]->print_lock);
	free_ptr((void *) &ph_stats[0]->print_lock);
	//pthread_detach(ph_stats[0]->monitor);
	// free_ptr((void *) &ph_stats[0]->monitor);
	forks = ph_stats[0]->forks;
	while (i < n_philo)
	{
		pthread_mutex_destroy(ph_stats[i]->left_fork);
		free_ptr((void *) &ph_stats[i]->left_fork);
		//pthread_detach(ph_stats[i]->pthread_ph);
		//free(&ph_stats[i]->pthread_ph);
		free_ptr((void *) &ph_stats[i]);
		i++;
	}
	free_ptr((void *) &forks);
	free_ptr((void *)&ph_stats);
}
