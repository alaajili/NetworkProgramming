CC = c++
CPPFLAGS = -Wall -Werror -Wextra -std=c++98 -fsanitize=address -g3


showip:
	$(CC) $(CPPFLAGS) showip.cpp -o showip

clean:
	rm -f showip
