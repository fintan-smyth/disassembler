/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassemble.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:22:05 by fsmyth            #+#    #+#             */
/*   Updated: 2025/12/01 15:57:43 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassemble.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

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

int	is_rex_byte(uint8_t byte)
{
	return (((byte >> 4) & 0b1111) == 0b0100);
}

void	parse_rex_byte(t_state *state, uint8_t byte)
{
	state->flags |= (byte & 0b1111);
}

void	parse_modrm_byte(t_state *state, uint8_t byte)
{
	uint8_t		mod = (byte >> 6) & 0b11;
	uint8_t		reg = (byte >> 3) & 0b111;
	uint8_t		rm = (byte >> 0) & 0b111;
	const char	*reg_name;

	strncpy(state->operand_bufs[OPERAND_RM], "\e[32m", BUF_SIZE);
	strncpy(state->operand_bufs[OPERAND_R], "\e[32m", BUF_SIZE);
	if (state->flags & REX_R)
		reg |= 0b1000;
	if (state->flags & REX_B)
		rm |= 0b1000;

	if (state->flags & EXT_OP)
		state->opnode = state->opnode->children[reg];
	else
	{
		reg_name = state->flags & REX_W ? reg64[reg] : reg32[reg];
		ft_strlcat(state->operand_bufs[OPERAND_R], reg_name, BUF_SIZE);
	}

	switch (mod) {
		case (0b00):
			if ((rm & 0b111) == 0b101)
			{
				// reg_name = state->flags & REX_W ? "(%rip)" : "(%eip)";
				reg_name = "(%rip)";
				ft_strlcat(state->operand_bufs[OPERAND_RM], reg_name, BUF_SIZE);
				state->flags |= DISP_32;
			}
			else if ((rm & 0b111) == 0b100)
				state->flags |= SIB;
			else
			{
				// reg_name = state->flags & REX_W ? reg64[rm] : reg32[rm];
				reg_name = reg64[rm];
				ft_strlcat(state->operand_bufs[OPERAND_RM], "(", BUF_SIZE);
				ft_strlcat(state->operand_bufs[OPERAND_RM], reg_name, BUF_SIZE);
				ft_strlcat(state->operand_bufs[OPERAND_RM], ")", BUF_SIZE);
			}
			break ;
		case (0b01):
			if ((rm & 0b111) == 0b100)
				state->flags |= SIB;
			else
			{
				// reg_name = state->flags & REX_W ? reg64[rm] : reg32[rm];
				reg_name = reg64[rm];
				ft_strlcat(state->operand_bufs[OPERAND_RM], "(", BUF_SIZE);
				ft_strlcat(state->operand_bufs[OPERAND_RM], reg_name, BUF_SIZE);
				ft_strlcat(state->operand_bufs[OPERAND_RM], ")", BUF_SIZE);
			}
			state->flags |= DISP_8;
			break ;
		case (0b10):
			if ((rm & 0b111) == 0b100)
				state->flags |= SIB;
			else
			{
				// reg_name = state->flags & REX_W ? reg64[rm] : reg32[rm];
				reg_name = reg64[rm];
				ft_strlcat(state->operand_bufs[OPERAND_RM], "(", BUF_SIZE);
				ft_strlcat(state->operand_bufs[OPERAND_RM], reg_name, BUF_SIZE);
				ft_strlcat(state->operand_bufs[OPERAND_RM], ")", BUF_SIZE);
			}
			state->flags |= DISP_32;
			break ;
		case (0b11):
			reg_name = state->flags & REX_W ? reg64[rm] : reg32[rm];
			ft_strlcat(state->operand_bufs[OPERAND_RM], reg_name, BUF_SIZE);
			break ;
	}
}

void	parse_reg_code(t_state *state, uint8_t byte)
{
	uint8_t		rm = byte & 0b111;
	const char	**regs = state->flags & REX_W ? reg64 : reg32;

	strncpy(state->operand_bufs[OPERAND_REG_CODE], "\e[32m", BUF_SIZE);
	ft_strlcat(state->operand_bufs[OPERAND_REG_CODE], regs[rm], BUF_SIZE);
}

void	prefix_str(char *dst, const char *src, uint64_t bufsize)
{
	char	tmp[BUF_SIZE];

	strncpy(tmp, dst, BUF_SIZE);
	strncpy(dst, src, bufsize);
	ft_strlcat(dst, tmp, bufsize);
}

uint64_t	parse_rel_value(t_state *state, uint8_t *bytes, uint64_t i)
{
	uint8_t		rel_size = (state->flags >> REL_SHIFT) & 0b111;
	uint64_t	addr;

	switch (rel_size) {
		case (1):
			state->rel8 = *(int8_t *)&bytes[i];
			i += rel_size;
			addr = i + state->rel8;
			break ;
		case (2):
			state->rel16 = *(int16_t *)&bytes[i];
			i += rel_size;
			addr = i + state->rel16;
			break ;
		case (4):
			state->rel32 = *(int32_t *)&bytes[i];
			i += rel_size;
			addr = i + state->rel32;
			break ;
		default:
			return (SIZE_MAX);
	}
	snprintf(state->operand_bufs[OPERAND_REL], BUF_SIZE, "\e[36m%zx", addr);
	return (i);
}

uint64_t	parse_disp_value(t_state *state, uint8_t *bytes, uint64_t i)
{
	uint8_t	disp_size = (state->flags >> DISP_SHIFT) & 0b1111;
	char	buf[BUF_SIZE];
	bool	negative = 0;

	switch (disp_size) {
		case (1):
			state->disp8 = *(int8_t *)&bytes[i];
			if (state->disp8 < 0)
			{
				negative = 1;
				state->disp8 *= -1;
			}
			snprintf(buf, BUF_SIZE, "$0x%x", state->disp8);
			i++;
			break ;
		case (2):
			state->disp16 = *(int16_t *)&bytes[i];
			if (state->disp16 < 0)
			{
				negative = 1;
				state->disp16 *= -1;
			}
			snprintf(buf, BUF_SIZE, "$0x%x", state->disp16);
			i += 2;
			break ;
		case (4):
			state->disp32 = *(int32_t *)&bytes[i];
			if (state->disp32 < 0)
			{
				negative = 1;
				state->disp32 *= -1;
			}
			snprintf(buf, BUF_SIZE, "$0x%x", state->disp32);
			i += 4;
			break ;
		case (8):
			state->disp64 = *(int64_t *)&bytes[i];
			if (state->disp64 < 0)
			{
				negative = 1;
				state->disp64 *= -1;
			}
			snprintf(buf, BUF_SIZE, "$0x%zx", state->disp64);
			i += 8;
			break ;
		default:
			return (SIZE_MAX);
	}

	prefix_str(state->operand_bufs[OPERAND_RM], buf, BUF_SIZE);
	if (negative)
		prefix_str(state->operand_bufs[OPERAND_RM], "-", BUF_SIZE);
	prefix_str(state->operand_bufs[OPERAND_RM], "\e[34m", BUF_SIZE);
	return (i);
}

uint64_t	parse_imm_value(t_state *state, uint8_t *bytes, uint64_t i)
{
	uint8_t	imm_size = (state->flags >> IMM_SHIFT) & 0b1111;

	switch (imm_size) {
		case (1):
			state->imm8 = *(int8_t *)&bytes[i];
			snprintf(state->operand_bufs[OPERAND_IMM], BUF_SIZE, "\e[31m$0x%x", state->imm8);
			i++;
			break ;
		case (2):
			state->imm16 = *(int16_t *)&bytes[i];
			snprintf(state->operand_bufs[OPERAND_IMM], BUF_SIZE, "\e[31m$0x%x", state->imm16);
			i += 2;
			break ;
		case (4):
			state->imm32 = *(int32_t *)&bytes[i];
			snprintf(state->operand_bufs[OPERAND_IMM], BUF_SIZE, "\e[31m$0x%x", state->imm32);
			i += 4;
			break ;
		case (8):
			state->imm64 = *(int64_t *)&bytes[i];
			snprintf(state->operand_bufs[OPERAND_IMM], BUF_SIZE, "\e[31m$0x%02zx", state->imm64);
			i += 8;
			break ;
		default:
			return (SIZE_MAX);
	}

	return (i);
}

void	parse_sib_byte(t_state *state, uint8_t byte)
{
	uint8_t		mod = (byte >> 6) & 0b11;
	uint8_t		index = (byte >> 3) & 0b111;
	uint8_t		base = (byte >> 0) & 0b111;
	uint8_t		scale;
	const char	*index_str = NULL;
	const char	*base_str = NULL;
	const char	*empty = "";

	switch (mod) {
		case (0b00):
			scale = 1;
			break ;
		case (0b01):
			scale = 2;
			break ;
		case (0b10):
			scale = 4;
			break ;
		case (0b11):
			scale = 8;
			break ;
		default:
			return ;
	}

	if (state->flags & REX_X)
		index |= 0b1000;
	if (state->flags & REX_B)
		base |= 0b1000;

	if (index == 0b100)
		index_str = empty;
	else
		index_str = reg64[index];

	if ((base & 0b111) == 0b101)
	{
		switch (mod) {
			case (0b00):
				state->flags |= DISP_32;
				base_str = empty;
				break ;
			case (0b01):
				state->flags |= DISP_8;
				base_str = reg64[base];
				break ;
			case (0b10):
				state->flags |= DISP_32;
				base_str = reg64[base];
				break ;
			default:
				break ;
		}
	}
	else
		base_str = reg64[base];
	if (!(base_str == empty && index_str == empty))
		snprintf(state->operand_bufs[OPERAND_RM], BUF_SIZE, "\e[33m(%s,%s,%d)", base_str, index_str, scale);
}

uint64_t	parse_prefix_bytes(t_state *state, uint8_t *data, uint64_t i)
{
	bool	is_prefix = false;

	do {
		is_prefix = true;
		if (is_rex_byte(data[i]))
			parse_rex_byte(state, data[i++]);
		else if (data[i] == 0x66)
			i++;
		else if (data[i] == 0x2e)
			i++;
		else
			is_prefix = 0;
	} while (is_prefix == 1);

	return (i);
}

void	setup_fixed_registers(t_state *state)
{
	strncpy(state->operand_bufs[OPERAND_RAX], "\e[32m%rax", BUF_SIZE);
	strncpy(state->operand_bufs[OPERAND_AL], "\e[32m%al", BUF_SIZE);
	strncpy(state->operand_bufs[OPERAND_ONE], "\e[31m$1", BUF_SIZE);
}

void	reset_state(t_state *state)
{
	state->flags = 0;
	state->opnode = NULL;
}

void	print_disassembly_line(int fd, t_state *state, uint64_t addr)
{
	const t_opcode	*op = state->opnode->op;
	const char		*src;
	const char		*src2;
	const char		*dst;

	switch (op->n_operands) {
		case (0):
			dprintf(fd, "%16zx:\t\e[35m%s\n\e[m", addr, op->name);
			break ;
		case (1):
			dst = state->operand_bufs[op->op1];
			dprintf(fd, "%16zx:\t\e[35m%s\t%s\n\e[m", addr, op->name, dst);
			break ;
		case (2):
			dst = state->operand_bufs[op->op1];
			src = state->operand_bufs[op->op2];
			dprintf(fd, "%16zx:\t\e[35m%s\t%s\e[m,%s\n\e[m", addr, op->name, src, dst);
			break ;
		case (3):
			dst = state->operand_bufs[op->op1];
			src = state->operand_bufs[op->op2];
			src2 = state->operand_bufs[op->op3];
			dprintf(fd, "%16zx:\t\e[35m%s\t%s,\e[m%s,\e[m%s\n\e[m", addr, op->name, src, src2, dst);
			break ;
		default:
			dprintf(3, "Error!\n");
			break ;
	}
}

int	print_disassembly(int fd, uint8_t *data, uint64_t start, uint64_t end)
{
	t_state		state = {};
	t_optrie	*root = calloc(1, sizeof(*root));

	build_optrie(root);
	setup_fixed_registers(&state);

	uint64_t	i = start;
	uint64_t	instruction_start;

	while (i < end)
	{
		instruction_start = i;
		reset_state(&state);
		i = parse_prefix_bytes(&state, data, i);
		state.opnode = optrie_search(root, data, &i);
		if (state.opnode == NULL)
		{
			printf("op not found\n");
			i = instruction_start + 1;
			continue ;
			// return (1);
		}

		state.flags |= state.opnode->flags;
		if (state.flags & REG_CODE)
			parse_reg_code(&state, data[i - 1]);
		if (state.flags & MODRM)
			parse_modrm_byte(&state, data[i++]);
		if (state.flags & SIB)
			parse_sib_byte(&state, data[i++]);
		if (state.flags & REL_MASK)
			i = parse_rel_value(&state, data, i);
		if (state.flags & DISP_MASK)
			i = parse_disp_value(&state, data, i);
		if (state.flags & IMM_MASK)
			i = parse_imm_value(&state, data, i);

		print_disassembly_line(fd, &state, instruction_start);
	}

	free_optrie(&root);
	return (0);
}
