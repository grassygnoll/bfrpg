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
#include "util.h"
#include "exp.h"

/* Main testing function */
int main(int argc, char** argv) {
        char another = 'Y' ;
        char line[MAX_LEN] ;
        int inSize ;
        Monster *Mon, *pMon ;
        int cnt = 0 ;
        int mSize = sizeof(Monster) ;  // 536 bytes currently
        int startSize = 1 ;
        char FNameTxt[] = "./monster.dat" ;
        char FNameBin[] = "./monster.db" ;
        
        // Dynamically allocate a Monster array of startSize elements...
        printf( "How many Monster elements do you want to enter? (default = 1): " ) ;
        inSize = atoi(chomp(fgets(line, MAX_LEN, stdin))) ;
        if( inSize > 1 )
            startSize = inSize ;
        
        // Confirm successful allocation
        Mon = (Monster*)calloc(startSize, mSize) ;
        if( Mon == NULL ) {
            printf( "Memory Error: Unable to allocate Monster array of size = %d!\n", startSize ) ;
            perror( "Memory Error: Unable to allocate Monster array.\n" ) ;
            abort() ;
        }
        else
            pMon = Mon ;

        // Open output text file and binary file...
        FILE* out = openDBtoWrite(FNameTxt, "a") ;
        FILE* outb = openDBtoWrite(FNameBin, "ab") ;

        // Loop until user is done entering monster data
        do {
            // Prompt user for data entry on monster
            manualMonsterEntry(pMon) ;
            cnt++ ;
            
            // Print to text format database
            if( out != NULL )
               WriteMonster( out, pMon ) ;

            // Print to binary format database
            if( outb != NULL )
               StoreMonster( outb, pMon ) ;

            // Print out structure info:
            PrintMonster(pMon) ;
            
            // Done with this Monster, increment pMon
            pMon++ ;

            printf("Add another monster? [Y/N]: ") ;
            another = getAnswer() ;
        } while( ((another != 'n') && (another != 'N')) && (cnt < startSize) ) ;

        // Close output text and binary files
        closeDB( out ) ;
        closeDB( outb ) ;
        
        // Free allocated memory
        free(Mon) ;

        // Based on input, display experience value
        expQuery() ;

        return 0 ;
}
