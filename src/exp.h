/*****************************************************************************/
/* exp.h                                                                     */
/* 3/31/2018                                                                 */
/* B Wheeless                                                                */
/*                                                                           */
/* Header file for experience point related source code.                     */
/*****************************************************************************/

#ifndef __EXP_H
#define __EXP_H

// For monster experience above level 25, add these values per level and
// Special Ability bonus
#define ABOVE25_EXP                750
#define ABOVE25_SPC_ABILITY_BONUS  25

// Function declarations
int getExperience( int, int ) ;

#endif // __EXP_H