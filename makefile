build:
	g++ -std=c++11 -Wall -o main.exe main.cpp

run:
	./main.exe

clean:
	rm main.exe

valgrind:
	valgrind --leak-check=yes ./main.exe

valgrindFull:
	valgrind --leak-check=full --show-leak-kinds=all ./main.exe