# Executable name
NAME        = enterTheMatrix

# Compiler
CC          = c++
CFLAGS      = -Wall -Wextra -Werror -std=c++11

# Directories
SRC_DIR     = srcs
BONUS_DIR   = bonus
BUILD_DIR   = build

# Sources
SRCS        = Matrix.cpp Vector.cpp linearCombination.cpp main.cpp
BONUS_SRCS  = 

# Full paths
SRC_FILES       = $(addprefix $(SRC_DIR)/, $(SRCS))
BONUS_FILES     = $(addprefix $(BONUS_DIR)/, $(BONUS_SRCS))

# Objects
OBJS        = $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))
BONUS_OBJS  = $(addprefix $(BUILD_DIR)/, $(BONUS_SRCS:.cpp=.o))

RM          = rm -f
RMDIR       = rm -rf

# ===================== RULES =====================

all: $(NAME)

bonus: $(NAME)

# Executable (normal)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Executable (bonus)
bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJS)

# Compile srcs
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile bonus
$(BUILD_DIR)/%.o: $(BONUS_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	$(RMDIR) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
