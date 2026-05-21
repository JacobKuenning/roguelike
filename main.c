#include <ncurses.h>
#include <stdlib.h>

typedef struct player {
	int xpos;
	int ypos;
	int health;
} player;

void updateplayer(player* p) {
	mvprintw(p->ypos, p->xpos, "@");
}

void moveplayer(player* p, int x, int y) {
	char dest = mvinch(p->ypos+y, p->xpos+x);
	if(dest == '-' || dest == '|') return;
	p->xpos += x;
	p->ypos += y;
}

#define WIDTH 60
#define HEIGHT 30

char** generatemap() {
	char** map = malloc(sizeof(char*)*HEIGHT);
	for(int i = 0; i < HEIGHT; i++) {
		map[i] = malloc(sizeof(char)*WIDTH);
		for(int j = 0; j < WIDTH; j++)
			map[i][j] = ' ';
	}

	// adding 9 rooms, evenly spread across map
	for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) {
		// generating room bounds
		int x1 = rand() % 16;
		int x2 = rand() % 16;
		int y1 = rand() % 6;
		int y2 = rand() % 6;

		// making smaller bound 1 and larger bound 2
		if(x1 > x2) {
			int temp = x1;
			x1 = x2;
			x2 = temp;
		}
		if(y1 > y2) {
			int temp = y1;
			y1 = y2;
			y2 = temp;
		}

		// adding a minimum WIDTH and HEIGHT
		x2 += 4;
		y2 += 4;

		// saving room to map
		for(int x = x1; x <= x2; x++) for(int y = y1; y <= y2; y++) {
			if(y == y1 || y == y2) map[y+10*j][x+20*i] = '-';
			else if(x == x1 || x == x2) map[y+10*j][x+20*i] = '|';
			else map[y+10*j][x+20*i] = '.';
		}
	}

	return map;
}

void printmap(char** map) {
	for(int i = 0; i < HEIGHT; i++)
		mvprintw(i, 0, "%s", map[i]);	
}

int main() {
	// screen setup
	initscr();
	noecho();
	curs_set(0);
	refresh();

	// add map
	char** map = generatemap();
	printmap(map);

	// add player
	player* p = malloc(sizeof(player));
	p->xpos = 14;
	p->ypos = 14;
	p->health = 100;
	updateplayer(p);

	// game loop
	char input;
	while((input = getch()) != 'q') {
		switch (input) {
		case 'h':
			moveplayer(p, -1, 0);
			break;
		case 'j':
			moveplayer(p, 0, 1);
			break;
		case 'k':
			moveplayer(p, 0, -1);
			break;
		case 'l':
			moveplayer(p, 1, 0);
			break;
		case 'y':
			moveplayer(p, -1, -1);
			break;
		case 'u':
			moveplayer(p, 1, -1);
			break;
		case 'b':
			moveplayer(p, -1, 1);
			break;
		case 'n':
			moveplayer(p, 1, 1);
			break;
		}
		// update map
		erase();
		printmap(map);
		updateplayer(p);
	}

	// close screen
	endwin();
	return 0;
}
