/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcodes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:57:06 by fsmyth            #+#    #+#             */
/*   Updated: 2025/11/30 19:54:08 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassemble.h"
#include <stdint.h>
#include <stdlib.h>

const t_opcode	ops[] = {
	{ .name = "xor",	.bytes = { 0x31 },		.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "push",	.bytes = { 0x50 },		.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "push",	.bytes = { 0x51 },		.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "push",	.bytes = { 0x52 },		.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "push",	.bytes = { 0x53 },		.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "push",	.bytes = { 0x54 },		.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "push",	.bytes = { 0x55 },		.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "push",	.bytes = { 0x56 },		.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "push",	.bytes = { 0x57 },		.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x58 },		.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x59 },		.n_bytes = 1, .flags = REG_CODE, 				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x5a },		.n_bytes = 1, .flags = REG_CODE, 				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x5b },		.n_bytes = 1, .flags = REG_CODE, 				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x5c },		.n_bytes = 1, .flags = REG_CODE, 				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x5d },		.n_bytes = 1, .flags = REG_CODE, 				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x5e },		.n_bytes = 1, .flags = REG_CODE, 				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x5f },		.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "add",	.bytes = { 0x81, 0 },	.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "or",		.bytes = { 0x81, 1 },	.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "adc",	.bytes = { 0x81, 2 },	.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "sbb",	.bytes = { 0x81, 3 },	.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "and",	.bytes = { 0x81, 4 },	.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "sub",	.bytes = { 0x81, 5 },	.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "xor",	.bytes = { 0x81, 6 },	.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "cmp",	.bytes = { 0x81, 7 },	.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "add",	.bytes = { 0x83, 0 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "or",		.bytes = { 0x83, 1 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "adc",	.bytes = { 0x83, 2 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "sbb",	.bytes = { 0x83, 3 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "and",	.bytes = { 0x83, 4 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "sub",	.bytes = { 0x83, 5 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "xor",	.bytes = { 0x83, 6 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "cmp",	.bytes = { 0x83, 7 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0x89 },		.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "lea",	.bytes = { 0x8d },		.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "mov",	.bytes = { 0xb0 },		.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb1 },		.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb2 },		.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb3 },		.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb4 },		.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb5 },		.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb6 },		.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb7 },		.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb8 },		.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb9 },		.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xba },		.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xbb },		.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xbc },		.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xbd },		.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xbe },		.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xbf },		.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "inc",	.bytes = { 0xff, 0 },	.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "dec",	.bytes = { 0xff, 1 },	.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "call",	.bytes = { 0xff, 2 },	.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "callf",	.bytes = { 0xff, 3 },	.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "jmp",	.bytes = { 0xff, 4 },	.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "jmpf",	.bytes = { 0xff, 5 },	.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "push",	.bytes = { 0xff, 6 },	.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
};

void	opcode_trie_insert(t_optrie *head, const t_opcode *opcode)
{
	uint8_t		i = 0;
	uint8_t		byte;
	t_optrie	*curr = head;

	while (i < opcode->n_bytes)
	{
		byte = opcode->bytes[i];
		if (curr->children[byte] == NULL)
			curr->children[byte] = calloc(1, sizeof(*curr));
		curr = curr->children[byte];
		i++;
	}
	curr->flags = opcode->flags;
	if (opcode->flags & EXT_OP)
	{
		curr->terminal = REQUIRES_EXT_OP;
		byte = opcode->bytes[i];
		if (curr->children[byte] == NULL)
			curr->children[byte] = calloc(1, sizeof(*curr));
		curr = curr->children[byte];
	}
	curr->terminal = TERMINAL;
	curr->op = opcode;
}

t_optrie	*optrie_search(t_optrie *root, uint8_t *data, uint64_t *iptr)
{
	t_optrie	*curr = root;

	while (curr != NULL)
	{
		if (curr->terminal != NOT_TERMINAL)
			return (curr);

		curr = curr->children[data[(*iptr)++]];
	}

	return (NULL);
}

void	build_optrie(t_optrie *root)
{
	uint64_t	i = 0;
	uint64_t	lim = sizeof(ops) / sizeof(t_opcode);

	while (i < lim)
		opcode_trie_insert(root, &ops[i++]);
}

void	free_optrie_traversal(t_optrie *current)
{
	if (current == NULL)
		return ;

	for (int i = 0; i < 256; i++)
		free_optrie_traversal(current->children[i]);
	free(current);
}

void	free_optrie(t_optrie **root)
{
	t_optrie	*curr = *root;

	free_optrie_traversal(curr);
	*root = NULL;
}
