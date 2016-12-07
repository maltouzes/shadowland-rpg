LIBS=-lsfml-graphics -lsfml-window -lsfml-system
makefile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(makefile_path))))
ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
CC=g++
CFLAGS=-c -g -std=c++11 -pedantic -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wredundant-decls -Wdouble-promotion -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Wlogical-op -Winline -Wshadow
CLFLAGS=-Wall -shared -fPIC


INSTALL?=install

all: shadowland

libtilemap.so: tilemap.cpp
	$(CC) $(CLFLAGS) -o libtilemap.so tilemap.cpp

creature.o: creature.cpp Animation.o
	$(CC) $(CFLAGS) creature.cpp Animation.o $(LIBS)

items.o: items.cpp
	$(CC) $(CFLAGS) items.cpp

inventory.o: inventory.cpp
	$(CC) $(CFLAGS) inventory.cpp

collision.o: collision.cpp
	$(CC) $(CFLAGS) collision.cpp $(LIBS)

map_manager.o: map_manager.cpp
	$(CC) $(CFLAGS) map_manager.cpp

animatedsprite.so: AnimatedSprite.cpp Animation.o
	$(CC) $(CLFLAGS) -o animatedsprite.so AnimatedSprite.cpp

Animation.o: Animation.cpp
	$(CC) $(CFLAGS) Animation.cpp $(LIBS)

game.o: game.cpp animatedsprite.so Animation.o libtilemap.so
	$(CC) $(CFLAGS) game.cpp Animation.o -lanimatedsprite -ltilemap $(LIBS)

main.o: main.cpp game.o
	$(CC) $(CFLAGS) main.cpp game.o

	@echo "--------------------------"
	@echo "** Building ShadowLand **"
shadowland: game.o main.o Animation.o AnimatedSprite.o collisions.o creature.o inventory.o items.o entity.h map_manager.o
	$(CC) main.o game.o Animation.o AnimatedSprite.o collisions.o creature.o inventory.o items.o entity.h map_manager.o -o game $(LIBS)
	@echo "--------------------------"

clean:
	@echo ""
	@echo "--------------------------"
	@echo "** Clean up **"
	rm *.o
	rm *.so
	rm game
	@echo ""
	@echo "Go to ShadowLand directory"
	@echo "And run Shadowland!"
	@echo "Enjoy!"

install: shadowland
	@echo ""
	@echo "--------------------------"
	@echo '** Installing... **'
	$(INSTALL) -D game $(ROOT_DIR)/ShadowLand/Shadowland
	cp -R $(ROOT_DIR)/Asset $(ROOT_DIR)/ShadowLand

uninstall:
	@echo ""
	@echo "--------------------------"
	@echo "** Uninstalling... **"
	rm -f $(ROOT_DIR)/ShadowLand/
	@echo ""
