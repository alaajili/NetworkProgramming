NAME = http
CLIENT = client
SERVER = server
SRV_SRCS = server.cpp
CLI_SRCS = client.cpp
SRV_OBJS = $(SRV_SRCS:.cpp=.o)
CLI_OBJS = $(CLI_SRCS:.cpp=.o)
CC = c++
CPPFLAGS = -std=c++98 -Wall -Werror -Wextra

all: $(NAME)

$(NAME) : $(SERVER) $(CLIENT)

$(SERVER): $(SRV_OBJS)
	$(CC) $(CPPFLAGS) $(SRV_OBJS) -o $(SERVER)

$(CLIENT): $(CLI_OBJS)
	$(CC) $(CPPFLAGS) $(CLI_OBJS) -o $(CLIENT)

clean:
	rm -f $(SRV_OBJS) $(CLI_OBJS)

fclean: clean
	rm -f $(CLIENT) $(SERVER)

re: fclean all
