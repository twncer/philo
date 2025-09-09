/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btuncer <btuncer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:51:44 by btuncer           #+#    #+#             */
/*   Updated: 2025/09/09 14:06:47 by btuncer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	convert_atoi(char *str, int sign_counter)
{
	int	res;

	res = 0;
	while (*str && (*str <= '9' && *str >= '0'))
	{
		res = res * 10;
		res = res + (*str - '0');
		str++;
	}
	if (sign_counter == -1)
		res = res * sign_counter;
	return (res);
}

int	issp(char c)
{
	if (c == 32 || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	sign_counter;

	sign_counter = 0;
	if (!*nptr)
		return (0);
	while (issp(*nptr))
		nptr++;
	while (!(*nptr <= '9' && *nptr >= '0') && *nptr)
	{
		if (*nptr == '-' || *nptr == '+')
			sign_counter++;
		else
			return (0);
		if (sign_counter > 1)
			return (0);
		nptr++;
	}
	if ((nptr - 1)[0] == '-')
		sign_counter = -1;
	return (convert_atoi((char *)nptr, sign_counter));
}
