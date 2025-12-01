/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:32:24 by fsmyth            #+#    #+#             */
/*   Updated: 2025/12/01 12:33:19 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	src_len = strlen(src);
	dst_len = strlen(dst);
	i = 0;
	while (dst[i] != 0)
	{
		i++;
	}
	if (n <= i)
		return (src_len + n);
	j = 0;
	while (src[j] != 0 && i < n - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = 0;
	return (src_len + dst_len);
}
