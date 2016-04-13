build:
	g++ main.cpp Socket.cpp StdioHelper.cpp IrcMessage.cpp Screen.cpp User.cpp \
	Irc.cpp Channel.cpp StringUtils.cpp -ot -lncurses
run:
	./t 127.0.0.1 6667
clean:
	rm t