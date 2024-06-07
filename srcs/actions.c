/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kammi <kammi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:39:46 by kammi             #+#    #+#             */
/*   Updated: 2024/06/07 17:41:41 by kammi            ###   ########.fr       */
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
		if (table->dead)
			break ;
		usleep(100);
	}
}
void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_msg(philo, FORK);
	pthread_mutex_lock(philo->fork_right);
	print_msg(philo, FORK);
	if (philo->table->dead)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return;
	}
	print_msg(philo, EAT);
	pthread_mutex_lock(&philo->table->m_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->m_last_meal);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (!philo->table->dead)
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
	if (philo->table->dead)
		return;
	print_msg(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}



void	thinking(t_philo *philo)
{
	size_t	time_to_think;
	size_t	temp;

	if (philo->table->dead)
		return;
	pthread_mutex_lock(&philo->table->m_last_meal);
	time_to_think = (philo->table->time_to_die);
	temp = ((get_time() - philo->last_meal) + philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->m_last_meal);
	if (temp >= time_to_think)
		time_to_think = 0;
	else
	{
		time_to_think -= temp;
		time_to_think /= 2;
		if (time_to_think > 500)
			time_to_think = 150;
	}
	print_msg(philo, THINK);
	ft_usleep(time_to_think, philo->table);
	return ;
}

// void	thinking(t_philo *philo)
// {
// 	size_t	time_to_think;
// 	size_t	last_meal_interval;

// 	if (philo->table->dead)
// 		return;
// 	pthread_mutex_lock(&philo->table->m_last_meal);
// 	last_meal_interval = get_time() - philo->last_meal;
// 	time_to_think = philo->table->time_to_die - last_meal_interval - philo->table->time_to_eat / 2;
// 	pthread_mutex_unlock(&philo->table->m_last_meal);
// 	if (time_to_think < 0)
// 		time_to_think = 0;
// 	else if (time_to_think > 500)
// 		time_to_think = 150;
// 	print_msg(philo, THINK);
// 	ft_usleep(time_to_think, philo->table);
// 	return ;

// }

// void	thinking(t_philo *philo)
// {
//     size_t	time_to_think = THINKING_TIME; // Définir une constante THINKING_TIME

//     if (philo->table->dead)
//         return;

//     print_msg(philo, THINK);
//     ft_usleep(time_to_think, philo->table);
//     return ;
// }
