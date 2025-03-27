all: tictactoe.cpp
	g++ -o minimax tictactoe.cpp

clean:
	rm minimax