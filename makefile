clean:
	rm -f *.o Server Client

Server:server.o tictactoe.o serverfuncs.o
	gcc $^ -o $@

server.o:server.c tictactoe.h
	gcc -c $<

tictactoe.o:tictactoe.c tictactoe.h
	gcc -c $<

serverfuncs.o:serverfuncs.c serverfuncs.h
	gcc -c $<

Client:client.o clientfuncs.o
	gcc $^ -o $@

client.o:client.c
	gcc -c $<

clientfuncs.o:clientfuncs.c clientfuncs.h
	gcc -c $<