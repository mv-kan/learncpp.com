FLAGS =  -std=c++20 -Werror -Wall -Weffc++ -Wextra -Wsign-conversion -pedantic-errors -fdiagnostics-color=always -g 
FLAGS_NO_SIGN =  -std=c++20 -Werror -Wall -Weffc++ -Wextra -pedantic-errors -fdiagnostics-color=always -g 
# no -Wsign-conversion
FLAGS_C = -std=c17 -Werror -Wall -Wextra  -pedantic-errors -fdiagnostics-color=always -g 
SRC_FILES = $(wildcard ${SRC}/*.cpp)
ARGS=$()
build:
	g++ ${FLAGS} ${SRC_FILES} -o ${SRC}/main.exe
run_no_sign:
	@g++ ${FLAGS_NO_SIGN} ${SRC_FILES} -o ${SRC}/main.exe
	${SRC}/main.exe

run:
	@g++ ${FLAGS} ${SRC_FILES} -o ${SRC}/main.exe
	${SRC}/main.exe

run_one: 
	@g++ ${FLAGS} ${SRC} -o $(dir ${SRC})/main.exe
	$(dir ${SRC})/main.exe
run_one_no_sign: 
	@g++ ${FLAGS_NO_SIGN} ${SRC} -o $(dir ${SRC})/main.exe
	$(dir ${SRC})/main.exe
run_one_yolo $(SRC):
	echo $(SRC)
	@g++ ${SRC} -o $(dir ${SRC})/main.exe
	$(dir ${SRC})/main.exe

run_one_c:
	gcc ${FLAGS_C} ${SRC} -o $(dir ${SRC})/main.exe -lm
	$(dir ${SRC})/main.exe

run_one_args:
	@g++ ${FLAGS} ${SRC} -o $(dir ${SRC})/main.exe 
	$(dir ${SRC})/main.exe ${ARGS}