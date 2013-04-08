#############MAKEFILE#################

OBJS=main.o cubo_magico.o engine.o input_manager.o model_manager.o renderer.o
CC=g++
DEBUG=-g
CFLAGS=-Wall -fpermissive -std=c++0x $(DEBUG)
LIBS=-lGL -lGLU -lglut

all: cubo

cubo:	$(OBJS)
	$(CC) $(LIBS) $(CFLAGS) $(OBJS) -o cubo

main.o: main.cpp 
	$(CC) $(LIBS) $(CFLAGS) -c main.cpp

engine.o: engine.hpp engine.cpp renderer.hpp input_manager.hpp model_manager.hpp IDrawable.hpp
	$(CC) $(LIBS) $(CFLAGS) -c engine.cpp

input-manager.o: input_manager.hpp input_manager.cpp renderer.hpp model_manager.hpp
	$(CC) $(LIBS) $(CFLAGS) -c input-manager.cpp

model-manager.o: model_manager.hpp model_manager.cpp IDrawable.hpp
	$(CC) $(LIBS) $(CFLAGS) -c model-manager.cpp

renderer.o: renderer.hpp renderer.cpp model_manager.hpp
	$(CC) $(LIBS) $(CFLAGS) -c renderer.cpp

cubo-magico.o: cubo_magico.hpp cubo_magico.cpp IDrawable.hpp
	$(CC) $(LIBS) $(CFLAGS) -c cubo_magico.cpp

clean:
	rm -f *.o
