

CCPP = clang++  -I ./include

FLAGS = -Wall -Werror -Wextra 

all: main.cpp 
	${CCPP} main.cpp -D TL=std -o std
	${CCPP} main.cpp -D TL=ft -o ft

test: all
	@clear 
	@echo '----------------- std ---------------' \
	&& ./std \
	&& echo '----------------- ft ---------------' \
	&& ./ft