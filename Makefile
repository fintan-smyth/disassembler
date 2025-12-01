CC = cc

CFLAGS = -Wall -Wextra -I ./include -O0

DBG_FLAGS =		-g3 \
				# -fsanitize=address \
				# -pg \

SRC_DIR := ./src
BUILD_DIR:= ./build
# CONFIG_DIR:= ${HOME}/.config/nchex
# BIN_DIR:= ${HOME}/.local/bin

SRC = $(SRC_DIR)/disassemble.c \
	  $(SRC_DIR)/opcodes.c \

MAIN = $(SRC_DIR)/main.c

OBJ = $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRC:.c=.o))
OBJ_MAIN = $(BUILD_DIR)/main.o

NAME = disassemble

NAME_LIB = libdisassemble.a

all: $(NAME)

lib: $(NAME_LIB)

# install: $(NAME)
# 	@mkdir -p $(CONFIG_DIR)
# 	@cp -n -v ./default.cfg $(CONFIG_DIR)/yatt.cfg
# 	@cp -fr  ./lang $(CONFIG_DIR)
# 	@cp -vf ./nchex $(BIN_DIR)/yatt

$(NAME): $(BUILD_DIR) $(OBJ) $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(DBG_FLAGS) $(OBJ) $(OBJ_MAIN) -o $(NAME)

$(NAME_LIB): $(BUILD_DIR) $(OBJ)
	ar rcs $(NAME_LIB) $(OBJ)

$(OBJ): $(BUILD_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(DBG_FLAGS) -c $^ -o $@

$(OBJ_MAIN): $(MAIN)
	$(CC) $(CFLAGS) $(DBG_FLAGS) -c $(SRC_DIR)/main.c -o $(BUILD_DIR)/main.o

$(BUILD_DIR):
	@mkdir -p $@

clean:
	rm -rf build/

fclean: clean
	rm -rf $(NAME_LIB)
	rm -rf $(NAME)

re: fclean all
.PHONY: all clean fclean re #install
