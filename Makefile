#LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS=-g -std=c++11

all: main

INSTALL?=install

main: main.o
	@echo "** Building Game.cpp"
	g++ -std=c++11 -o jeux Animation.hpp Animation.cpp AnimatedSprite.hpp AnimatedSprite.cpp item.cpp item.hpp game.hpp game.cpp main.cpp -I/home/melanie/Programmes/SFML-2.3.2/include -L/home/melanie/Programmes/SFML-2.3.2/lib -L/home/melanie/Programmes/cpp/sfml/point-and-click/lib -lsfml-graphics -lsfml-window -lsfml-system
	export LD_LIBRARY_PATH=/home/melanie/Programmes/SFML-2.3.2/lib
	@echo "Please run jeux"

clean:
	@echo "** Removing object files and executable..."
	rm -f game *.o
	@echo ""

install: Game
	@echo '** Installing...'
	$(INSTALL) -D Game $(DESTDIR)~/Programmes/cpp/sfml/pacman
	@echo ""

uninstall:
	@echo '** Uninstalling...'
	rm -f ~/Programmes/cpp/sfml/pacman/Game
	@echo ""
