/*****************************************************************************/
/* testdrvr.c                                                                */
/* 3/31/2018                                                                 */
/* B Wheeless                                                                */
/*                                                                           */
/* Contains test code to run various parts of app as it is developed.        */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "monster.h"
#include "exp.h"

/* Main testing function */
int main(int argc, char** argv) {
        char another = 'Y' ;
        Monster aMonster ;
        char FNameTxt[] = "./monster.dat" ;
        char FNameBin[] = "./monster.db" ;

        // Open output text file and binary file...
        FILE* out = openDBtoWrite(FNameTxt, "a") ;
        FILE* outb = openDBtoWrite(FNameBin, "ab") ;

        // Loop until user is done entering monster data
        do {
          // Prompt user for data entry on monster
          manualMonsterEntry(&aMonster) ;

          // Print to text format database
          if( out != NULL )
            WriteMonster( out, &aMonster ) ;

          // Print to binary format database
          if( outb != NULL )
            StoreMonster( outb, &aMonster ) ;

          // Print out structure info:
          PrintMonster(&aMonster) ;

          printf("Add another monster? [Y/N]: ") ;
          another = getAnswer() ;
        } while( (another != 'n') && (another != 'N') ) ;

        // Close output text and binary files
        closeDB( out ) ;
        closeDB( outb ) ;

        // Based on input, display experience value
        expQuery() ;

        return 0 ;
}
