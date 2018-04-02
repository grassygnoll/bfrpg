/*****************************************************************************/
/* util.h                                                                    */
/* 4/01/2018                                                                 */
/* B Wheeless                                                                */
/*                                                                           */
/* Header file for utility related source code.                              */
/*****************************************************************************/

// Function declarations
FILE* openDBtoWrite( const char* ) ;
int WriteMonster( FILE*, Monster* ) ;
int closeDB( FILE* ) ;
