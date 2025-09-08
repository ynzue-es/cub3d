/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_digit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:18:16 by engiusep          #+#    #+#             */
/*   Updated: 2025/09/08 14:49:29 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	line_isdigit(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_isdigit(line[i]) == 1)
		return (1);
	return (0);
}
