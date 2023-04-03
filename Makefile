all:
	g++ graphic_crack.cpp pill.cpp -c
	g++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio graphic_crack.o pill.o
	./a.out 1 gif
