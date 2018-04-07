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
#include "exp.h"

/*****************************************************************************/
/* openDBtoWrite() - accepts filename and mode to open in                    */
/*                   returns opened file handle                              */
/*****************************************************************************/
FILE* openDBtoWrite( const char* Name, const char* Mode ) {
        return fopen( Name, Mode ) ;
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

/**********************************************************************/
/* StoreMonster() - Accepts file handle and pointer to monster object */
/**********************************************************************/
void StoreMonster( FILE* db, Monster* m ) {
  fwrite(m, sizeof(Monster), 1, db) ;
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

  a = '\n' ;
  while( ((c = getchar()) != '\n') && (c != EOF) ) {
    a = c ;
  }

  if( a == '\n' )
    a = 'N' ;

  return toupper(a) ;
}

/***********************************************************************/
/* manualMonsterEntry() - Accepts a Monster structure and populates it */
/***********************************************************************/
void manualMonsterEntry(Monster* m) {
  char buf[MAX_LEN] ;
  char DefaultTreasure[] = "None" ;
  char answer ;
  char* tmp ;
  int i_tmp, looper ;

  // Print section header/information to screen
  printf("=============================================================\n") ;
  printf("           Manual Monster Data Entry Section\n" ) ;
  printf("=============================================================\n") ;

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
  if( answer == 'Y' ) {
    printf("UnArmored AC: ") ;
    m->AC.UnArmored = atoi(chomp(fgets(buf, MAX_LEN, stdin))) ;
  } else
    m->AC.UnArmored = m->AC.Armored ;
  printf("Hit by Silver Only? [Y/N]: ") ;
  answer = getAnswer() ;
  if( answer == 'Y' )
    m->AC.HitBySilver = 'Y' ;
  printf("Hit by Magical Only? [Y/N]: ") ;
  answer = getAnswer() ;
  if( answer == 'Y' )
    m->AC.HitByMagical = 'Y' ;

  // Grab HD info
  printf("Monster's hit die? [XdY format (ex. 1d8)]: ") ;
  tmp = strtok(chomp(fgets(buf, MAX_LEN, stdin)), "d" ) ;
  if(tmp != NULL)
    m->HitDice.NbrDice = atoi(tmp) ;
  tmp = strtok(NULL, "d") ;
  if(tmp != NULL)
    m->HitDice.DieType = atoi(tmp) ;
  printf("Additional bonus hit points? (default = 0): ") ;
  m->HitDice.BonusHP = atoi(chomp(fgets(buf, MAX_LEN, stdin))) ;
  printf("Special Ability Bonus(es)? (range is 0-2, default = 0): ") ;
  i_tmp = atoi(chomp(fgets(buf, MAX_LEN, stdin))) ;
  if( i_tmp >= 0 && i_tmp < 3 )
    m->HitDice.SpecialAbilityBonus = i_tmp ;
  printf("Attack Bonus (default = Number of HD): ") ;
  i_tmp = atoi(chomp(fgets(buf, MAX_LEN, stdin))) ;
  if( i_tmp == 0 )
    m->HitDice.AttackBonus = m->HitDice.NbrDice ;
  else
    m->HitDice.AttackBonus = i_tmp ;

  // Grab type(s) of attacks (max = 3) and damage associated with each attack
  printf("How many attacks does this monster have? (Max = 3): ") ;
  i_tmp = atoi(chomp(fgets(buf, MAX_LEN, stdin))) ;
  looper = i_tmp - 1 ;
  if( i_tmp > 0 && i_tmp <= 3 ) {
    for(int i = 0; i <= looper; i++) {
      printf("Attack type: ") ;
      chomp(fgets(m->NbrAttacks[i].Type, MAX_LEN, stdin)) ;
      printf("Number of attacks of this type: ") ;
      m->NbrAttacks[i].Nbr = atoi(chomp(fgets(buf, MAX_LEN, stdin))) ;
      printf("Damage of this attack type? [XdY format (ex. 3d6)]: ") ;
      tmp = strtok(chomp(fgets(buf, MAX_LEN, stdin)), "d" ) ;
      if(tmp != NULL)
        m->Dmg[i].NbrDice = atoi(tmp) ;
      tmp = strtok(NULL, "d") ;
      if(tmp != NULL)
        m->Dmg[i].DieType = atoi(tmp) ;
    }
  }

  // Grab movement type(s)
  printf("How many types of movement can this monster use? (Max = 3): ") ;
  i_tmp = atoi(chomp(fgets(buf, MAX_LEN, stdin))) ;
  looper = i_tmp - 1 ;
  if( i_tmp > 0 && i_tmp <= 3) {
    for(int i = 0; i <= looper; i++) {
      printf("Movement type (ex. Walk, Fly, etc.): ") ;
      chomp(fgets(m->Movement[i].Type, MAX_LEN, stdin)) ;
      printf("Distance value in feet (integer value; Default = 30): ") ;
      if( (i_tmp = atoi(chomp(fgets(buf, MAX_LEN, stdin)))) > 0 )
        m->Movement[i].Distance = i_tmp ;
      printf("Turning radius in feet (integer value; Default = 5): ") ;
      if( (i_tmp = atoi(chomp(fgets(buf, MAX_LEN, stdin)))) > 0 )
        m->Movement[i].TurningDistance = i_tmp ;
    }
  }

  // Grab Number Appearing information
  printf("How many groups for numbers appearing? ") ;
  printf("(Ex. 1d6 underground, 2d6 lair, etc.; Max = 3): ") ;
  i_tmp = atoi(chomp(fgets(buf, MAX_LEN, stdin))) ;
  looper = i_tmp - 1 ;
  if( i_tmp > 0 && i_tmp <= 3) {
    for(int i = 0; i <= looper; i++) {
      printf("Group Type: ") ;
      chomp(fgets(m->NbrAppearing[i].Type, MAX_LEN, stdin)) ;
      printf("Number appearing for this group type? [XdY format (ex. 1d6)]: ") ;
      tmp = strtok(chomp(fgets(buf, MAX_LEN, stdin)), "d" ) ;
      if(tmp != NULL)
        m->NbrAppearing[i].NbrDice = atoi(tmp) ;
      tmp = strtok(NULL, "d") ;
      if(tmp != NULL)
        m->NbrAppearing[i].DieType = atoi(tmp) ;
    }
  }

  // Grab SaveAs information
  printf("Save As What Class? ") ;
  chomp(fgets(m->SaveAs.Class, MAX_LEN, stdin)) ;
  printf("Save As What Level? ") ;
  m->SaveAs.Level = atoi(chomp(fgets(buf, MAX_LEN, stdin))) ;

  // Grab morale
  printf("Morale value (integer value): ") ;
  m->morale = atoi(chomp(fgets(buf, MAX_LEN, stdin))) ;

  // Grab Treasure Type info (if any)
  printf("Any treasure type information for this monster? [Y/N]: ") ;
  answer = getAnswer() ;
  if( answer == 'Y' ) {
    printf("Treasure type: ") ;
    chomp(fgets(m->TreasureType, MAX_LEN, stdin)) ;
  } else
    strncpy(m->TreasureType, DefaultTreasure, MAX_LEN) ;

  // Last piece - calc XP and populate the structure value
  m->Exp = getExperience(m->HitDice.NbrDice, m->HitDice.SpecialAbilityBonus) ;
}

/************************************************************************/
/* expQuery() - prompts user for input and prints calculated experience */
/************************************************************************/
void expQuery() {
  char buf[MAX_LEN] ;
  int level = 0, specBonusCnt = 0, nbrKilled = 0, totalEXP = 0 ;
  char answer ;

  // Request needed input from user
  printf("=============================================================\n") ;
  printf("              Monster Experience Point Query\n" ) ;
  printf("=============================================================\n") ;
  printf("Enter level of monster: ") ;
  level = atoi(chomp(fgets(buf, MAX_LEN, stdin))) ;
  printf("Any special bonuses? [Y/N]: ");
  answer = getAnswer() ;
  if( answer == 'Y' ) {
    printf("Enter total special bonus count: ") ;
    specBonusCnt = atoi(chomp(fgets(buf, MAX_LEN, stdin))) ;
  }
  printf("Enter total of this monster killed: ") ;
  nbrKilled = atoi(chomp(fgets(buf, MAX_LEN, stdin))) ;

  // Calc experience and report it:
  totalEXP = nbrKilled * getExperience(level, specBonusCnt) ;
  printf("\nTotal Experience Award: %d\n", totalEXP) ;
}

/*************************************************************/
/* PrintMonster() - Accepts a Monster and prints it "pretty" */
/*************************************************************/
void PrintMonster(Monster* m) {
  //print header and AC info
  printf("=============================================================\n") ;
  printf("                   Monster: %s\n", m->Name ) ;
  printf("=============================================================\n") ;
  printf("Armor Class:    \t%d", m->AC.Armored) ;
  if( m->AC.Armored != m->AC.UnArmored )
    printf(" (Unarmored: %d)", m->AC.UnArmored) ;
  if( m->AC.HitBySilver == 'Y' )
    printf("~") ;
  if( m->AC.HitByMagical == 'Y' )
    printf("^") ;
  printf("\n") ;

  //print Hit Dice info
  printf("Hit Dice:       \t%d", m->HitDice.NbrDice) ;
  if( m->HitDice.DieType != 8 )
    printf("d%d", m->HitDice.DieType) ;
  if( m->HitDice.BonusHP > 0 )
    printf("+%d", m->HitDice.BonusHP) ;
  for(int i = m->HitDice.SpecialAbilityBonus; i > 0; i--)
    printf("*") ;
  if( m->HitDice.AttackBonus != m->HitDice.NbrDice )
    printf(" (+%d)", m->HitDice.AttackBonus) ;
  printf("\n") ;

  //print Attack
  for( int i = 0; i < MAX_NBR_ATTACKS; i++) {
    if( i == 0 )
      printf("No. of Attacks: \t%d %s", m->NbrAttacks[i].Nbr, m->NbrAttacks[i].Type) ;
    else if( (i > 0) && (m->NbrAttacks[i].Nbr != 0))
      printf("/%d %s", m->NbrAttacks[i].Nbr, m->NbrAttacks[i].Type) ;
  }
  printf("\n") ;

  //print Damage
  for( int i = 0; i < MAX_NBR_ATTACKS; i++) {
    if( i == 0 )
      printf("Damage:         \t%dd%d", m->Dmg[i].NbrDice, m->Dmg[i].DieType) ;
    else if( (i > 0) && (m->NbrAttacks[i].Nbr != 0))
      printf("/%dd%d", m->Dmg[i].NbrDice, m->Dmg[i].DieType) ;
  }
  printf("\n") ;

  //print Movement
  for( int i = 0; i < NBR_MOVE_TYPES; i++ ) {
    if( i == 0 ) {
      if( m->Movement[i].TurningDistance != 5 )
        printf("Movement:       \t%d' (%d')", m->Movement[i].Distance,
               m->Movement[i].TurningDistance) ;
      else
        printf("Movement:       \t%d'", m->Movement[i].Distance) ;
    } else {
      if( m->Movement[i].Type[0] != '\0' ) {
        if( m->Movement[i].TurningDistance != 5 )
          printf(" / %d' (%d')", m->Movement[i].Distance, m->Movement[i].TurningDistance) ;
        else
          printf(" / %d'", m->Movement[i].Distance) ;
      }
    }
  }
  printf("\n") ;

  //print Number appearing
  for( int i = 0; i < NBR_APPEARING_TYPES; i++ ) {
    if( i == 0 ) {
      printf("No. Appearing:    \t%s %dd%d", m->NbrAppearing[i].Type,
             m->NbrAppearing[i].NbrDice, m->NbrAppearing[i].DieType) ;
    } else if( m->NbrAppearing[i].Type[0] != '\0' ) {
      printf("; %s %dd%d", m->NbrAppearing[i].Type, m->NbrAppearing[i].NbrDice,
             m->NbrAppearing[i].DieType) ;
    }
  }
  printf("\n") ;

  //print Save As, Morale, Treasure Type, and Experience Value
  printf("Save As:             \t%s: %d\n", m->SaveAs.Class, m->SaveAs.Level) ;
  printf("Morale:              \t%d\n", m->morale) ;
  printf("Treasure Type:       \t%s\n", m->TreasureType) ;
  printf("XP:                  \t%d\n\n", m->Exp) ;
}
