LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS=-g -std=c++11
makefile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(makefile_path))))
ROOT_DIR:=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))


all: main

INSTALL?=install

main: main.o
	@echo ""
	@echo "--------------------------"
	@echo "** Building ShadowLand **"
	g++ -std=c++11 -o game -g entity.h creature.h creature.cpp inventory.h inventory.cpp collisions.h collisions.cpp map_manager.hpp map_manager.cpp tilemap.cpp Animation.hpp Animation.cpp AnimatedSprite.hpp AnimatedSprite.cpp item.cpp item.hpp items.cpp items.h game.hpp game.cpp main.cpp $(LIBS)

clean:
	@echo ""
	@echo "--------------------------"
	@echo "** Clean up **"
	rm game
	@echo ""
	@echo "Go to ShadowLand directory"
	@echo "And run Shadowland!"
	@echo "Enjoy!"

install: main
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
