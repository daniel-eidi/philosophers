/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:32:00 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/11/10 15:48:35 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// -----------------	ALLOWED LIBS	----------------
# include <pthread.h> // threads and mutexes functions
# include <stdio.h> // printf()
# include <unistd.h> // usleep()
# include <stdlib.h> // malloc(), free()
# include <sys/time.h> // gettimeofday()
# include <stdbool.h> // bool typedef

typedef struct s_philos_status
{
	int				id;
	pthread_t		monitor;
	pthread_t		pthread_ph;
	long			init;
	long			lst_philos_meal;
	int				changed_status;
	int				status;
	int				total_ph;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_eat;
	int				n_eat;
	int				*exit;
	pthread_mutex_t	**forks;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_lock;
}	t_ph_status;

int					ft_isdigit(int c);
int					ft_atoi(const char *str);
long long			ft_atol(const char *str);
char				*ft_itoa(long n);
void				*ft_calloc(size_t nmemb, size_t size);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);

pthread_mutex_t		**init_forks(int n_philo);
t_ph_status			**init_ph_stats(char **argv, long init);
long				now(long init);
void				*philo_routine(void *args);
void				print_actual_time(int long init);
void				*thread_monitor(void *args);

void				free_ph_stats(t_ph_status	**ph_stats);

#endif