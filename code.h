#define PLAYER1 1
#define PLAYER2 2
int pcount;

void init(int *grid, int row, int column);
void display(int *grid, int row, int column, int *flag);
void place(int *grid, int row, int column, int r, int c, int *flag);
void expand(int *grid, int *flag);
void explode(int *grid, int row, int column, int r, int c, int *flag);			
void select(int row, int column);

void initflag(int *flag, int row, int column);
void flag(int *flag, int row, int column);
void displayflag(int *flag, int row, int column);

int check(int *flag, int row, int column, int r, int c);

int checkwon(int *flag, int row, int column);

int printmenu();
