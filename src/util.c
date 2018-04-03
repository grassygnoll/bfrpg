/*****************************************************************************/
/* util.c                                                                    */
/* 4/01/2018                                                                 */
/* B Wheeless                                                                */
/*                                                                           */
/* Contains code for manual input of monster data, saving of monster data,   */
/* and other miscellaneous data processing routines for monster data.        */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "monster.h"
#include "util.h"

/*****************************************************************************/
/* openDBtoWrite() - accepts filename and returns opened file handle         */
/*****************************************************************************/
FILE* openDBtoWrite( const char* Name ) {
        return fopen( Name, "a" ) ;
}

/*****************************************************************************/
/* WriteMonster() - Accepts filehandle and Pointer to monster object         */
/*                - Writes monster data to text file                         */
/*****************************************************************************/
int WriteMonster( FILE* db, Monster* m ) {
        fprintf( db, "%s|%i|%i|%c|%c|%i|%i|%i|%i|%i|", m->Name, m->AC.Armored,
                       m->AC.UnArmored, m->AC.HitBySilver, m->AC.HitByMagical,
                       m->HitDice.NbrDice, m->HitDice.DieType, m->HitDice.BonusHP,
                       m->HitDice.SpecialAbilityBonus, m->HitDice.AttackBonus ) ;
        for(int i = 0; i < MAX_NBR_ATTACKS; i++)
            fprintf( db, "%i|%s|", m->NbrAttacks[i].Nbr, m->NbrAttacks[i].Type ) ;
        for(int i = 0; i < MAX_NBR_ATTACKS; i++)
            fprintf( db, "%i|%i|", m->Dmg[i].NbrDice, m->Dmg[i].DieType ) ;
        for(int i = 0; i < NBR_MOVE_TYPES; i++)
            fprintf( db, "%s|%i|%i|", m->Movement[i].Type, m->Movement[i].Distance,
                            m->Movement[i].TurningDistance ) ;
        fprintf( db, "%i|", m->morale ) ;
        for(int i = 0; i < NBR_APPEARING_TYPES; i++)
            fprintf( db, "%s|%i|%i|", m->NbrAppearing[i].Type, m->NbrAppearing[i].NbrDice,
                            m->NbrAppearing[i].DieType ) ;
        fprintf( db, "%s|%i|%s|%i\n", m->SaveAs.Class, m->SaveAs.Level, m->TreasureType,
                        m->Exp ) ;

        return 0 ;
}

/*****************************************************************************/
/* closeDB() - Accepts filehandle and closes file it points to.              */
/*****************************************************************************/
int closeDB( FILE* db ) {
        return fclose(db) ;
}

/*****************************************************************************/
/* init() - Accepts a monster sturcture and populates it with defaults.      */
/*****************************************************************************/
void init(Monster* Mon) {
        Mon->Name[0] = '\0' ;
        Mon->AC.Armored = 20 ;
        Mon->AC.UnArmored = 20 ;
        Mon->AC.HitBySilver = 'N' ;
        Mon->AC.HitByMagical = 'N' ;
        Mon->HitDice.NbrDice = 0 ;
        Mon->HitDice.DieType = 0 ;
        Mon->HitDice.BonusHP = 0 ;
        Mon->HitDice.SpecialAbilityBonus = 0 ;
        Mon->HitDice.AttackBonus = 0 ;
        for( int i = 0; i < MAX_NBR_ATTACKS; i++ ) {
            Mon->NbrAttacks[i].Nbr = 0 ;
            Mon->NbrAttacks[i].Type[0] = '\0' ;
            Mon->Dmg[i].NbrDice = 0 ;
            Mon->Dmg[i].DieType = 0 ;
        }
        for( int i = 0; i < NBR_MOVE_TYPES; i++ ) {
            Mon->Movement[i].Type[0] = '\0' ;
            Mon->Movement[i].Distance = 30 ;
            Mon->Movement[i].TurningDistance = 5 ;
        }
        Mon->morale = 0 ;
        for( int i = 0; i < NBR_APPEARING_TYPES; i++ ) {
            Mon->NbrAppearing[i].Type[0] = '\0' ;
            Mon->NbrAppearing[i].NbrDice = 0 ;
            Mon->NbrAppearing[i].DieType = 0 ;
        }
        Mon->SaveAs.Class[0] = '\0' ;
        Mon->SaveAs.Level = 0 ;
        Mon->TreasureType[0] = '\0' ;
        Mon->Exp = 0 ;
}

/*******************************************************************/
/* chomp() - Accepts a char* and if '\n' is at the end, removes it */
/*******************************************************************/
char* chomp(char* inStr) {
  int end ;

  end = strlen(inStr) - 1 ;
  if( inStr[end] == '\n' )
    inStr[end] = '\0' ;

  return inStr ;
}

/*************************************************************************/
/* getAnswer() - Accepts: nothing; Returns: a character entered on STDIN */
/*               and flushes STDIN up to most recent '\n'                */
/*************************************************************************/
char getAnswer() {
  char a, c ;

  a = getchar() ;
  while( ((c = getchar()) != '\n') && (c != EOF) ) { }

  return a ;
}

/***********************************************************************/
/* manualMonsterEntry() - Accepts a Monster structure and populates it */
/***********************************************************************/
void manualMonsterEntry(Monster* m) {
  char buf[MAX_LEN] ;
  char answer ;

  // Initialize our monster
  init(m) ;

  // Now grab user input on specific monster, start with Name
  printf("Enter monster name: ") ;
  chomp(fgets(m->Name, MAX_LEN, stdin)) ;

  // Grab AC info
  printf("Armored AC: ") ;
  m->AC.Armored = atoi(chomp(fgets(buf, MAX_LEN, stdin))) ;
  printf("Is UnArmored AC different than Armored? [Y/N]: ") ;
  answer = getAnswer() ;
  if( (answer == 'Y') || (answer == 'y') ) {
    printf("UnArmored AC: ") ;
    m->AC.UnArmored = atoi(chomp(fgets(buf, MAX_LEN, stdin))) ;
  } else
    m->AC.UnArmored = m->AC.Armored ;
  printf("Hit by Silver Only? [Y/N]: ") ;
  answer = getAnswer() ;
  if( answer == 'Y' || answer == 'y' )
    m->AC.HitBySilver = 'Y' ;
  printf("Hit by Magical Only? [Y/N]: ") ;
  answer = getAnswer() ;
  if( answer == 'Y' || answer == 'y' )
    m->AC.HitByMagical = 'Y' ;
}
