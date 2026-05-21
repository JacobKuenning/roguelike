#include <ncurses.h>

int main() {
	// screen setup
	initscr();
	printw("Hello World!");
	noecho();
	refresh();

	getch();

	return 0;
}
