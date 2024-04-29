NAME = convert
CC = c++
RM = rm -f

CFLAGS = -Wall -Wextra -Werror -std=c++98
SRC =  main.cpp  BitcoinExchange.cpp
OBJ = $(SRC:%.cpp=%.o)
all : $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)  -o $(NAME) 
%.o : %.cpp BitcoinExchange.hpp
	$(CC) $(CFLAGS)  -c $< -o $@
clean :
	$(RM) $(OBJ)
fclean : clean
	$(RM) $(NAME)
re : fclean all