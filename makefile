all:
		g++ src/main.cpp src/renderwindow.cpp -o bin/acc -lsfml-graphics -lsfml-window -lsfml-system -lGL -lSOIL -std=c++11
clean:
		rm -rf bin/acc
