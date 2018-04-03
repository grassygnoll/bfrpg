/*****************************************************************************/
/* util.h                                                                    */
/* 4/01/2018                                                                 */
/* B Wheeless                                                                */
/*                                                                           */
/* Header file for utility related source code.                              */
/*****************************************************************************/

// Function declarations
FILE* openDBtoWrite( const char* ) ;
int closeDB( FILE* ) ;
char* chomp(char*) ;
char getAnswer() ;
