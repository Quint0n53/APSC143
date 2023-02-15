// APSC 143 Engineering Programming Project Starter Code
// Feel free to change anything about this file, but do not remove "#include "colours.h".

// Make sure to include all relevant libraries
#include "cstdio"
#include "cstdlib"
#include "colours.h"
#include <ctime>

// You don't need to use these, but they help make your code look more organized
#define PACMAN 'P'
#define GHOST 'G'
#define DOT '.'
#define WALL 'W'
#define EMPTY ' '
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'

//global map variable which stores the current game map
char *mapArray[9];
int numDots;

//function header for isWall
int isWall(int currentX, int currentY, int directionX, int directionY);

//general character class that includes variables for both the pacman and the ghosts
class character {
protected:
    //All characters, as well as any sub-classes have access to their current position, and the direction they are headed
    //The upper left of the map is 0,0, +ve x is to the right, +ve y is down
    int currentX, currentY, directionX, directionY;

public:
    //default declaration function for a character
    character() {
        //by default, all characters are not moving
        directionX = 0;
        directionY = 0;
    }

    //public functions to get the position and direction of the character
    int getCurrentX() {
        return currentX;
    }
    //function to get the current y position of a character
    int getCurrentY() {
        return currentY;
    }
    //function to get the current X direction of a character
    int getDirectionX() {
        return directionX;
    }
    //function to get the current y direction of a character
    int getDirectionY() {
        return directionY;
    }

    //public function to set the direction of the character
    void setDirection(char dir) {
        //convert the character entered from the keyboard (w,a,s,d) to a direction
        if (dir == DOWN) {
            directionY = 1;
            directionX = 0;
        } else if (dir == UP) {
            directionY = -1;
            directionX = 0;
        } else if (dir == LEFT) {
            directionX = -1;
            directionY = 0;
        } else if (dir == RIGHT) {
            directionX = 1;
            directionY = 0;
        } else {
            directionX = 0;
            directionY = 0;
        }
    }
    //function to set the x position of any character
    void setCurrentX(int x) {
        currentX = x;
    }
    //function to set the y position of any character
    void setCurrentY(int y) {
        currentY = y;
    }
};

//pacman class which inherits from the character class
class pacman : public character {
public:
    //function to update the current position of pacman
    void updatePosition() {
        //check if the old spot where the player was is not a ghost, if it isn't, update the map to be empty
        //as pacman ate the dot, if there was a dot there
        if (mapArray[currentY][currentX] != GHOST) {
            mapArray[currentY][currentX] = EMPTY;
        }
        //Update the position by adding the current direction of pacman
        currentX += directionX;
        currentY += directionY;
        //if the new spot is a dot, replace it with pacman, and remove 1 from the total number of dots left on map
        if (mapArray[currentY][currentX] == DOT) {
            mapArray[currentY][currentX] = PACMAN;
            numDots--;
        } else {
            //even if there is no dot at the location, replace the spot in the map with pacman
            mapArray[currentY][currentX] = PACMAN;
        }
    }
};

//ghost class which inherits from the character class
class ghost : public character {
private:
    //variables specific to the ghost character numWallsFound is used in the recursive updatePosition function,
    int numWallsFound;
    //variable to store if where the ghost was a dot, this allows the dot to reappear after the ghost moves
    bool wasDot = false;
    //variable storing how many directions a ghost can move from a given position
    int intersectionOptions;
    //function to update the position of the ghost -- involves tracking player if in sight
public:
    //reset function that is called once before each update position call, in order to reset how many walls are found
    void reset() {
        numWallsFound = 0;
        intersectionOptions=0;
    }
    //recursive function used for the ghosts to check in all 4 directions if it can see pacman, if it can then it will attempt to follow
    //Also checks if the ghost is at an intersection, and if so, will choose a direction randomly
    void updatePosition(int dirX, int dirY) {
        //check if the position calculated using the direction and current position is a wall
        if (isWall(currentX, currentY, dirX, dirY)) {
            //if the wall is more than 1 block away, this means the ghost could travel in this direction
            if(dirX >1||dirX<-1||dirY>1||dirY<-1){
                intersectionOptions++;
            }
            //since there is a wall, add 1 to the number of walls found. At any given point, there will be 4 walls around the ghost
            //at a max distance of 8 blocks from the ghost
            numWallsFound++;
            //after the first wall is found, look for the wall above the ghost
            if (numWallsFound == 1) {
                updatePosition(0, -1);
                //after second wall, look for wall to the right of the ghost
            } else if (numWallsFound == 2) {
                updatePosition(1, 0);
                //after third wall, look for wall to the left of the ghost
            } else if (numWallsFound == 3) {
                updatePosition(-1, 0);
            } else {
                //four walls were found, and pacman was not located during the search so the ghost will move randomly
                randomMove();
                //break the recursive loop
                return;
            }
            //if it is not a wall, but a ghost, dot or an empty space, continue searching in that direction
        } else if (mapArray[currentY + dirY][currentX + dirX] == DOT ||
                   (mapArray[currentY + dirY][currentX + dirX] == GHOST) ||
                   mapArray[currentY + dirY][currentX + dirX] == EMPTY) {
            //check if the ghost is heading in the y direction (thus 0 for the x direction)
            if (dirX == 0) {
                //if the direction is greater than zero, continue looking down, continue looking up
                dirY > 0 ? updatePosition(0, dirY + 1) : updatePosition(0, dirY - 1);
            } else {
                //if the ghost is not moving in the y direction, it must be moving in the x-direction. Same principle as above for continuing to search
                //in the same x direction as the previous recursive call
                dirX > 0 ? updatePosition(dirX + 1, 0) : updatePosition(dirX - 1, 0);
            }
            //if the block isn't a wall, ghost, dot or empty, then it must be pacman
        } else  {
            //check which direction pacman is. Pacman is above or below ghost if dirX=0
            if (dirX == 0) {
                //set the new direction of the ghost based off which direction pacman is. If the y direction is positive, pacman is below the ghost
                dirY > 0 ? directionY = 1 : directionY = -1;
                //Ghost is moving vertically, so horizontal movement is set to 0
                directionX = 0;
            } else {
                //pacman is visible horizontally from the ghost. If dirX is above 0, then pacman is to the right, otherwise to the left
                dirX > 0 ? directionX = 1 : directionX = -1;
                //set the vertical movement to 0 because there is horizontal movement
                directionY = 0;
            }
        }
    }
    //function used to control the movement of the ghost if pacman is not visible
    void randomMove() {
        //variable to hold the number of directions the ghost could move
        int numOptions = 0;
        //variable that holds which option is chosen via random number generator
        int choice = 0;
        //temp variable that stores how many options are passed, use to convert the random number, to the actual option in the array
        int optionsPassed = 0;
        //N E S W
        bool options[] = {0, 0, 0, 0};
        //check if the next spot the ghost will move to if it continues in the same direction is a wall or if both directions are 0 (happens at the
        //start of the game), or if there are more than 2 options of directions that the ghost could move
        if (isWall(currentX, currentY, directionX, directionY) || directionY == 0 && directionX == 0||intersectionOptions>2) {
            //check if there is a wall directly north, east, south and west of the ghost (four separate if statements)
            if (!isWall(currentX, currentY, 0, -1)) {
                if (directionY != 1) {
                    //update the position in the array to true, as there is an option (same for all four if statements)
                    options[0] = true;
                    //add one to the options (same for all four if statements)
                    numOptions++;
                }
            }
            if (!isWall(currentX, currentY, 1, 0)) {
                //only an option if the ghost wasn't coming from that direction already
                if (directionX != -1) {
                    options[1] = true;
                    numOptions++;
                }

            }
            if (!isWall(currentX, currentY, 0, 1)) {
                if (directionY != -1) {
                    options[2] = true;
                    numOptions++;
                }

            }
            if (!isWall(currentX, currentY, -1, 0)) {
                if (directionX != 1) {
                    options[3] = true;
                    numOptions++;
                }
            }
            //generate a random number between 0 and the number of options available
            choice = (rand() % numOptions);
            //for loop that loops through all the options in the array
            for (int i = 0; i < 4; i++) {
                //check if the current location in the array is a direction the ghost can move, and the number of options passed, is less than the choice option
                if (options[i] && optionsPassed < choice) {
                    optionsPassed++;
                    //otherwise, if it is an option, and its the correct choice, change the choice variable to the location in the array
                } else if (options[i] && optionsPassed == choice) {
                    choice = i;
                    i = 4;
                }
            }
            //Using the N E S W order of the array, set the direction of the ghost based off which direction was randomly chose
            if (choice == 0) {
                //going up
                directionX = 0;
                directionY = -1;
            } else if (choice == 1) {
                //going to the right
                directionX = 1;
                directionY = 0;
            } else if (choice == 2) {
                //going down
                directionY = 1;
                directionX = 0;
            } else {
                //going left
                directionX = -1;
                directionY = 0;
            }
        }
    }
    //function to actually update the position of the ghost in the map function
    void move() {
        //if there was a dot in the ghosts current position, replace the dot
        if (wasDot) {
            mapArray[currentY][currentX] = DOT;
            //reset if there was a dot
            wasDot = false;
        } else {
            //otherwise reset the spot to empty
            mapArray[currentY][currentX] = EMPTY;
        }
        //update the position
        currentX += directionX;
        currentY += directionY;
        //if the new location is a dot, store that it is a dot in order to replace it later
        if (mapArray[currentY][currentX] == DOT) {
            wasDot = true;
        }
        //update the ghosts position in the map
        mapArray[currentY][currentX] = GHOST;
    }
};

//function headers
void printMap();

void readMap(ghost &ghost1, ghost &ghost2, pacman &player);

int winCheck();

int loseCheck(ghost ghost1, ghost ghost2, pacman player);

void clear();

int main() {
    srand(time(NULL));
    //variable declarations
    ghost ghost1;
    ghost ghost2;
    pacman player;
    //variable that holds the user input
    char userInput = '\0';
    //ensure the total number of dots starts counting from 0
    numDots = 0;
    readMap(ghost1, ghost2, player);
    printMap();
    //infinite loop while game is still valid(not lost or won)
    while (!winCheck() && !loseCheck(ghost1, ghost2, player)) {
        //get user input and store
        userInput = getch();
        //if valid input then move player and ghosts, else just wait for new user input
        if (userInput == DOWN || userInput == UP || userInput == RIGHT || userInput == LEFT) {
            //send direction to player function but not moving yet
            player.setDirection(userInput);
            //reset both ghost moving strategies
            ghost1.reset();
            ghost2.reset();
            //move ghosts using either chase or random move
            ghost1.updatePosition(0, 1);
            ghost2.updatePosition(0, 1);
            //if player is attempting to move into a wall. Let ghosts move and player frozen
            if (isWall(player.getCurrentX(), player.getCurrentY(), player.getDirectionX(), player.getDirectionY())) {
                player.setDirection('b');
            } else { //actually move the player in the map
                player.updatePosition();
            }
            //used to check if the player is attempting to move through the ghost. Since the ghosts current position variable has not been updated yet
            //this if statement will see if the player moved where a ghost just was. If the loseCheck returns true, break the loop
            if (loseCheck(ghost1, ghost2, player)) {
                ghost1.move();
                ghost2.move();
                printMap();
                break;
            }
            //moves ghost to the new location and reprints map to the screen for the user
            ghost1.move();
            ghost2.move();
            printMap();
        }
    }
    //if the loop has ended, either win or loss must be true. Check for win then print statement
    colourChange(15);
    if (winCheck()) {
        printf("Congratulations! You win! Press any key to exit the game\n");

    } else {
        printf("Sorry, you lose. Press any key to exit the game\n");
    }
    //wait for exit character
    getch();
    //empty array memory for proper etiquette
    for (int i = 0; i < 9; i++) {
        free(mapArray[i]);
    }
    return 0;
}

//print map to the console
void printMap() {
    //all walls are blue, ghost is pink, pacman is yellow, dots are white
    colourChange(1);
    //print upper wall not in the map
    printf("W W W W W W W W W W W\n");
    for (int i = 0; i < 9; i++) {
        colourChange(1);
        //print first outer wall
        printf("W ");
        for (int j = 0; j <= 8; j++) {
            //change colour depending on output item
            if (mapArray[i][j] == WALL) {
                colourChange(1);
            } else if (mapArray[i][j] == DOT) {
                colourChange(15);
            } else if (mapArray[i][j] == GHOST) {
                colourChange(13);
            } else if (mapArray[i][j] == PACMAN) {
                colourChange(6);
            }
            //print all items with one space
            printf("%c ", mapArray[i][j]);
        }
        colourChange(1);
        //print outer wall
        printf("W\n");
    }
    colourChange(1);
    //print lower walls
    printf("W W W W W W W W W W W\n");
}

//function to get map from the map.txt file and stock variables
void readMap(ghost &ghost1, ghost &ghost2, pacman &player) {
    FILE *mapFile = fopen("C:\\Users\\vande\\CLionProjects\\APSC143\\apsc143project\\map.txt", "r");
    //safety check for found file
    if (mapFile == NULL) {
        printf("File not found.");
        return;
    }
    //boolean to check for 2 different ghosts
    bool firstGhost = true;
    for (int i = 0; i < 9; i++) {
        //init 2nd dimensions to the map array in malloc
        mapArray[i] = (char *) malloc(sizeof(char) * 10);
        for (int j = 0; j < 9; j++) {
            //get character from the file
            mapArray[i][j] = fgetc(mapFile);
            //check if the character is a ghost or pacman
            if (mapArray[i][j] == PACMAN) {
                player.setCurrentX(j);
                player.setCurrentY(i);
            } else if (mapArray[i][j] == GHOST && firstGhost) {
                ghost1.setCurrentX(j);
                ghost1.setCurrentY(i);
                firstGhost = 0;
            } else if (mapArray[i][j] == GHOST && !firstGhost) {
                ghost2.setCurrentY(i);
                ghost2.setCurrentX(j);
            } else if (mapArray[i][j] == DOT) {
                //used for wincheck function
                numDots++;
            }
            //read in two more characters to get rid of the two blank spaces
            fgetc(mapFile);
            //only read one more character (the newline) if the last line
            if (j != 8) {
                fgetc(mapFile);
            }
        }
        //end each line with null character to avoid junk/new line
        mapArray[i][9] = '\0';
    }
    //close file for etiquette
    fclose(mapFile);

}

int winCheck() {
    //if all the dots have been eaten game must be over
    if (numDots == 0) {
        return 1;
    } else {
        //dots still remain, continue playing
        return 0;
    }
}

//check if either of the ghosts have the same position as the player, if so, the game is lost
int loseCheck(ghost ghost1, ghost ghost2, pacman player) {
    //check if ghost 1 and player are in the same position
    if (ghost1.getCurrentY() == player.getCurrentY() && ghost1.getCurrentX() == player.getCurrentX()) {
        return 1;
        //check ghost 2 and players position
    } else if (ghost2.getCurrentY() == player.getCurrentY() && ghost2.getCurrentX() == player.getCurrentX()) {
        return 1;
        //if both ghosts are not in the same position as the player, then the game has not been lost
    } else {
        return 0;
    }
}

int isWall(int currentX, int currentY, int directionX, int directionY) {
    //check if the character is already on the side of the map, and wants to move towards the outside
    if (currentX + directionX > 8 || currentY + directionY > 8 || currentX + directionX < 0 ||
        currentY + directionY < 0) {
        return 1;
        //check if anyone's current plus direction would hit a "inner" wall of the map
    } else if (mapArray[currentY + directionY][currentX + directionX] == WALL) {
        return 1;
    } else {
        //must not be a wall
        return 0;
    }
}