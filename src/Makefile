TARGET=program
.PHONY: clean
all: $(TARGET)

nbody: 
	gcc -O0 nbody.c nbodylib.c -Wall -Werror -Wvla -lm -lpthread -o nbody

nbody-gui:
	gcc -O0 nbodygui.c nbodylib.c -o nbodygui -Wall -Werror -Wvla -lm -lpthread -lSDL2 -lSDL2_gfx

test:
	gcc -O0 nbodytest.c nbodylib.c -Wall -Werror -Wvla -lm -lpthread -o nbodytest

clean:
	rm -f *.o
	rm -f nbodytest
	rm -f nbodygui
	rm -f nbody
	rm -f benchmark_output.txt
