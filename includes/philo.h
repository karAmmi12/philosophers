/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:15:17 by kammi             #+#    #+#             */
/*   Updated: 2024/06/27 14:18:29 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

/*******************************STRUCT************************************/

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_table
{
	t_philo				*philos;
	pthread_t			death_thread;
	pthread_mutex_t		*forks;
	pthread_mutex_t		m_dead;
	pthread_mutex_t		m_count_meal;
	pthread_mutex_t		m_print;
	pthread_mutex_t		m_last_meal;
	size_t				nbr_philos;
	size_t				start_time;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				nbr_must_eat;
	int					dead;
}						t_table;

typedef struct s_philo
{
	size_t				id;
	size_t				position;
	pthread_t			thread;
	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*fork_right;
	long long			last_meal;
	t_table				*table;
	size_t				count_meal;
}						t_philo;

enum
{
	EAT = 1,
	SLEEP = 2,
	THINK = 3,
	DEAD = 4,
	FORK = 5
};

/*******************************COLOR************************************/
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

/*******************************LIBFT************************************/

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
long	ft_atol(const char *str, int *err);

/*******************************INIT************************************/
int		init_table(t_table *table);
void	philo_forks_init(t_philo *philo, size_t i);
int		init_forks(t_table *table);
int		init_philos(t_table *table);
int		init_mutex(t_table *table);

/*******************************PARSER************************************/
int		parser(int ac, char **av, t_table *table);
int		check_args(int ac, char **av);

/*******************************PHILO************************************/
int		start_simulation(t_table *table);
void	*philo_routine(void *arg);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

void	set_death(t_table *table);
int		death(t_table *table);
int		handle_end(t_table *table);
void	*death_monitor(void *arg);
int		check_death(t_philo *philo);

/********************************UTILS************************************/

void	wait_all_philos(size_t time_start);
size_t	get_time(void);
void	ft_usleep(size_t time, t_table *table);
void	print_msg(t_philo *philo, int msg);
void	cleaning(t_table *table);

#endif
