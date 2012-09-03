all : main.o game.o tools.o
	gcc main.o game.o tools.o -o prog `sdl-config --libs` -lSDL_image

main.o : main.c
	gcc -c main.c -o main.o `sdl-config --cflags`

tools.o : tools.c
	gcc -c tools.c -o tools.o `sdl-config --cflags`

game.o : game.c
	gcc -c game.c -o game.o `sdl-config --cflags`



clean :
	rm -rf *.o

sclean : clean
	rm -rf prog
