SRC_FILES	:= $(wildcard src/*.cpp)
HDR_FILES	:= $(wildcard src/*.hpp)

default:
	g++ $(SRC_FILES) -std=c++17 -g -fsanitize=address
