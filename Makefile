
SRC_DIR := src
OBJ_DIR := build
TARGET  := $(OBJ_DIR)/main


SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

LDFLAGS := -lGL -lGLU -lglfw -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor
CPPFLAGS := -std=c++11
CXXFLAGS := -MMD
-include $(OBJ_FILES:.o=.d)

$(TARGET): $(OBJ_FILES)
	g++ -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

#build/main.o: src/main.cpp 
#	#mkdir build
#	g++  -c src/main.cpp -o build/main.o -Iglad/include -I./src

#build/main: build/main.o
#	g++ build/main.o -o build/main 
	
run: $(TARGET)
	MESA_GL_VERSION_OVERRIDE=3.3 ./$(TARGET)

clean:
	rm -r $(OBJ_FILES)