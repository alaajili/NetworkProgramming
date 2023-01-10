CC = c++
CPPFLAGS = -Wall -Werror -Wextra -std=c++98


showip:
	$(CC) $(CPPFLAGS) showip.cpp -o showip

clean:
	rm -f showip
