/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:39:46 by kammi             #+#    #+#             */
/*   Updated: 2024/06/27 12:21:19 by kammi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t time, t_table *table)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (death(table))
			break ;
		// if (time - (get_time() - start) < 500)
		// 	usleep(time - (get_time() - start));
		// else
		usleep(500);
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_msg(philo, FORK);
	pthread_mutex_lock(philo->fork_right);
	print_msg(philo, FORK);
	if (death(philo->table))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return ;
	}
	print_msg(philo, EAT);
	pthread_mutex_lock(&philo->table->m_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->m_last_meal);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (!death(philo->table))
	{
		pthread_mutex_lock(&philo->table->m_count_meal);
		philo->count_meal++;
		pthread_mutex_unlock(&philo->table->m_count_meal);
	}
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
}

void	sleeping(t_philo *philo)
{
	if (death(philo->table))
		return ;
	print_msg(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

void	thinking(t_philo *philo)
{
	size_t	time_to_think;

	if (death(philo->table))
		return ;
	print_msg(philo, THINK);
	if (philo->table->nbr_philos % 2 == 0)
		return ;
	else if (philo->table->time_to_sleep > philo->table->time_to_eat)
		return ;
	else
		time_to_think = 100;
	ft_usleep(time_to_think, philo->table);
}
