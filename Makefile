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

OBJ = $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRC:.c=.o))

NAME = disassemble

all: $(NAME)

# install: $(NAME)
# 	@mkdir -p $(CONFIG_DIR)
# 	@cp -n -v ./default.cfg $(CONFIG_DIR)/yatt.cfg
# 	@cp -fr  ./lang $(CONFIG_DIR)
# 	@cp -vf ./nchex $(BIN_DIR)/yatt

$(NAME): $(BUILD_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ): $(BUILD_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIR):
	@mkdir -p $@

clean:
	rm -rf build/

fclean: clean
	rm -rf $(NAME)

re: fclean all
.PHONY: all clean fclean re #install
