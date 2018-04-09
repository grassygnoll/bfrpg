/*****************************************************************************/
/* util.h                                                                    */
/* 4/01/2018                                                                 */
/* B Wheeless                                                                */
/*                                                                           */
/* Header file for utility related source code.                              */
/*****************************************************************************/

#ifndef __UTIL_H
#define __UTIL_H

// Function declarations
FILE* openDBtoWrite( const char*, const char* ) ;
int closeDB( FILE* ) ;
char* chomp(char*) ;
char getAnswer() ;
void expQuery() ;

#endif // __UTIL_H