#include "main.h"

/* 
 * Function name: printMaze()
 * Description: Prints the maze
 */
void printMaze(void) {
  for (int y = SIZE - 1; y >= 0; y--) {
		
    /*
     * Print north wall, mouse, and traces
     */
    for (int x = 0; x < SIZE; x++) {
      if ( hasNorthWall(x, y) )
        if (HIDEEAST)
          printf("+----");
        else 
          printf("+----+");
      else
        if (HIDEEAST)
          printf("+    ");
        else
          printf("+    +");
    }
    
    if (HIDEEAST) {
      printf("+");
    }
    
    printf("\n\r");
  
    
    
    /*
     * Print west and east wall, mouse, and traces
     */
    for (int x = 0; x < SIZE; x++) {
      
      // Print west wall
      if ( hasWestWall(x, y) )
        printf("|");
      else
        printf(" ");
      
      // Print if mouse present
      if ( x == curPosX && y == curPosY ) {
        if (orientation == NORTH)
          printf("  ^ ");
        else if (orientation == EAST)
          printf("  > ");
        else if (orientation == SOUTH)
          printf("  v ");
        else if (orientation == WEST)
          printf("  < ");
      }
      
      // Print markers
      else {
        printf("%4d", distance[x][y]);
      }
      
      // Opt to print east wall
      if (!HIDEEAST) {
        if ( hasEastWall(x, y) )
          printf("|");
        else
          printf(" ");
      }
    }
    
    // Print east boundary if necessary
    if (HIDEEAST){
      printf("|");
    }
    
    printf("\n\r");
    
    // Opt to print south wall
    if (!HIDESOUTH) {
      for (int x = 0; x < SIZE; x++) {
        if ( hasSouthWall(x, y) ) {
          if (HIDEEAST) 
            printf("+----");
          else
            printf("+----+");
        }
        else {
          if (HIDEEAST)
            printf("+    ");
          else 
            printf("+    +");
        }
      }
      
      if (HIDEEAST) {
        printf("+");
      }
      
      printf("\n\r");
    }
  }
  
    // Print south boundary if necessary 
    if(HIDESOUTH) {
      for(int x = 0; x < SIZE; x++) {
        if(HIDEEAST)
          printf("+----");
        else 
          printf("+----+");     
      }
      
      if (HIDEEAST) {
        printf("+");
      }
      
      printf("\n\r");
    }
  
}
