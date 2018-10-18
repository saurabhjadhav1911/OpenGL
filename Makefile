


build/main.o: src/main.cpp
	#mkdir build
	g++ -std=c++11 -c src/main.cpp -o build/main.o -Iglad/include

build/main: build/main.o
	g++ build/main.o -o build/main -lGL -lGLU -lglfw -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
	
run: build/main
	./build/main

clean:
	rm -r build/