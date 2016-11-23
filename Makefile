LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS=-g -std=c++11
makefile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(makefile_path))))
ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))


all: main

INSTALL?=install

main: main.o
	@echo $(ROOT_DIR)
	@echo "** Building shadowland"
	g++ -std=c++11 -o game -g entity.h creature.h creature.cpp inventory.h inventory.cpp collisions.h collisions.cpp map_manager.hpp map_manager.cpp tilemap.cpp Animation.hpp Animation.cpp AnimatedSprite.hpp AnimatedSprite.cpp item.cpp item.hpp items.cpp items.h game.hpp game.cpp main.cpp $(LIBS)
	@echo "Go to Game directory"
	@echo "And run Shadowland!"
	@echo "Enjoy!"

clean:
	@echo "** Removing object files and executable..."
	rm -r $(ROOT_DIR)/Game
	rm game
	@echo ""

install: main
	@echo '** Installing...'
	$(INSTALL) -D game $(ROOT_DIR)/Game/Shadowland
	cp -R $(ROOT_DIR)/Asset $(ROOT_DIR)/Game
	rm game
	@echo ""

uninstall:
	@echo '** Uninstalling...'
	rm -f $(ROOT_DIR)/Game/
	@echo ""
