# ================= EXECUTABLES =================

NAME        = enterTheMatrix
BONUS_NAME  = bonus_enterTheMatrix

# ================= COMPILER ====================

CC      = c++
CFLAGS  = -Wall -Wextra -Werror -std=c++11

# ================= DIRECTORIES =================

SRC_DIR         = srcs
BONUS_DIR       = bonus
BUILD_DIR       = build
BUILD_BONUS_DIR = build_bonus

# ================= SOURCES =====================

SRCS        = Matrix.cpp Vector.cpp linearCombination.cpp main.cpp
BONUS_SRCS  = Matrix.cpp Vector.cpp linearCombination.cpp main.cpp

# Full paths
SRC_FILES       = $(addprefix $(SRC_DIR)/, $(SRCS))
BONUS_FILES     = $(addprefix $(BONUS_DIR)/, $(BONUS_SRCS))

# Objects
OBJS        = $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))
BONUS_OBJS  = $(addprefix $(BUILD_BONUS_DIR)/, $(BONUS_SRCS:.cpp=.o))

RM      = rm -f
RMDIR   = rm -rf

# ================= RULES =======================

all: $(NAME)

bonus: $(BONUS_NAME)

# -------- NORMAL EXEC --------

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# -------- BONUS EXEC --------

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_BONUS_DIR)/%.o: $(BONUS_DIR)/%.cpp | $(BUILD_BONUS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_BONUS_DIR):
	mkdir -p $(BUILD_BONUS_DIR)

# -------- CLEAN --------

clean:
	$(RMDIR) $(BUILD_DIR) $(BUILD_BONUS_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re
