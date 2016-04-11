build:
	g++ main.cpp Socket.cpp StdioHelper.cpp IrcMessage.cpp Screen.cpp User.cpp Irc.cpp -ot -lncurses
run:
	./t 127.0.0.1 6667
clean:
	rm t