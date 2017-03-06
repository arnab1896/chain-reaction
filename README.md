DESCRIPTION : 
	
	Chain reaction is a two player board game. The grid is represented by a 2-d integer array. Also another 2-d integer array 'flag' is used, to denote whether an element in the grid at a particular position belongs to player1 or player2.
(The display is done using ncurses)
	
The printmenu() function prints the menu on the screen. It performs the following tasks depending on which option is selected :
	If EXIT is chosen, the game exits.
	If INSTRUCTIONS is chosen, 
	    the program opens the file "instuctions.txt" and displays the text on the screen.
	If PLAY is chosen, the game is played by the following logic :
	
The functions init() and initflag() initializes all elements in the grid and flag respectively to 0.

The display() function displays the grid on the screen.

The check() function checks if a player can place an element at desired position by checking the flag array at that position.

The place() function places an element at position (r, c), passed as arguments to the function. It places the element by the following logic :
	If cell (r, c) hasn't reached its critical mass, then
	    function expand() is called which increments the element at (r, c) by 1.
	else
	    function explode() is called which makes the element at (r, c) = 0 and places one element each in the adjacent cells 
	    i.e. at (r - 1, c), (r, c + 1), (r + 1, c), (r - 1, c - 1) by calling place() function each time.
	    
	Thus place() and explode() call each other recursively multiple times until the grid reaches a stable state, i.e. all the cells
	in the grid have no. of elements less than their critical masses.
	
	The flag array is also altered simultaneously depending on which player places the element.
	
The checkwon() function checks if the grid contains elements of both the players. If it doesn't, then the player whose elements are present in the grid wins, else the game continues.
