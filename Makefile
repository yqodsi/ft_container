

CCPP = clang++ -std=c++98 -I ./include

FLAGS = -Wall -Werror -Wextra 

all: main.cpp 
	${CCPP} main.cpp -o std
	${CCPP} main.cpp -D TL=ft -o ft

test: all
	@clear 
	@echo '----------------- std ---------------' \
	&& ./std | tee std_out \
	&& echo '----------------- ft ---------------' \
	&& ./ft | tee ft_out \
	&& diff ft_out std_out
