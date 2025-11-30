/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:32:25 by fsmyth            #+#    #+#             */
/*   Updated: 2025/11/30 14:32:57 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassemble.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	t_state		state = {};
	t_optrie	*root = calloc(1, sizeof(*root));
	t_optrie	*curr_op;

	build_optrie(root);
	uint64_t	i = 0;
	uint64_t	instruction_start;
	uint8_t	bytes[] = {
		0x31, 0xed,
		0x49, 0x89, 0xd1,
		0x5e,
		0x48, 0x89, 0xe2,
		0x48, 0x83, 0xe4, 0xf0,
		0x50,
		0x54,
		0x45, 0x31, 0xc0,
		0x31, 0xc9,
	};

	while (i < sizeof(bytes))
	{
		instruction_start = i;
		reset_state(&state);
		i = parse_prefix_bytes(&state, bytes, i);
		curr_op = optrie_search(root, bytes, &i);
		if (curr_op == NULL)
			return (printf("op not found\n"), 1);

		state.flags |= curr_op->flags;
		if (state.flags & REG_CODE)
			parse_reg_code(&state, bytes[i - 1]);
		if (state.flags & MODRM)
			parse_modrm_byte(&state, bytes[i++], &curr_op);
		if (state.flags & SIB)
			parse_sib_byte(&state, bytes[i++]);
		if (state.flags & IMM_MASK)
			i = parse_imm_value(&state, bytes, i);

		state.operation = curr_op->name;
		printf("%16zx:\t%s\t%s,%s\n", instruction_start + 0x2384, state.operation, state.operand2, state.operand1);
	}
}
