NAME = test
FLAGS = -std=c++14 -D_NDEBUG -O3 -lpthread
SRCS = ./main.cpp 
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@g++ -o $(NAME) $(OBJS) $(FLAGS)
	@echo "done"

%.o:%.cpp
	@g++ -o $@ -c $< $(FLAGS)

clean:
	@rm $(OBJS)
	@echo ".o files removed"

fclean: clean
	@rm $(NAME)
	@echo "Files removed"

re: fclean all

.PHONY: all clean fclean re