/*****************************************************************************/
/* exp.c                                                                     */
/* 4/01/2018                                                                 */
/* B Wheeless                                                                */
/*                                                                           */
/* Contains implementation code for function defs found in exp.h             */
/*****************************************************************************/

#include <stdlib.h>
#include "exp.h"

/*****************************************************************************/
/* getExperience()                                                           */
/*         - accepts level and special ability bonus count                   */
/*         - returns experience award for single instance of monster         */
/*****************************************************************************/
int getExperience( int Level, int SABonus ) {
        int totalExp ;

        totalExp = MonsterExpValue[Level][0] + (SABonus * MonsterExpValue[Level][1]) ;

        return totalExp ;
}

