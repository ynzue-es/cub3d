/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_pixel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:05:42 by yannis            #+#    #+#             */
/*   Updated: 2025/09/09 10:47:18 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	hex_char_to_int(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

int	hex_to_int(char *hex_str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (hex_str[i])
	{
		result = result * 16 + hex_char_to_int(hex_str[i]);
		i++;
	}
	return (result);
}

int	size_hex(int n)
{
	int	size;

	size = 0;
	while (n > 0)
	{
		n = n / 16;
		size++;
	}
	size++;
	return (size);
}

char	*switch_hex(int n)
{
	char	*hex;
	char	*base;
	int		i;
	int		size;

	base = "0123456789abcdef";
	size = size_hex(n);
	hex = malloc(size);
	if (!hex)
		return (NULL);
	i = 0;
	while (n > 0)
	{
		hex[i] = (base[n % 16]);
		n = n / 16;
		i++;
	}
	hex[i] = '\0';
	return (hex);
}

int	switch_tab_int(t_data_game *data_game, int flag_ceil_floor)
{
	char	*str[3];
	char	*new;
	char	*new2;
	int		result;
	int		i;

	i = 0;
	if (convert_hex(str, flag_ceil_floor, data_game) == -1)
		return (free_tab(str), -1);
	new = ft_strjoin(str[0], str[1]);
	if (!new)
		return (-1);
	new2 = ft_strjoin(new, str[2]);
	if (!new2)
	{
		free(new);
		return (-1);
	}
	result = hex_to_int(new2);
	while (i < 3)
		free(str[i++]);
	free(new);
	free(new2);
	return (result);
}
