all:
	g++ graphic_crack.cpp -c
	g++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio graphic_crack.o
run:
	./a.out
