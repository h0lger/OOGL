all:
		g++ src/main.cpp src/renderwindow.cpp src/shader.cpp src/transform.cpp src/camera.cpp src/texture.cpp src/objLoader.cpp src/mesh.cpp -o bin/oogl -lsfml-graphics -lsfml-window -lsfml-system -lGL -lSOIL -std=c++11
clean:
		rm -rf bin/oogl

