#include <ncurses.h>
#include "code.h"
#include <string.h>

void init(int *grid, int row, int column) {			//initializes all the elements in the grid to 0
	int count = 0;
	while(count < row * column) {
		*grid = 0;
		grid++;
		count++;
	}
}

void display(int *grid, int row, int column, int *flag) {			//displays the grid
	int count = 0, chk;
	int x, y, indent, xindent, i = 0;
	indent = (COLS - (4 * (column - 1) + 4)) / 2;	
	x = indent;
	y = ((LINES - (2 * (row - 1) + 1) - 8) / 2);			
	move(y, x);
	
	y = y - 1;
	x = x + 1;
	attrset(COLOR_PAIR(5));
	x = x + 4;
	for(i = 1; i <= row; i++) {
		move(y, x);
		printw("%d", i);
		x = x + 4;
	}
	xindent = indent + 5;
	x = xindent;
	y = y + 2;
	i = 1;
	
	attrset(COLOR_PAIR(4));
	while(count < row * column) {
		move(y, x);
		attrset(COLOR_PAIR(4));
		if(*grid) {
			chk = *flag;
			attrset(COLOR_PAIR(chk));
			attron(A_BOLD);
			printw("%d", *grid);
			x = x + 4;
			refresh();
		}
		else {
			printw("_");
			x = x + 4;
			refresh();
		}
		
		grid++;
		flag++;
		count++;
		if(count % column == 0) {
			move(y, indent);
			attrset(COLOR_PAIR(5));
			printw("%d", i);
			i++;
			y = y + 2;
			x = xindent;
			refresh();
		}
	}
}

void place(int *grid, int row, int column, int r, int c, int *flag) {
	if(r < 0 || r >= row || c < 0 || c >= column) {
		/*returns if the element to be placed is outside the boundaries of the grid*/
		return;
	} 
	
	
	int *p = grid;
	int *q = flag;						
	
	int i, j;
	for(i = 0; i < r; i++) {
		for(j = 0; j < column; j++) {
			grid++;
			flag++;							
		}
	}
	for(i = 0; i < c; i++) {
		grid++;
		flag++;						
	}
	
	if(r == 0 || r == row - 1 || c == 0 || c == column - 1) {
		/*element to be placed at the corners*/
		if((r == 0 && c == 0) || (r == row - 1 && c == 0) || (r == 0 && c == column - 1) || (r == row - 1 && c == column - 1)) {
			if(*grid == 0) {
				expand(grid, flag);
			}
			else{
				explode(p, row, column, r, c, q);
			}
		}
		/*element to be placed at the edges*/
		else {
			if(*grid == 0 || *grid == 1) {
				expand(grid, flag);
			}
			else{
				explode(p, row, column, r, c, q);
			}
		}
	}
	/*element to be placed in the inner cells*/
	else if(*grid == 0 || *grid == 1 || *grid == 2) {
		expand(grid, flag);
	}
	else { 
		explode(p, row, column, r, c, q);		
	}
}

void expand(int *grid, int *flag) {				//increases the no. of elements at grid[r][c] by 1;
	(*grid)++;		
	*flag = pcount;							
}


void explode(int *grid, int row, int column, int r, int c, int *flag) {		//grid[row][column] contains 3 elements
	int *p = grid;
	int *q = flag;							
	
	int i, j;
	for(i = 0; i < r; i++) {
		for(j = 0; j < column; j++) {
			grid++;
			flag++;							
		}
	}
	for(i = 0; i < c; i++) {
		grid++;
		flag++;				
	}	
	
	(*grid) = 0;
	(*flag) = 0;					
		
	place(p, row, column, r - 1, c, q);				//place an element at grid[r - 1][c];
	place(p, row, column, r, c + 1, q);				//place an element at grid[r][c + 1];
	place(p, row, column, r + 1, c, q);				//place an element at grid[r + 1][c];
	place(p, row, column, r, c - 1, q);				//place an element at grid[r][c - 1];
}

void initflag(int *flag, int row, int column) {			//initializes all the elements in the flag to 0
	int count = 0;
	while(count < row * column) {
		*flag = 0;
		flag++;
		count++;
	}
}

int check(int *flag, int row, int column, int r, int c) {
	/*checks the element flag[r][c] and returns the corresponding number*/
	int i, j;
	for(i = 0; i < r; i++) {
		for(j = 0; j < column; j++) {
			flag++;							
		}
	}
	for(i = 0; i < c; i++) {
		flag++;						
	}

	if(*flag == 1) {
		return PLAYER1;
	}
	if(*flag == 2) {
		return PLAYER2;
	}
	return 0;
}

int checkwon(int *flag, int row, int column) {
	/*checks if flag contains elements of only one player
		if yes, returns the corresponding number
		else returns 0*/
	int player, count = 0;
	while(count < row * column) {
		if(*flag) {
			player = *flag;
			flag++;
			count++;
			break;
		}
		flag++;
		count++;
	}
	while(count < row * column) {
		if(*flag && *flag != player) {
			return 0;
		}
		flag++;
		count++;
	}
	return player;
}

#define X ((COLS - strlen(menu[c])) / 2)
int printmenu() {
	/*displays the menu on the screen*/
	int key, menuitem = 0, c, x, y;
	
	attrset(COLOR_PAIR(4));
	x = (COLS - 36) / 2;
	y = (LINES) - 5;
	move(y, x);
	printw("Use UP or DOWN arrow key to navigate");
	x = (COLS - 21) / 2;
	y = y + 2;
	move(y, x);
	printw("Press ENTER to select");
	
	attrset(COLOR_PAIR(7));
	x = (COLS - 7) / 2;
	y = 10;
	move(y, x);
	attron(A_UNDERLINE);
	attron(A_BOLD);
	printw("M E N U");
	attroff(A_UNDERLINE);
	
	attrset(COLOR_PAIR(5));
	attron(A_BOLD);
	char menu[3][16] = {"PLAY",  "INSTRUCTIONS", "EXIT"};
	x = (COLS - 40) / 2;
	y = (LINES - 5) / 2;
	for(c = 0;c < 3; c++) {
		if(c == menuitem) {
			attron(A_REVERSE);
		}
		mvaddstr(y + (c * 2), X, menu[c]);
		attroff(A_REVERSE);
	}
	
	/*returns 0, 1 or 2 depending on the option selected*/
	keypad(stdscr, TRUE);
	noecho();
	do {
		key = getch();
		switch(key) {
			case KEY_DOWN:
				menuitem++;
				if(menuitem > 3-1) {
					menuitem = 0;
				}
				break;

			case KEY_UP:
				menuitem--;
				if(menuitem < 0) {
					menuitem = 3-1;
				}
				break;

			default: break;

		}
		for(c = 0;c < 3; c++) {
			if(c == menuitem) {
				attron(A_REVERSE);
			}
			mvaddstr(y + (c * 2), X, menu[c]);
			attroff(A_REVERSE);
		}

	} while(key != '\n');
	echo();
	return menuitem;
}








	
