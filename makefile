FLAGS =  -std=c++20 -Werror -Wall -Weffc++ -Wextra -Wsign-conversion -pedantic-errors -fdiagnostics-color=always -g 

SRC_FILES = $(wildcard ${SRC}/*.cpp)
build:
	g++ ${FLAGS} ${SRC_FILES} -o ${SRC}/main.exe

run:
	@g++ ${FLAGS} ${SRC_FILES} -o ${SRC}/main.exe
	${SRC}/main.exe

run_one: 
	@g++ ${FLAGS} ${SRC} -o $(dir ${SRC})/main.exe
	$(dir ${SRC})/main.exe

run_one_yolo $(SRC):
	echo $(SRC)
	@g++ ${SRC} -o $(dir ${SRC})/main.exe
	$(dir ${SRC})/main.exe