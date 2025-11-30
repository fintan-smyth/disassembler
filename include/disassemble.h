/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassemble.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsmyth <fsmyth@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 16:47:32 by fsmyth            #+#    #+#             */
/*   Updated: 2025/11/29 00:04:04 by fsmyth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASSEMBLE_H
# define DISASSEMBLE_H

#include <stdbool.h>
#include <stdint.h>

# define IMM_MASK (IMM_8 | IMM_16 | IMM_32 | IMM_64)

enum
{
	REX_B		= (1 << 0),
	REX_X		= (1 << 1),
	REX_R		= (1 << 2),
	REX_W		= (1 << 3),
	EXTENDED_OP	= (1 << 4),
	MODRM		= (1 << 5),
	SIB			= (1 << 6),
	IMM_8		= (1 << 7),
	IMM_16		= (1 << 8),
	IMM_32		= (1 << 9),
	IMM_64		= (1 << 10),
	REG_CODE	= (1 << 11),
};


enum
{
	NOT_TERMINAL = 0,
	TERMINAL,
	REQUIRES_EXT_OP,
};

typedef struct s_opcode
{
	const char	*name;
	uint8_t		bytes[8];
	uint8_t		n_bytes;
	uint64_t	flags;
	bool		extended;
}	t_opcode;

typedef struct s_optrie
{
	uint64_t		flags;
	int				terminal;
	const char		*name;
	struct s_optrie *children[256];
}	t_optrie;

typedef struct s_state
{
	uint64_t	flags;
	const char	*operation;
	const char	**ext_op_table;
	char		operand1[256];
	char		operand2[256];
	char		operand3[256];
	uint8_t		op_extension;
	union {
		int8_t	imm8;
		int16_t	imm16;
		int32_t	imm32;
		int64_t	imm64;
	};
}	t_state;

void		build_optrie(t_optrie *root);
t_optrie	*optrie_search(t_optrie *root, uint8_t *data, uint64_t *iptr);
void		reset_state(t_state *state);
uint64_t	parse_prefix_bytes(t_state *state, uint8_t *data, uint64_t i);
void		parse_sib_byte(t_state *state, uint8_t byte);
uint64_t	parse_imm_value(t_state *state, uint8_t *bytes, uint64_t i);
void		parse_reg_code(t_state *state, uint8_t byte);
void		parse_modrm_byte(t_state *state, uint8_t byte, t_optrie **curr_op);
int	print_disassembly(int fd, uint8_t *data, uint64_t start, uint64_t end);

#endif
