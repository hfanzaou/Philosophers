/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfanzaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 03:18:00 by hfanzaou          #+#    #+#             */
/*   Updated: 2022/09/04 04:11:29 by hfanzaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_isdigit(int c)
{
	if (!(c >= 48 && c <= 57))
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	long long int	r;
	int				s;

	r = 0;
	s = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			s *= -1;
	while (*str >= '0' && *str <= '9' && *str)
	{
		if (r > 2147483647 && s > 0)
			return (-1);
		if (-r < -2147483648 && s < 0)
			return (0);
		r = r * 10 + (*str++ - 48);
	}
	return (r * s);
}
