all:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/environment.c src/texture.c src/utils.c src/penguin.c src/timer.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lobj -lopengl32 -lm -o penguinGame.exe -Wall -Wextra -Wpedantic -w

linux:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c -lobj -lSDL2 -lSDL2_image -lGL -lm -o cube -Wall -Wextra -Wpedantic
