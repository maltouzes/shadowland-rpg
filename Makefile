#LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS=-g -std=c++11

all: main

INSTALL?=install

main: main.o
	@echo "** Building Game.cpp"
#g++ -std=c++11 -o jeux AnimatedSprite.hpp AnimatedSprite.cpp Animation.hpp Animation.cpp Game.hpp Game.cpp main.cpp -I/home/melanie/Programmes/SFML-2.3/include -L/home/melanie/Programmes/SFML-2.3/lib -lsfml-graphics -lsfml-window -lsfml-system
	g++ -std=c++11 -o jeux item.hpp item.cpp game.hpp game.cpp main.cpp -I/home/melanie/Programmes/SFML-2.3/include -L/home/melanie/Programmes/SFML-2.3/lib -lsfml-graphics -lsfml-window -lsfml-system
	export LD_LIBRARY_PATH=/home/melanie/Programmes/SFML-2.3/lib
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
