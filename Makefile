# Nom de l'exécutable final
NAME	= enterTheMatrix

# Compilateur et options
CC		= c++
CFLAGS	= -Wall -Wextra -Werror -std=c++11

# Répertoires
SRC_DIR	= srcs
BUILD_DIR = build

SRCS	= $(SRC_DIR)/Matrix.cpp \
		  $(SRC_DIR)/Vector.cpp \
		  $(SRC_DIR)/linearCombination.cpp \
		  $(SRC_DIR)/main.cpp

OBJS	= $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.cpp=.o)))

RM		= rm -f
RMDIR	= rm -rf

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crée le dossier build s'il n'existe pas
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	$(RMDIR) $(BUILD_DIR)

fclean:	clean
	$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
