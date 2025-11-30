/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassemble.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:22:05 by fsmyth            #+#    #+#             */
/*   Updated: 2025/11/30 14:36:19 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassemble.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char	*reg64[16] = {
	"%rax",
	"%rcx",
	"%rdx",
	"%rbx",
	"%rsp",
	"%rbp",
	"%rsi",
	"%rdi",
	"%r8",
	"%r9",
	"%r10",
	"%r11",
	"%r12",
	"%r13",
	"%r14",
	"%r15",
};

const char	*reg32[16] = {
	"%eax",
	"%ecx",
	"%edx",
	"%ebx",
	"%esp",
	"%ebp",
	"%esi",
	"%edi",
	"%r8d",
	"%r9d",
	"%r10d",
	"%r11d",
	"%r12d",
	"%r13d",
	"%r14d",
	"%r15d",
};

const char	*table_0x83[8] = {
	"add",
	"or",
	"adc",
	"sbb",
	"and",
	"sub",
	"xor",
	"cmp",
};

const t_opcode	ops[] = {
	{ .name = "xor",	.bytes = { 0x31 },		.n_bytes = 1, .flags = MODRM, .extended = 0 },
	{ .name = "push",	.bytes = { 0x50 },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "push",	.bytes = { 0x51 },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "push",	.bytes = { 0x52 },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "push",	.bytes = { 0x53 },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "push",	.bytes = { 0x54 },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "push",	.bytes = { 0x55 },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "push",	.bytes = { 0x56 },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "push",	.bytes = { 0x57 },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "pop",	.bytes = { 0x58 },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "pop",	.bytes = { 0x59 },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "pop",	.bytes = { 0x5a },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "pop",	.bytes = { 0x5b },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "pop",	.bytes = { 0x5c },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "pop",	.bytes = { 0x5d },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "pop",	.bytes = { 0x5e },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "pop",	.bytes = { 0x5f },		.n_bytes = 1, .flags = REG_CODE, .extended = 0 },
	{ .name = "add",	.bytes = { 0x83, 0 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXTENDED_OP, .extended = 1 },
	{ .name = "or",		.bytes = { 0x83, 1 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXTENDED_OP, .extended = 1 },
	{ .name = "adc",	.bytes = { 0x83, 2 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXTENDED_OP, .extended = 1 },
	{ .name = "sbb",	.bytes = { 0x83, 3 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXTENDED_OP, .extended = 1 },
	{ .name = "and",	.bytes = { 0x83, 4 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXTENDED_OP, .extended = 1 },
	{ .name = "sub",	.bytes = { 0x83, 5 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXTENDED_OP, .extended = 1 },
	{ .name = "xor",	.bytes = { 0x83, 6 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXTENDED_OP, .extended = 1 },
	{ .name = "cmp",	.bytes = { 0x83, 7 },	.n_bytes = 1, .flags = MODRM | IMM_8 | EXTENDED_OP, .extended = 1 },
	{ .name = "mov",	.bytes = { 0x89 },		.n_bytes = 1, .flags = MODRM, .extended = 0 },
};

int	is_rex_byte(uint8_t byte)
{
	return (((byte >> 4) & 0b1111) == 0b0100);
}

void	parse_rex_byte(t_state *state, uint8_t byte)
{
	state->flags |= (byte & 0b1111);
}

void	parse_modrm_byte(t_state *state, uint8_t byte, t_optrie **curr_op)
{
	uint8_t		mod = (byte >> 6) & 0b11;
	uint8_t		reg = (byte >> 3) & 0b111;
	uint8_t		rm = (byte >> 0) & 0b111;
	const char	*reg_name;

	if (state->flags & REX_R)
		reg |= 0b1000;
	if (state->flags & REX_B)
		rm |= 0b1000;

	switch (mod) {
		case (0b00):
			break ;
		case (0b01):
			break ;
		case (0b10):
			break ;
		case (0b11):
			if (state->flags & EXTENDED_OP)
				*curr_op = (*curr_op)->children[reg];
			else
			{
				reg_name = state->flags & REX_W ? reg64[reg] : reg32[reg];
				strncpy(state->operand2, reg_name, 255);
			}
			reg_name = state->flags & REX_W ? reg64[rm] : reg32[rm];
			strncpy(state->operand1, reg_name, 255);
			break ;
	}
}

void	parse_reg_code(t_state *state, uint8_t byte)
{
	uint8_t		rm = byte & 0b111;

	strncpy(state->operand1, reg64[rm], 255);
}

uint64_t	parse_imm_value(t_state *state, uint8_t *bytes, uint64_t i)
{
	uint8_t	imm_size = (state->flags >> 7) & 0b1111;

	switch (imm_size) {
		case (1):
			state->imm8 = *(int8_t *)&bytes[i];
			snprintf(state->operand2, 255, "$%#02x", state->imm8);
			i++;
			break ;
		case (2):
			state->imm16 = *(int16_t *)&bytes[i];
			snprintf(state->operand2, 255, "$%#04x", state->imm16);
			i += 2;
			break ;
		case (4):
			state->imm32 = *(int32_t *)&bytes[i];
			snprintf(state->operand2, 255, "$%#08x", state->imm32);
			i += 4;
			break ;
		case (8):
			state->imm64 = *(int64_t *)&bytes[i];
			snprintf(state->operand2, 255, "$%#016zx", state->imm64);
			i += 8;
			break ;
		default:
			return (SIZE_MAX);
	}

	return (i);
}

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
	if (opcode->extended)
	{
		curr->terminal = REQUIRES_EXT_OP;
		byte = opcode->bytes[i];
		if (curr->children[byte] == NULL)
			curr->children[byte] = calloc(1, sizeof(*curr));
		curr = curr->children[byte];
	}
	curr->terminal = TERMINAL;
	curr->name = opcode->name;
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
	// printf("ops: %ld\n", lim);

	while (i < lim)
		opcode_trie_insert(root, &ops[i++]);
}

void	parse_sib_byte(t_state *state, uint8_t byte)
{
	;
}

uint64_t	parse_prefix_bytes(t_state *state, uint8_t *data, uint64_t i)
{
	if (is_rex_byte(data[i]))
		parse_rex_byte(state, data[i++]);

	return (i);
}

void	reset_state(t_state *state)
{
	memset(state, 0, sizeof(*state));
}

void	print_disassembly_line(int fd, t_state *state, uint64_t addr)
{
	dprintf(fd, "%16zx:\t%s\t%s,%s\n", addr, state->operation, state->operand2, state->operand1);
}

int	print_disassembly(int fd, uint8_t *data, uint64_t start, uint64_t end)
{
	t_state		state = {};
	t_optrie	*root = calloc(1, sizeof(*root));
	t_optrie	*curr_op;

	build_optrie(root);
	uint64_t	i = start;
	uint64_t	instruction_start;

	while (i < end)
	{
		instruction_start = i;
		reset_state(&state);
		i = parse_prefix_bytes(&state, data, i);
		curr_op = optrie_search(root, data, &i);
		if (curr_op == NULL)
			return (printf("op not found\n"), 1);

		state.flags |= curr_op->flags;
		if (state.flags & REG_CODE)
			parse_reg_code(&state, data[i - 1]);
		if (state.flags & MODRM)
			parse_modrm_byte(&state, data[i++], &curr_op);
		if (state.flags & SIB)
			parse_sib_byte(&state, data[i++]);
		if (state.flags & IMM_MASK)
			i = parse_imm_value(&state, data, i);

		state.operation = curr_op->name;
		print_disassembly_line(fd, &state, instruction_start);
	}

	return (0);
}
