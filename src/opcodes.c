/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcodes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 18:57:06 by fsmyth            #+#    #+#             */
/*   Updated: 2025/12/01 15:04:33 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassemble.h"
#include <stdint.h>
#include <stdlib.h>

const t_opcode	ops[] = {
	{ .name = "add",	.bytes = { 0x00 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "add",	.bytes = { 0x01 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "add",	.bytes = { 0x02 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "add",	.bytes = { 0x03 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "add",	.bytes = { 0x04 },			.n_bytes = 1, .flags = IMM_8,					.n_operands = 2, .op1 = OPERAND_AL, .op2 = OPERAND_IMM },
	{ .name = "add",	.bytes = { 0x05 },			.n_bytes = 1, .flags = IMM_32,					.n_operands = 2, .op1 = OPERAND_RAX, .op2 = OPERAND_IMM },
	{ .name = "or",		.bytes = { 0x08 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "or",		.bytes = { 0x09 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "or",		.bytes = { 0x0a },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "or",		.bytes = { 0x0b },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "or",		.bytes = { 0x0c },			.n_bytes = 1, .flags = IMM_8,					.n_operands = 2, .op1 = OPERAND_AL, .op2 = OPERAND_IMM },
	{ .name = "or",		.bytes = { 0x0d },			.n_bytes = 1, .flags = IMM_32,					.n_operands = 2, .op1 = OPERAND_RAX, .op2 = OPERAND_IMM },

	{ .name = "adc",	.bytes = { 0x10 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "adc",	.bytes = { 0x11 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "adc",	.bytes = { 0x12 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "adc",	.bytes = { 0x13 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "adc",	.bytes = { 0x14 },			.n_bytes = 1, .flags = IMM_8,					.n_operands = 2, .op1 = OPERAND_AL, .op2 = OPERAND_IMM },
	{ .name = "adc",	.bytes = { 0x15 },			.n_bytes = 1, .flags = IMM_32,					.n_operands = 2, .op1 = OPERAND_RAX, .op2 = OPERAND_IMM },
	{ .name = "sbb",	.bytes = { 0x18 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "sbb",	.bytes = { 0x19 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "sbb",	.bytes = { 0x1a },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "sbb",	.bytes = { 0x1b },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "sbb",	.bytes = { 0x1c },			.n_bytes = 1, .flags = IMM_8,					.n_operands = 2, .op1 = OPERAND_AL, .op2 = OPERAND_IMM },
	{ .name = "sbb",	.bytes = { 0x1d },			.n_bytes = 1, .flags = IMM_32,					.n_operands = 2, .op1 = OPERAND_RAX, .op2 = OPERAND_IMM },

	{ .name = "and",	.bytes = { 0x20 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "and",	.bytes = { 0x21 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "and",	.bytes = { 0x22 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "and",	.bytes = { 0x23 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "and",	.bytes = { 0x24 },			.n_bytes = 1, .flags = IMM_8,					.n_operands = 2, .op1 = OPERAND_AL, .op2 = OPERAND_IMM },
	{ .name = "and",	.bytes = { 0x25 },			.n_bytes = 1, .flags = IMM_32,					.n_operands = 2, .op1 = OPERAND_RAX, .op2 = OPERAND_IMM },
	{ .name = "sub",	.bytes = { 0x28 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "sub",	.bytes = { 0x29 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "sub",	.bytes = { 0x2a },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "sub",	.bytes = { 0x2b },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "sub",	.bytes = { 0x2c },			.n_bytes = 1, .flags = IMM_8,					.n_operands = 2, .op1 = OPERAND_AL, .op2 = OPERAND_IMM },
	{ .name = "sub",	.bytes = { 0x2d },			.n_bytes = 1, .flags = IMM_32,					.n_operands = 2, .op1 = OPERAND_RAX, .op2 = OPERAND_IMM },

	{ .name = "xor",	.bytes = { 0x30 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "xor",	.bytes = { 0x31 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "xor",	.bytes = { 0x32 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "xor",	.bytes = { 0x33 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "xor",	.bytes = { 0x34 },			.n_bytes = 1, .flags = IMM_8,					.n_operands = 2, .op1 = OPERAND_AL, .op2 = OPERAND_IMM },
	{ .name = "xor",	.bytes = { 0x35 },			.n_bytes = 1, .flags = IMM_32,					.n_operands = 2, .op1 = OPERAND_RAX, .op2 = OPERAND_IMM },
	{ .name = "cmp",	.bytes = { 0x38 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "cmp",	.bytes = { 0x39 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "cmp",	.bytes = { 0x3a },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "cmp",	.bytes = { 0x3b },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "cmp",	.bytes = { 0x3c },			.n_bytes = 1, .flags = IMM_32,					.n_operands = 2, .op1 = OPERAND_AL, .op2 = OPERAND_IMM },
	{ .name = "cmp",	.bytes = { 0x3d },			.n_bytes = 1, .flags = IMM_32,					.n_operands = 2, .op1 = OPERAND_RAX, .op2 = OPERAND_IMM },

	{ .name = "push",	.bytes = { 0x50 },			.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "push",	.bytes = { 0x51 },			.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "push",	.bytes = { 0x52 },			.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "push",	.bytes = { 0x53 },			.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "push",	.bytes = { 0x54 },			.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "push",	.bytes = { 0x55 },			.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "push",	.bytes = { 0x56 },			.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "push",	.bytes = { 0x57 },			.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x58 },			.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x59 },			.n_bytes = 1, .flags = REG_CODE, 				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x5a },			.n_bytes = 1, .flags = REG_CODE, 				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x5b },			.n_bytes = 1, .flags = REG_CODE, 				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x5c },			.n_bytes = 1, .flags = REG_CODE, 				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x5d },			.n_bytes = 1, .flags = REG_CODE, 				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x5e },			.n_bytes = 1, .flags = REG_CODE, 				.n_operands = 1, .op1 = OPERAND_REG_CODE, },
	{ .name = "pop",	.bytes = { 0x5f },			.n_bytes = 1, .flags = REG_CODE,				.n_operands = 1, .op1 = OPERAND_REG_CODE, },

	{ .name = "movslq",	.bytes = { 0x63 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },

	{ .name = "jo",		.bytes = { 0x70 },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jno",	.bytes = { 0x71 },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jb",		.bytes = { 0x72 },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jae",	.bytes = { 0x73 },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "je",		.bytes = { 0x74 },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jne",	.bytes = { 0x75 },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jbe",	.bytes = { 0x76 },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "ja",		.bytes = { 0x77 },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "js",		.bytes = { 0x78 },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jns",	.bytes = { 0x79 },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jp",		.bytes = { 0x7a },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jnp",	.bytes = { 0x7b },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jl",		.bytes = { 0x7c },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jge",	.bytes = { 0x7d },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jle",	.bytes = { 0x7e },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jg",		.bytes = { 0x7f },			.n_bytes = 1, .flags = REL_8,					.n_operands = 1, .op1 = OPERAND_REL },

	{ .name = "add",	.bytes = { 0x80, 0 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "or",		.bytes = { 0x80, 1 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "adc",	.bytes = { 0x80, 2 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "sbb",	.bytes = { 0x80, 3 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "and",	.bytes = { 0x80, 4 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "sub",	.bytes = { 0x80, 5 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "xor",	.bytes = { 0x80, 6 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "cmp",	.bytes = { 0x80, 7 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "add",	.bytes = { 0x81, 0 },		.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "or",		.bytes = { 0x81, 1 },		.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "adc",	.bytes = { 0x81, 2 },		.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "sbb",	.bytes = { 0x81, 3 },		.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "and",	.bytes = { 0x81, 4 },		.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "sub",	.bytes = { 0x81, 5 },		.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "xor",	.bytes = { 0x81, 6 },		.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "cmp",	.bytes = { 0x81, 7 },		.n_bytes = 1, .flags = MODRM | IMM_32 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "add",	.bytes = { 0x83, 0 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "or",		.bytes = { 0x83, 1 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "adc",	.bytes = { 0x83, 2 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "sbb",	.bytes = { 0x83, 3 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "and",	.bytes = { 0x83, 4 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "sub",	.bytes = { 0x83, 5 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "xor",	.bytes = { 0x83, 6 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "cmp",	.bytes = { 0x83, 7 },		.n_bytes = 1, .flags = MODRM | IMM_8 | EXT_OP,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "test",	.bytes = { 0x84 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "test",	.bytes = { 0x85 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "mov",	.bytes = { 0x89 },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_R },
	{ .name = "mov",	.bytes = { 0x8b },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },
	{ .name = "lea",	.bytes = { 0x8d },			.n_bytes = 1, .flags = MODRM,					.n_operands = 2, .op1 = OPERAND_R, .op2 = OPERAND_RM },

	{ .name = "nop",	.bytes = { 0x90 },			.n_bytes = 1, .flags = 0,						.n_operands = 0 },

	{ .name = "mov",	.bytes = { 0xb0 },			.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb1 },			.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb2 },			.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb3 },			.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb4 },			.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb5 },			.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb6 },			.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb7 },			.n_bytes = 1, .flags = REG_CODE | IMM_8,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb8 },			.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xb9 },			.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xba },			.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xbb },			.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xbc },			.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xbd },			.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xbe },			.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xbf },			.n_bytes = 1, .flags = REG_CODE | IMM_32,		.n_operands = 2, .op1 = OPERAND_REG_CODE, .op2 = OPERAND_IMM },

	{ .name = "rol",	.bytes = { 0xc0, 0 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "ror",	.bytes = { 0xc0, 1 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "rcl",	.bytes = { 0xc0, 2 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "rcr",	.bytes = { 0xc0, 3 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "shl",	.bytes = { 0xc0, 4 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "shr",	.bytes = { 0xc0, 5 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "shl",	.bytes = { 0xc0, 6 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "sar",	.bytes = { 0xc0, 7 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "rol",	.bytes = { 0xc1, 0 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "ror",	.bytes = { 0xc1, 1 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "rcl",	.bytes = { 0xc1, 2 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "rcr",	.bytes = { 0xc1, 3 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "shl",	.bytes = { 0xc1, 4 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "shr",	.bytes = { 0xc1, 5 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "shl",	.bytes = { 0xc1, 6 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "sar",	.bytes = { 0xc1, 7 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "ret",	.bytes = { 0xc2 },			.n_bytes = 1, .flags = IMM_16,					.n_operands = 1, .op1 = OPERAND_IMM },
	{ .name = "ret",	.bytes = { 0xc3 },			.n_bytes = 1, .flags = 0,						.n_operands = 0 },
	{ .name = "mov",	.bytes = { 0xc6, 0 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_8,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "mov",	.bytes = { 0xc7, 0 },		.n_bytes = 1, .flags = MODRM | EXT_OP | IMM_32,	.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_IMM },
	{ .name = "leave",	.bytes = { 0xc9 },			.n_bytes = 1, .flags = 0,						.n_operands = 0 },

	{ .name = "rol",	.bytes = { 0xd0, 0 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },
	{ .name = "ror",	.bytes = { 0xd0, 1 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },
	{ .name = "rcl",	.bytes = { 0xd0, 2 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },
	{ .name = "rcr",	.bytes = { 0xd0, 3 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },
	{ .name = "shl",	.bytes = { 0xd0, 4 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },
	{ .name = "shr",	.bytes = { 0xd0, 5 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },
	{ .name = "shl",	.bytes = { 0xd0, 6 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },
	{ .name = "sar",	.bytes = { 0xd0, 7 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },
	{ .name = "rol",	.bytes = { 0xd1, 0 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },
	{ .name = "ror",	.bytes = { 0xd1, 1 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },
	{ .name = "rcl",	.bytes = { 0xd1, 2 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },
	{ .name = "rcr",	.bytes = { 0xd1, 3 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },
	{ .name = "shl",	.bytes = { 0xd1, 4 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },
	{ .name = "shr",	.bytes = { 0xd1, 5 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },
	{ .name = "shl",	.bytes = { 0xd1, 6 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },
	{ .name = "sar",	.bytes = { 0xd1, 7 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 2, .op1 = OPERAND_RM, .op2 = OPERAND_ONE },

	{ .name = "call",	.bytes = { 0xe8 },			.n_bytes = 1, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jmp",	.bytes = { 0xe9 },			.n_bytes = 1, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },

	{ .name = "hlt",	.bytes = { 0xf4 },			.n_bytes = 1, .flags = 0,						.n_operands = 0 },
	{ .name = "inc",	.bytes = { 0xff, 0 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "dec",	.bytes = { 0xff, 1 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "call",	.bytes = { 0xff, 2 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "callf",	.bytes = { 0xff, 3 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "jmp",	.bytes = { 0xff, 4 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "jmpf",	.bytes = { 0xff, 5 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "push",	.bytes = { 0xff, 6 },		.n_bytes = 1, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },

	{ .name = "nop",	.bytes = { 0x0f, 0x1f, 0 },	.n_bytes = 2, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "nop",	.bytes = { 0x0f, 0x1f, 1 },	.n_bytes = 2, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "nop",	.bytes = { 0x0f, 0x1f, 2 },	.n_bytes = 2, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "nop",	.bytes = { 0x0f, 0x1f, 3 },	.n_bytes = 2, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "nop",	.bytes = { 0x0f, 0x1f, 4 },	.n_bytes = 2, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "nop",	.bytes = { 0x0f, 0x1f, 5 },	.n_bytes = 2, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "nop",	.bytes = { 0x0f, 0x1f, 6 },	.n_bytes = 2, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },
	{ .name = "nop",	.bytes = { 0x0f, 0x1f, 7 },	.n_bytes = 2, .flags = MODRM | EXT_OP,			.n_operands = 1, .op1 = OPERAND_RM },

	{ .name = "jo",		.bytes = { 0x0f, 0x80 },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jno",	.bytes = { 0x0f, 0x81 },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jb",		.bytes = { 0x0f, 0x82 },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jae",	.bytes = { 0x0f, 0x83 },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "je",		.bytes = { 0x0f, 0x84 },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jne",	.bytes = { 0x0f, 0x85 },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jbe",	.bytes = { 0x0f, 0x86 },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "ja",		.bytes = { 0x0f, 0x87 },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "js",		.bytes = { 0x0f, 0x88 },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jns",	.bytes = { 0x0f, 0x89 },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jp",		.bytes = { 0x0f, 0x8a },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jnp",	.bytes = { 0x0f, 0x8b },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jl",		.bytes = { 0x0f, 0x8c },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jge",	.bytes = { 0x0f, 0x8d },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jle",	.bytes = { 0x0f, 0x8e },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	{ .name = "jg",		.bytes = { 0x0f, 0x8f },	.n_bytes = 2, .flags = REL_32,					.n_operands = 1, .op1 = OPERAND_REL },
	
	{ .name = "endbr64",.bytes = { 0xf3, 0x0f, 0x1e, 0xfa },	.n_bytes = 4, .flags = 0,			.n_operands = 0, },
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
