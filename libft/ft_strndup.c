/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:17:56 by engiusep          #+#    #+#             */
/*   Updated: 2025/07/23 14:18:06 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int size)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(size * sizeof(char) + 1);
	if (!new)
		return (NULL);
	while (i < size)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}