/*****************************************************************************/
/* exp.h                                                                     */
/* 3/31/2018                                                                 */
/* B Wheeless                                                                */
/*                                                                           */
/* Header file for experience point related source code.                     */
/*****************************************************************************/

// For monster experience above level 25, add these values per level and 
// Special Ability bonus
#define ABOVE25_EXP                750
#define ABOVE25_SPC_ABILITY_BONUS  25

/*****************************************************************************/
/* getExperience()                                                           */
/*       - accepts level and special ability bonus count                     */
/*       - returns experience award                                          */
/*****************************************************************************/
// Function declarations
int getExperience( int, int ) ;

// Defines a multi-dimensional array for Monster experience table
// Each row contains 2 columns (Exp value, Spc Ablty Bonus)
int MonsterExpValue[26][2] = {
        {10, 3},        /* Level: < 1 */
        {25, 12},       /* Level: 1   */
        {75, 25},       /* Level: 2   */
        {145, 30},      /* Level: 3   */
        {240, 40},      /* Level: 4   */
        {360, 45},      /* Level: 5   */
        {500, 55},      /* Level: 6   */
        {670, 65},      /* Level: 7   */
        {875, 70},      /* Level: 8   */
        {1075, 75},     /* Level: 9   */
        {1300, 90},     /* Level: 10  */
        {1575, 95},     /* Level: 11  */
        {1875, 100},    /* Level: 12  */
        {2175, 110},    /* Level: 13  */
        {2500, 115},    /* Level: 14  */
        {2850, 125},    /* Level: 15  */
        {3250, 135},    /* Level: 16  */
        {3600, 145},    /* Level: 17  */
        {4000, 160},    /* Level: 18  */
        {4500, 175},    /* Level: 19  */
        {5250, 200},    /* Level: 20  */
        {6000, 225},    /* Level: 21  */
        {6750, 250},    /* Level: 22  */
        {7500, 275},    /* Level: 23  */
        {8250, 300},    /* Level: 24  */
        {9000, 325}     /* Level: 25  */
} ;

