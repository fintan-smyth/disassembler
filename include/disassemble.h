/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassemble.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:47:32 by fsmyth            #+#    #+#             */
/*   Updated: 2025/12/01 15:59:00 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASSEMBLE_H
# define DISASSEMBLE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define BUF_SIZE 32

# define IMM_MASK (IMM_8 | IMM_16 | IMM_32 | IMM_64)
# define DISP_MASK (DISP_8 | DISP_16 | DISP_32 | DISP_64)
# define REL_MASK (REL_8 | REL_16 | REL_32)
# define IMM_SHIFT 7
# define DISP_SHIFT 11
# define REL_SHIFT 15

enum
{
	REX_B		= (1 << 0),
	REX_X		= (1 << 1),
	REX_R		= (1 << 2),
	REX_W		= (1 << 3),
	EXT_OP		= (1 << 4),
	MODRM		= (1 << 5),
	SIB			= (1 << 6),
	IMM_8		= (1 << 7),
	IMM_16		= (1 << 8),
	IMM_32		= (1 << 9),
	IMM_64		= (1 << 10),
	DISP_8		= (1 << 11),
	DISP_16		= (1 << 12),
	DISP_32		= (1 << 13),
	DISP_64		= (1 << 14),
	REL_8		= (1 << 15),
	REL_16		= (1 << 16),
	REL_32		= (1 << 17),
	REG_CODE	= (1 << 18),
	FIXED_REG	= (1 << 19),
};


enum
{
	NOT_TERMINAL = 0,
	TERMINAL,
	REQUIRES_EXT_OP,
};

enum
{
	OPERAND_NONE = 0,
	OPERAND_RM,
	OPERAND_R,
	OPERAND_IMM,
	OPERAND_REG_CODE,
	OPERAND_REL,
	OPERAND_RAX,
	OPERAND_AL,
	OPERAND_ONE,
	OPERAND_MAX,
};

typedef struct s_opcode
{
	const char	*name;
	uint8_t		bytes[8];
	uint8_t		n_bytes;
	uint64_t	flags;
	uint8_t		op1;
	uint8_t		op2;
	uint8_t		op3;
	uint8_t		n_operands;
}	t_opcode;

typedef struct s_optrie
{
	const t_opcode	*op;
	uint64_t		flags;
	int				terminal;
	struct s_optrie *children[256];
}	t_optrie;

typedef struct s_state
{
	uint64_t		flags;
	t_optrie		*opnode;
	char			operand_bufs[OPERAND_MAX][BUF_SIZE];
	union {
		int8_t		imm8;
		int16_t		imm16;
		int32_t		imm32;
		int64_t		imm64;
	};
	union {
		int8_t		disp8;
		int16_t		disp16;
		int32_t		disp32;
		int64_t		disp64;
	};
	union {
		int8_t		rel8;
		int16_t		rel16;
		int32_t		rel32;
	};
}	t_state;

void		build_optrie(t_optrie *root);
t_optrie	*optrie_search(t_optrie *root, uint8_t *data, uint64_t *iptr);
void		free_optrie(t_optrie **root);
void		reset_state(t_state *state);
uint64_t	parse_prefix_bytes(t_state *state, uint8_t *data, uint64_t i);
void		parse_sib_byte(t_state *state, uint8_t byte);
uint64_t	parse_imm_value(t_state *state, uint8_t *bytes, uint64_t i);
void		parse_reg_code(t_state *state, uint8_t byte);
void		parse_modrm_byte(t_state *state, uint8_t byte);
int			print_disassembly(int fd, uint8_t *data, uint64_t start, uint64_t end);

// Utils
size_t	ft_strlcat(char *dst, const char *src, size_t n);

#endif
