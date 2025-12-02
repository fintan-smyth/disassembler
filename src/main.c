/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:32:25 by fsmyth            #+#    #+#             */
/*   Updated: 2025/12/01 15:55:30 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassemble.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

uint8_t	*read_input_file(char *filename, uint64_t *size)
{
	struct stat 	statbuf;
	uint8_t			*data;

	int retval = stat(filename, &statbuf);
	if (retval != EXIT_SUCCESS)
		return (perror(filename), NULL);

	*size = statbuf.st_size;
	data = malloc(*size);
	if (data == NULL)
		return (perror("malloc"), NULL);

	int	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror(filename), NULL);

	retval = read(fd, data, *size);
	close(fd);
	return (data);
}

int	main(void)
{
	// uint8_t	bytes[] = {
	// 	0x31, 0xed,
	// 	0x49, 0x89, 0xd1,
	// 	0x5e,
	// 	0x48, 0x89, 0xe2,
	// 	0x48, 0x83, 0xe4, 0xf0,
	// 	0x50,
	// 	0x54,
	// 	0x45, 0x31, 0xc0,
	// 	0x31, 0xc9,
	// 	0x48, 0x8d, 0x3d, 0xed, 0x02, 0x00, 0x00,
	// 	0xff, 0x15, 0xdb, 0x8b, 0x00, 0x00,
	// 	0x55,
	// 	0x48, 0x89, 0xe5,
	// 	0x48, 0x8d, 0x05, 0x40, 0x5b, 0x00, 0x00,
	// 	0x48, 0x89, 0xc6,
	// 	0xbf, 0x06, 0x00, 0x00, 0x00,
	// 	0x89, 0xbd, 0x2c, 0xfe, 0xff, 0xff,
	// };

	uint64_t	size;
	uint8_t		*data = read_input_file("/home/fintan/fortytwo/nchex/nchex", &size);

	printf("START:\n");
	print_disassembly(1, data, 0x23c0, 0x24b9);

	printf("\nINIT_NCURSES:\n");
	print_disassembly(1, data, 0x24b9, 0x2669);

	printf("\nDEINIT_NCURSES:\n");
	print_disassembly(1, data, 0x2669, 0x267f);

	printf("\ncleanup\n");
	print_disassembly(1, data, 0x267f, 0x26cc);

	printf("\nMAIN:\n");
	print_disassembly(1, data, 0x26cc, 0x2936);

	// uint64_t	size;
	// uint8_t		*data = read_input_file("/home/fsmyth/projects/nchex/nchex", &size);
	//
	// printf("START:\n");
	// print_disassembly(1, data, 0x2360, 120);
	//
	// printf("\nINIT_NCURSES:\n");
	// print_disassembly(1, data, 0x2450, 20);
	//
	// printf("\nMAIN:\n");
	// print_disassembly(1, data, 0x2640, 30);
	//
	// printf("\nINIT_BYTECOLS:\n");
	// print_disassembly(1, data, 0x2cd0, 300);
}
