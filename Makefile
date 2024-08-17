
main.exe: main.c
	gcc -o main.exe -lmingw32 ./lib/libSDL2.a ./lib/libSDL2_image.a .\lib\libSDL2main.a D:\lib\SDL2.dll D:\lib\SDL2_image.dll -I include main.c