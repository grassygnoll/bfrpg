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

/* External functions */
int getExperience(int, int) ;

/* Main testing function */
int main(int argc, char** argv) {
        int level = 0 ;
        int amount = 0 ;
        int bonuscnt = 0 ;
        int totalEXP = 0 ;
        char cr, flag ;
        Monster aMonster ;
        char FName[] = "./monster.db" ;

        // Loop until user is done entering monster data
        printf("=============================================================") ;
        printf("           Manual Monster Data Entry Section " ) ;
        printf("=============================================================") ;
        
        // Update structure
        init(&aMonster) ;

        aMonster.Name = "Bee, Giant" ;
        aMonster.AC.Armored = 13 ;
        aMonster.HitDice.NbrDice = 1 ;
        aMonster.HitDice.DieType = 4 ;
        aMonster.HitDice.SpecialAbilityBonus = 1 ;
        aMonster.NbrAttacks[0].Nbr = 1 ;
        aMonster.NbrAttacks[0].Type = "sting" ;
        aMonster.Movement[0].Type = "Walk" ;
        aMonster.Movement[0].Distance = 10 ;
        aMonster.Movement[1].Type = "Fly" ;
        aMonster.Movement[1].Distance = 50 ;
        aMonster.morale = 9 ;
        aMonster.Exp = getExperience(0, 1) ;  // Because HD = 1d4 & one special ability bonus

        // Gather input from user:
        printf("Enter level of monster: ") ;
        scanf("%i", &level) ;
        printf("Any special bonuses? [Y/N]: ");
        scanf("%c%c", &cr, &flag) ;
        if( toupper(flag) == 'Y' ) {
                printf("Enter total special bonus count: ") ;
                scanf("%i", &bonuscnt) ;
        }
        printf("Enter total of this monster killed: ") ;
        scanf("%i", &amount) ;

        // Calc and report experience:
        totalEXP = amount * getExperience(level, bonuscnt) ;
        printf("Total Experience Award: %d\n", totalEXP) ;

        // Print out structure info:
        printf( "Monster: %s\n", aMonster.Name ) ;
        printf( "\tAC (armored):  %i\n", aMonster.AC.Armored ) ;
        printf( "\tMovement Type: %s\tSpeed: %i\n", aMonster.Movement[1].Type, aMonster.Movement[1].Distance ) ;
        printf( "\tMorale:        %i\n", aMonster.morale ) ;
        printf( "\tExperience Value: %i\n", aMonster.Exp ) ;

        // Print to database
        FILE* out = openDBtoWrite(FName) ;
        if( out != NULL ) {
                WriteMonster( out, &aMonster ) ;
                closeDB( out ) ;
        }

        return 0 ;
}