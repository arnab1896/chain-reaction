#include <ncurses.h>
#include "code.h"

int main() {
	initscr();
	start_color();	
	
	init_pair(PLAYER1, COLOR_RED, COLOR_BLACK);	
	init_pair(PLAYER2, COLOR_GREEN, COLOR_BLACK);	
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);	
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_YELLOW, COLOR_BLACK);										
	
	attrset(COLOR_PAIR(7));
	attron(A_BOLD);	
	int row, column, r, c;
	int x, y;
	int chk, cw, playerwon, i, g;
	
	char title[30] = "C H A I N   R E A C T I O N";
	x = (COLS - 27) / 2;
	y = (LINES) / 2;
	move(y, x);
	noecho();
	attron(A_UNDERLINE);
	refresh();		
	
	i = 0;
	char *p = &title[0];
	while(*p) {
		printw("%c", *p);
		refresh();
		napms(100);
		p++;
	}
	attroff(A_UNDERLINE);
	refresh();
	napms(500);
	move(y, x);
	deleteln();
	
	g = printmenu();				//displays the menu
	while(g != 2) {	
		if(g == 1) {
			/*opens the "instuctions.txt" file and displays the instructions on the screen*/
			FILE *fp;
			fp = fopen("instructions.txt", "r");
			if(fp == NULL) {
				clear();
				g = printmenu();
				continue;
			}
			int i = 0, j = 0;
			char line[16][64];
			char string[128];
			while(fread(&line[i][j], sizeof(char), 1, fp)) {
				while(line[i][j] != '\n') {
					j++;
					fread(&line[i][j], sizeof(char), 1, fp);
				}	
				line[i][j] = '\0';
				i++;
				j = 0;
			}
			fclose(fp);
			
			clear();
			x = (COLS - 12) / 2;
			y = (LINES - 33) / 2;
			move(y, x);
			attrset(COLOR_PAIR(7));
			attron(A_UNDERLINE);
			attron(A_BOLD);
			printw("INSTRUCTIONS"); 
			attroff(A_UNDERLINE);
			x = (COLS - 60) / 2;
			y = y + 3;
			attrset(COLOR_PAIR(5));
			for(i = 0; i < 15; i++) {
				move(y, x);
				if(i >= 11) {
					attrset(COLOR_PAIR(PLAYER2));
					if(i == 11) {
						attron(A_UNDERLINE);
					}
				}
				printw("%s", line[i]);
				attroff(A_UNDERLINE);
				y = y + 2;
			}
		}	
			
		if(g == 0) {
			/*the game starts*/
			clear();
			attrset(COLOR_PAIR(4));
			x = (COLS - 36) / 2;
			y = (LINES) / 2;
			move(y, x);
			printw("Enter no of rows and columns : ");
			refresh();
			scanw("%d%d", &row, &column);
			refresh();
			move(y, x);
			deleteln();
			refresh();
	
			int grid[row][column];		//creats a 2-d array of size row * column
			init(&grid[0][0], row, column);	
	
			int flag[row][column];		//creats a 2-d array of size row * column
			initflag(&flag[0][0], row, column);			//
	
			attrset(COLOR_PAIR(4));	
			display(&grid[0][0], row, column, &flag[0][0]);
	
			x = (COLS - 60) / 2;
			y = (LINES) - 8;
			pcount = PLAYER1;
			cw = 0;
			i = 0;
			while(1) {
				move(y, x);
				attrset(COLOR_PAIR(pcount));
				printw("Enter row and column at which element is to be placed: ");
				refresh();
				scanw("%d%d", &r, &c);
		
				if(r <= 0 || r > row || c <= 0 || c > column) {
					/*doesn't accept invalid positions*/
					move(y, x);
					clrtoeol();
					continue;
				}
			
				/*checks if player is allowed to place the element*/
				chk = check(&flag[0][0], row, column, r - 1, c - 1);
				if(chk == pcount || chk == 0) {
					place(&grid[0][0], row, column, r - 1, c - 1, &flag[0][0]);
					
					/*changes the player's turn*/
					if(pcount == PLAYER1) {
						pcount = PLAYER2;
					}
					else {
						pcount = PLAYER1;
						cw++;
					}
				}	
				display(&grid[0][0], row, column, &flag[0][0]);
				refresh();
				move(y, x);
				clrtoeol();
				/*checks if the game ends*/
				if((playerwon = checkwon(&flag[0][0], row, column)) && cw > 0) {
					break;
				}
				refresh();
			}
			move(y, x);
			clrtoeol();
			x = (COLS - 15) / 2;
			move(y, x);
			attrset(COLOR_PAIR(playerwon));
			attron(A_BOLD);
			printw("PLAYER %d ", playerwon);
			attroff(A_BOLD);
			attrset(COLOR_PAIR(4));
			printw("WON!!!");
		}
	
	x = (COLS - 31) / 2;
	y = (LINES) - 3;
	move(y, x);
	attrset(COLOR_PAIR(7));
	printw("Press any key to return to menu");
	getch();
		
	clear();
	g = printmenu();
	}
	
	endwin();
	return 0;	
}
